/* Copyright 2020 kakunpc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
        KC_D,    KC_F,  KC_J, KC_K,
        KC_C,    KC_M,  KC_ENT
    )
};

/* Rotary encoder settings */
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_S);
    } else {
      tap_code(KC_A);
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
      tap_code(KC_L);
    } else {
      tap_code(KC_SCLN);
    }
  }
}

int ledIds[] = {1,2,3,4,5,6,0};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int col = record->event.key.col;
    int row = record->event.key.row;
    int index =  ledIds[col + (row * 4)];
    if (record->event.pressed) {
        sethsv(HSV_WHITE, (LED_TYPE *)&led[index]);
    }
    else{
        setrgb(0,0,0 , (LED_TYPE *)&led[index]);
    }
    rgblight_set();

    return true;
}


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
  for(int i = 0; i < 7;++i){
    int id = ledIds[i];
    setrgb(0,0,0 , (LED_TYPE *)&led[id]);
  }
  // setrgb(150,150,150, (LED_TYPE *)&led[7]);
  // setrgb(150,150,150, (LED_TYPE *)&led[8]);
  rgblight_set();
  //rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}
