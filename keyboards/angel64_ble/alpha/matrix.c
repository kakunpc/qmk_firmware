/*
Copyright 2018 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "quantum.h"

#include "progmem.h"

#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "ble_radio_notification.h"

#include "app_ble_func.h"

#include "i2c.h"
#include "io_expander.h"

#ifndef MATRIX_ROW_PINS
 #include "pin_assign.h"
#endif

#include <stdbool.h>
const uint32_t rowPins[THIS_DEVICE_ROWS] = MATRIX_ROW_PINS;
const uint32_t colPins[THIS_DEVICE_COLS] = MATRIX_COL_PINS;

#ifndef DEBOUNCE
#   define DEBOUNCE 2
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_dummy[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

#define QUEUE_LEN 32
typedef struct {
  ble_switch_state_t* const buf;
  uint8_t ridx, widx, cnt;
  const uint8_t len;
} switch_queue;
ble_switch_state_t rcv_keys_buf[QUEUE_LEN], delay_keys_buf[QUEUE_LEN];
switch_queue rcv_queue={rcv_keys_buf, 0, 0, 0, sizeof(rcv_keys_buf)/sizeof(rcv_keys_buf[0])};
switch_queue delay_queue={delay_keys_buf, 0, 0, 0, sizeof(delay_keys_buf)/sizeof(delay_keys_buf[0])};
#ifndef BURST_TRESHOLD
  extern const uint8_t MAINTASK_INTERVAL;
#ifdef BLE_NUS_MAX_INTERVAL
  #define BURST_THRESHOLD (BLE_NUS_MAX_INTERVAL/MAINTASK_INTERVAL+1)
#else
  #define BURST_THRESHOLD 1
#endif // BLE_NUS_MAX_INTERVAL
#endif

static size_t push_queue(switch_queue *q, ble_switch_state_t dat) {
  if (q->cnt < q->len) {
    q->buf[q->widx++] = dat;
    q->widx %= q->len;
    q->cnt++;
    return 1;
  } else {
    return 0;
  }
}

static size_t pop_queue(switch_queue *q, ble_switch_state_t *dat) {
  if (q->cnt) {
    *dat = q->buf[q->ridx++];
    q->ridx %= q->len;
    q->cnt--;
    return 1;
  } else {
    return 0;
  }
}

static ble_switch_state_t front_queue(switch_queue *q){
  return q->buf[q->ridx];
}

static void init_rows(void);
static void init_cols(void);
void scan_row2col(void);
matrix_row_t get_row2col(uint8_t row);
void unselectCols(void);
void selectCol(uint8_t col);
matrix_col_t readRows(void);
matrix_col_t read_col(uint8_t col);
void unselectRows(void);
void selectRow(uint8_t row);
matrix_row_t readCols(void);
matrix_row_t read_row(uint8_t row);

#define LED_ON()    do { } while (0)
#define LED_OFF()   do { } while (0)
#define LED_TGL()   do { } while (0)

static uint8_t timing;
static uint8_t sync;

/*
void matrix_init(void) {
  // initialize row and col
  init_rows();
  init_cols();
  unselect_cols();
  unselect_rows();
//    NRF_LOG_INFO("matrix init\r\n")

// initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

#if defined(NRF_SEPARATE_KEYBOARD_MASTER) && defined(USE_I2C)
  i2c_init();
#endif
#if defined(NRF_SEPARATE_KEYBOARD_SLAVE) && defined(USE_I2C)
  i2cs_init();
#endif
#if defined(USE_AS_I2C_SLAVE)
  i2cs_init();
#endif
  matrix_init_user();
}
*/

void matrix_init_user(){
  // initialize row and col
  init_rows();
  init_cols();
  unselectCols();
  unselectRows();
//    NRF_LOG_INFO("matrix init\r\n")

// initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

#if defined(NRF_SEPARATE_KEYBOARD_MASTER) && defined(USE_I2C)
  i2c_init();
#endif
#if defined(NRF_SEPARATE_KEYBOARD_SLAVE) && defined(USE_I2C)
  i2cs_init();
#endif
#if defined(USE_AS_I2C_SLAVE)
  i2cs_init();
#endif

  set_usb_enabled(true);

}


static inline void set_received_key(ble_switch_state_t key, bool from_slave) {
  const uint8_t matrix_offset = 0;

  uint8_t row = key.id / MATRIX_COLS;
  uint8_t col = key.id % MATRIX_COLS;

  if (key.state) {
    matrix[row + matrix_offset] |= (1 << col);
  } else {
    matrix[row + matrix_offset] &= ~(1 << col);
  }
}

