/* Copyright 2018 takashiski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,KC_ either version 2 of the License,KC_ or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,KC_
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not,KC_ see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "hecomi.h"
#include "rgblight_list.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

//R1:7 + 8 = 15
//R2:7 + 8 = 15
//R3:6 + 7 = 13
//R4:6 + 8 = 14
//R5:6 + 6 = 12
//total : 69 keys
//
enum layers{
	DF,
	LW,
	FN
};


#define KC_FN MO(FN)
#define KC_LW MO(LW)
#define KC_SFT(XXX) LSFT(XXX)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[DF]=LAYOUT(\
			KC_ESC,KC_GRV,KC_1,KC_2,KC_3,KC_4,KC_5,                  KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_BSPC,\
			KC_TAB  ,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,                 KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_BSLS,\
			KC_LCTRL ,KC_A,KC_S,KC_D,KC_F,KC_G,                     KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_ENT,\
			KC_LSFT   ,KC_Z,KC_X,KC_C,KC_V,KC_B,               KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_DEL,\
			KC_LGUI,KC_NO,KC_LALT,KC_LW,KC_FN,KC_SPC,  KC_SPC,KC_FN,KC_LEFT,KC_UP,KC_DOWN,KC_RIGHT\
			),
	[LW]=LAYOUT(\
			KC_NO,KC_NO,RGB_VAD,RGB_VAI,RGB_HUI,RGB_HUD,KC_TRNS,                  RGB_MOD,RGB_RMOD,KC_TRNS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,\
			KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                 KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,\
			KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,                     KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,\
			KC_NO   ,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,               KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,\
			KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,  KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO\
			),
	[FN]=LAYOUT(\
			KC_ESC,KC_GRV,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,                  KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_BSPC,\
			KC_TAB  ,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,                 KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_BSLS,\
			KC_LCTRL ,KC_A,KC_S,KC_D,KC_F,KC_G,                     KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_ENT,\
			KC_LSFT   ,KC_Z,KC_X,KC_C,KC_V,KC_B,               KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_DEL,\
			KC_LGUI,KC_NO,KC_LALT,KC_MHEN,KC_NO,KC_SPC,  KC_SPC,KC_NO,KC_HOME,KC_PGUP,KC_PGDOWN,KC_END\
			),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_sethsv_blue(); // sets the color to teal/cyan without saving
  // 6yrgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}

/*
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case 1: // LW
		rgblight_sethsv_green();
        break;
    case 2: // FN
		rgblight_sethsv_red();
        break;
    default:
		rgblight_sethsv_blue();
        break;
    }
  return state;
}
*/