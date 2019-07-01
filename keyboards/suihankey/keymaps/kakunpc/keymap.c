/* Copyright 2019 kakunpc
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

enum layers{
    BASE = 0,
    SKILL_1,
    SKILL_2,
    SKILL_3
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT(
        KC_ESC, KC_Q, KC_W, KC_E, KC_BSLS,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TAB, KC_A, KC_S, KC_D, KC_I,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_Z,   KC_C, KC_O, KC_M, KC_P,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LT(SKILL_3,KC_R), LT(SKILL_2,KC_T), LT(SKILL_1,KC_SPC),      KC_NO, KC_NO, KC_NO),

	[SKILL_1] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_6, KC_7, KC_8, KC_9, KC_0,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_MINS, KC_EQL, KC_NO, KC_NO,              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
              RGB_HUI, RGB_HUD, KC_NO,              KC_NO, KC_NO, KC_NO, KC_NO),

	[SKILL_2] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_F11, KC_F12, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                    RGB_SAI, KC_NO, RGB_SAD,        KC_NO, KC_NO, KC_NO),

	[SKILL_3] = LAYOUT(
        LCTL(KC_1), LCTL(KC_2), LCTL(KC_3), LCTL(KC_4), LCTL(KC_5),                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LCTL(KC_6), LCTL(KC_7), LCTL(KC_8), LCTL(KC_9), LCTL(KC_0),                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LCTL(KC_MINS), LCTL(KC_EQL), KC_NO, RGB_MOD, RGB_RMOD,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_NO, RGB_VAI, RGB_VAD,               KC_NO, KC_NO, KC_NO)
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

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case BASE:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case SKILL_1:
      oled_write_P(PSTR("SKILL_1\n"), false);
      break;
    case SKILL_2:
      oled_write_P(PSTR("SKILL_2\n"), false);
      break;
    case SKILL_3:
      oled_write_P(PSTR("SKILL_3\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding 'n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  oled_write_P(IS_HOST_LED_ON(USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(IS_HOST_LED_ON(USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(IS_HOST_LED_ON(USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}
#endif