uint8_t matrix_scan_impl(matrix_row_t* _matrix){
  uint8_t matrix_offset = 0;
  volatile int matrix_changed = 0;
  ble_switch_state_t ble_switch_send[THIS_DEVICE_ROWS*THIS_DEVICE_COLS];

  matrix_offset = 0;
  init_rows();
  for (uint8_t i = 0; i < THIS_DEVICE_ROWS; i++) {
    matrix_row_t row = read_row(i);
    if (matrix_debouncing[i + matrix_offset] != row) {
      matrix_debouncing[i + matrix_offset] = row;
      debouncing = DEBOUNCE;
    }
  }


  if (debouncing) {
    if (--debouncing) {
//            wait_ms(1);
    } else {
      for (uint8_t i = 0; i < THIS_DEVICE_ROWS; i++) {
        if (matrix_dummy[i + matrix_offset] != matrix_debouncing[i + matrix_offset]) {
          for (uint8_t j = 0; j < THIS_DEVICE_COLS; j++) {
            if ((matrix_dummy[i + matrix_offset]
                ^ matrix_debouncing[i + matrix_offset]) & (1 << j)) {
              ble_switch_send[0].dat[0]=0xff;
              ble_switch_send[0].dat[1]=((int)sync) % 0xff; // synchronizing packet
              ble_switch_send[matrix_changed+1].timing = timing;
              ble_switch_send[matrix_changed+1].state = (matrix_debouncing[i
                  + matrix_offset] >> j) & 1;
              ble_switch_send[matrix_changed+1].id = i * MATRIX_COLS + j;
              matrix_changed++;
            }
          }
        }
#if defined(NRF_SEPARATE_KEYBOARD_MASTER) || defined(NRF_SEPARATE_KEYBOARD_SLAVE)
        matrix_dummy[i + matrix_offset] = matrix_debouncing[i + matrix_offset];
//        matrix[i + matrix_offset] = matrix_debouncing[i + matrix_offset]; Do not set matrix directory
#else
        matrix_dummy[i + matrix_offset] = matrix_debouncing[i + matrix_offset];
        matrix[i + matrix_offset] = matrix_debouncing[i + matrix_offset];
#endif
      }
    }
  }

  matrix_offset = MATRIX_ROWS / 2;
  init_cols();
  scan_row2col();
  for (uint8_t i = 0; i < THIS_DEVICE_ROWS; i++) {
    matrix_row_t row = get_row2col(i);
    if (matrix_debouncing[i + matrix_offset] != row) {
      matrix_debouncing[i + matrix_offset] = row;
      debouncing = DEBOUNCE;
    }
  }

  if (debouncing) {
    if (--debouncing) {
//            wait_ms(1);
    } else {
      for (uint8_t i = 0; i < THIS_DEVICE_ROWS; i++) {
        if (matrix_dummy[i + matrix_offset] != matrix_debouncing[i + matrix_offset]) {
          for (uint8_t j = 0; j < THIS_DEVICE_COLS; j++) {
            if ((matrix_dummy[i + matrix_offset]
                ^ matrix_debouncing[i + matrix_offset]) & (1 << j)) {
              ble_switch_send[0].dat[0]=0xff;
              ble_switch_send[0].dat[1]=((int)sync) % 0xff; // synchronizing packet
              ble_switch_send[matrix_changed+1].timing = timing;
              ble_switch_send[matrix_changed+1].state = (matrix_debouncing[i
                  + matrix_offset] >> j) & 1;
              ble_switch_send[matrix_changed+1].id = i * MATRIX_COLS + j;
              matrix_changed++;
            }
          }
        }
#if defined(NRF_SEPARATE_KEYBOARD_MASTER) || defined(NRF_SEPARATE_KEYBOARD_SLAVE)
        matrix_dummy[i + matrix_offset] = matrix_debouncing[i + matrix_offset];
//        matrix[i + matrix_offset] = matrix_debouncing[i + matrix_offset]; Do not set matrix directory
#else
        matrix_dummy[i + matrix_offset] = matrix_debouncing[i + matrix_offset];
        matrix[i + matrix_offset] = matrix_debouncing[i + matrix_offset];
#endif
      }
    }
  }

#if defined(NRF_SEPARATE_KEYBOARD_MASTER)
  for (int i=0; i<matrix_changed; i++) {
    push_queue(&delay_queue, ble_switch_send[i+1]);
  }

#if defined(NRF_SEPARATE_KEYBOARD_MASTER) && defined(USE_I2C)
#if MATRIX_COLS>8
#error "MATRIX_COLS should be less than eight for I2C "
#endif
  uint8_t slave_offset = 0;
  uint8_t slave_matrix_changed = 0;
  uint8_t i2c_dat[MATRIX_ROWS];
  memset(i2c_dat, 0xFF, sizeof(i2c_dat));
//  i2c_readReg(SLAVE_I2C_ADDRESS, 0, i2c_dat, MATRIX_ROWS - THIS_DEVICE_ROWS, 0);
  i2c_init();
  i2c_receive(SLAVE_I2C_ADDRESS, i2c_dat, MATRIX_ROWS - THIS_DEVICE_ROWS);
  i2c_uninit();
  uint8_t comm_error=0;
  for (uint8_t i = 0; i < MATRIX_ROWS - THIS_DEVICE_ROWS; i++) {
    if (i2c_dat[i]==0xFF) {
      comm_error=1;
    }
  }
  if (!comm_error) {
    for (uint8_t i = 0; i < MATRIX_ROWS - THIS_DEVICE_ROWS; i++) {
      if (matrix_dummy[i + slave_offset] != i2c_dat[i]) {
        for (uint8_t j = 0; j < MATRIX_COLS; j++) {
          if ((matrix_dummy[i + slave_offset] ^ i2c_dat[i]) & (1 << j)) {
            ble_switch_send[0].dat[0] = 0xff;
            ble_switch_send[0].dat[1] = ((int) sync) % 0xff; // synchronizing packet
            ble_switch_send[slave_matrix_changed + 1].timing = timing;
            ble_switch_send[slave_matrix_changed + 1].state = (i2c_dat[i] >> j) & 1;
            ble_switch_send[slave_matrix_changed + 1].id = i * MATRIX_COLS + j;
            slave_matrix_changed++;
          }
        }
      }
      matrix_dummy[i + slave_offset] = i2c_dat[i];
    }
    for (int i=0; i<slave_matrix_changed; i++) {
      push_queue(&rcv_queue, ble_switch_send[i+1]);
    }
  }
  else {
#ifdef USE_LP_MAT_EXPANDER
    // initialize LP_MAT_EXPANDER
    i2c_init();
    lp_mat_config_t lpconf = LP_MAT_CONFIG;
    uint8_t* plpconf = (uint8_t*)&lpconf;
    lpconf.checksum = 0;
    for(uint8_t i=0; i<sizeof(lpconf)-1; i++) {
      lpconf.checksum ^= plpconf[i];
    }
    i2c_transmit(SLAVE_I2C_ADDRESS, plpconf, sizeof(lpconf));
    i2c_uninit();
#endif
  }
#endif

#endif

/* Power consumption test*/
//  static int cnt1, cnt2;
//  if(cnt1 == 0){
////    matrix[0] |= 0x1;
//    matrix_changed = 1;
//    ble_switch_send[0].timing = 0;
//    ble_switch_send[0].row = 3;
//    ble_switch_send[0].col = 0;
//    ble_switch_send[0].state = 1;
//  } else if(cnt1==3){
////    matrix[0] &= ~0x1;
//    matrix_changed = 1;
//    ble_switch_send[0].timing = 0;
//    ble_switch_send[0].row = 3;
//    ble_switch_send[0].col = 0;
//    ble_switch_send[0].state = 0;
//  }
//  cnt1++;
//  cnt1%=6;
//
//  if(cnt2 == 0){
//      sprintf(str, "%4dmV\n", get_vcc());
////      send_string(str);
//  }
//  cnt2++;
//  cnt2%=10000;

#if defined(USE_AS_I2C_SLAVE)
  i2cs_prepare((uint8_t*)&matrix_dummy[matrix_offset], sizeof(matrix_row_t)*THIS_DEVICE_ROWS);
  UNUSED_VARIABLE(ble_switch_send);
#endif
  UNUSED_VARIABLE(ble_switch_send);

  timing++;
  if(timing==0xFF) timing=0;

  // Process received keys
  ble_switch_state_t rcv_key;
  uint8_t slave_time_stamp = 0;
  uint8_t master_time_stamp = 0;
  static uint8_t dowel_count;

  slave_time_stamp = rcv_queue.cnt ? front_queue(&rcv_queue).timing : 0xFF;
  master_time_stamp = delay_queue.cnt ? front_queue(&delay_queue).timing : 0xFF;

  // count delay of master inputs
  dowel_count = timing - front_queue(&delay_queue).timing;

  // master key inputs are proceeded after constant delay or newer slave inputs come.
  if ((master_time_stamp != 0xFF && dowel_count >= BURST_THRESHOLD) || (rcv_queue.cnt &&
      ((master_time_stamp < slave_time_stamp) ))) {
    while (delay_queue.cnt) {
      rcv_key = front_queue(&delay_queue);
      if (master_time_stamp == rcv_key.timing) {
        set_received_key(rcv_key, false);
        pop_queue(&delay_queue, &rcv_key);
      } else {
        break;
      }
    }
  }
  // slave key inputs are proceeded if they are older
  if (master_time_stamp >= slave_time_stamp) {
    while (rcv_queue.cnt) {
      rcv_key = front_queue(&rcv_queue);
      if (slave_time_stamp == rcv_key.timing) {
        set_received_key(rcv_key, true);
        pop_queue(&rcv_queue, &rcv_key);
      } else {
        break;
      }
    }
  }
  return 1;
}

