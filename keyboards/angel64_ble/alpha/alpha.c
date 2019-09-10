#include "matrix.h"
#include "quantum.h"
#include "nrf.h"
#include "app_ble_func.h"

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

void matrix_init_user() {
//  rgblight_mode_noeeprom(35);
//  set_usb_enabled(true);
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
      iota_gfx_init(!IS_LEFT_HAND);   // turns on the display
  #endif
}

