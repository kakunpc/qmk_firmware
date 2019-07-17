#ifndef MASTER_CONFIG_H_
#define MASTER_CONFIG_H_

#include "custom_board.h"

#define THIS_DEVICE_ROWS 6
#define THIS_DEVICE_COLS 6

#define MATRIX_ROW_PINS {  PIN7,  PIN8,  PIN9, PIN10, PIN11, PIN12 }
#define MATRIX_COL_PINS { PIN20, PIN19, PIN18, PIN17, PIN16, PIN15 }
#define IS_LEFT_HAND  true
#define ENABLE_STARTUP_ADV_NOLIST

#define BLE_NUS_MIN_INTERVAL 8.5
#define BLE_NUS_MAX_INTERVAL 8.5

#endif /* MASTER_CONFIG_H_ */