char str[16];

static void init_rows() {
  for(int i=0; i<THIS_DEVICE_COLS; i++) {
    nrf_gpio_cfg_input(colPins[i], NRF_GPIO_PIN_PULLUP);
  }
  for(int i=0; i<THIS_DEVICE_ROWS; i++) {
    nrf_gpio_cfg(rowPins[i],
        NRF_GPIO_PIN_DIR_OUTPUT,
        NRF_GPIO_PIN_INPUT_DISCONNECT,
        NRF_GPIO_PIN_NOPULL,
        NRF_GPIO_PIN_S0D1,
        NRF_GPIO_PIN_NOSENSE);
  }
}
/* Column pin configuration
 */
static void  init_cols(void)
{
  for(int i=0; i<THIS_DEVICE_ROWS; i++) {
    nrf_gpio_cfg_input(rowPins[i], NRF_GPIO_PIN_PULLUP);
  }
  for(int i=0; i<THIS_DEVICE_COLS; i++) {
    nrf_gpio_cfg(colPins[i],
        NRF_GPIO_PIN_DIR_OUTPUT,
        NRF_GPIO_PIN_INPUT_DISCONNECT,
        NRF_GPIO_PIN_NOPULL,
        NRF_GPIO_PIN_S0D1,
        NRF_GPIO_PIN_NOSENSE);
  }
}
matrix_row_t matrix_row2col[MATRIX_ROWS];
void scan_row2col(void)
{
  for (uint8_t i = 0; i < THIS_DEVICE_COLS; i++) {
    matrix_col_t col = read_col(i);
    for (uint8_t j = 0; j < THIS_DEVICE_ROWS; j++) {
      uint8_t bit =  (col >> j) & 1;
      if ( bit == 1) {
        matrix_row2col[j] |= (1 << i);
      } else {
        matrix_row2col[j] &= ~(1 << i);
      }
    }
  }
}
matrix_row_t get_row2col(uint8_t row)
{
  return matrix_row2col[row];
}

/* Returns status of switches(1:on, 0:off) */
matrix_col_t readRows(void)
{
  matrix_col_t col = 0;
  for (int i=0; i<THIS_DEVICE_ROWS; i++) {
    col |= ((nrf_gpio_pin_read(rowPins[i]) ? 0 : 1) << i);
  }
  return col;
}

void unselectCols(void)
{
  for(int i=0; i<THIS_DEVICE_COLS; i++) {
    nrf_gpio_pin_set(colPins[i]);
  }
}

void selectCol(uint8_t col)
{
    nrf_gpio_pin_clear(colPins[col]);
}

/* Returns status of switches(1:on, 0:off) */
matrix_row_t readCols(void)
{
  matrix_row_t row = 0;
  for (int i=0; i<THIS_DEVICE_COLS; i++) {
    row |= ((nrf_gpio_pin_read(colPins[i]) ? 0 : 1) << i);
  }
  return row;
}

/* Row pin configuration
 */
void unselectRows(void)
{
  for(int i=0; i<THIS_DEVICE_ROWS; i++) {
    nrf_gpio_pin_set(rowPins[i]);
  }
}

void selectRow(uint8_t row)
{
    nrf_gpio_pin_clear(rowPins[row]);
}

matrix_row_t read_row(uint8_t row)
{
#ifdef USE_I2C_IOEXPANDER
  return read_row_ioexpander(row);
#else
  selectRow(row);
  wait_us(0);
  matrix_row_t row_state = readCols();
  unselectRows();
  return row_state;
#endif
}

matrix_col_t read_col(uint8_t col)
{
  selectCol(col);
  wait_us(0);
  matrix_col_t col_state = readRows();
  unselectCols();
  return col_state;
}

void ble_nus_packetrcv_handler(ble_switch_state_t* buf, uint8_t len) {
  static uint8_t prev_recv_timing;
  int i=0;
  int32_t slave_time_est;
  if (buf[0].dat[0]==0xFF) {
    // master and slave synchronizing
    NRF_LOG_DEBUG("%d %d %d %d",timing, buf[0].dat[1], prev_recv_timing, ((int32_t)timing+buf[0].dat[1]-prev_recv_timing) % 0xFF);
    slave_time_est = (int32_t)buf[0].dat[1];
    timing=((int32_t)timing+slave_time_est-prev_recv_timing) % 0xFF;
    prev_recv_timing = timing;
    i=1;
  }
  for (; i<len; i++) {
    push_queue(&rcv_queue, buf[i]);
  }
}
