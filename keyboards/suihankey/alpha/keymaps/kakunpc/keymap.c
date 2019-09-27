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
    BASE,
    SKILL_1,
    SKILL_2,
    SKILL_3,
    UTILITY,
    SETTING,
    SATISFACTORY,
    SATISFACTORY_SETTING,
    TOHOU,
    TOHOU_SETTING,
};

enum my_keycodes {
  LOGO_TOG = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_MINUS, KC_Q, KC_W, KC_E, KC_QUOTE,
        KC_LSFT, KC_A, KC_S, KC_D, LT(UTILITY,KC_SPC),
        LT(SKILL_3,KC_SPC), LT(SKILL_2,KC_SPC), LT(SKILL_1,KC_SPC)),

	[SKILL_1] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,
        KC_F11, KC_Q, KC_W, KC_E, KC_F12,
        KC_LSFT, KC_A, KC_S, KC_D, KC_NO,
              KC_NO, KC_NO, KC_NO),

	[SKILL_2] = LAYOUT(
        LCTL(KC_1), LCTL(KC_2), LCTL(KC_3), LCTL(KC_4), LCTL(KC_5),
        LCTL(KC_MINUS), KC_Q, KC_W, KC_E, LCTL(KC_QUOTE),
        KC_LSFT, KC_A, KC_S, KC_D, KC_NO,
                    KC_NO, KC_NO, KC_NO),

	[SKILL_3] = LAYOUT(
        KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_F11, KC_F7, KC_F8, KC_F9, KC_F10,
        LCTL(KC_6), LCTL(KC_7), LCTL(KC_8), LCTL(KC_9), LCTL(KC_0),
                                            KC_NO, KC_NO, KC_NO),

	[UTILITY] = LAYOUT(
        LT(SETTING,KC_ESC), KC_Q, KC_W, KC_E, KC_B,
        KC_TAB, KC_A, KC_S, KC_D, KC_I,
        KC_Z,   KC_C, KC_O, KC_M, KC_P,
        LT(SKILL_3,KC_SPC), LT(SKILL_2,KC_SPC), LT(SKILL_1,KC_SPC)),

	[SETTING] = LAYOUT(
        KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
        KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
        DF(SATISFACTORY), DF(TOHOU), KC_NO, KC_NO, LOGO_TOG,
              RGB_MOD, RGB_RMOD, RGB_TOG),

	[SATISFACTORY] = LAYOUT(
        LT(SATISFACTORY_SETTING,KC_ESC), KC_Q, KC_W, KC_E, KC_R,
        KC_TAB, KC_A, KC_S, KC_D, KC_F,
        KC_LSFT,   KC_Z, KC_X, KC_C, KC_V,
                  KC_T, KC_SPC, KC_SPC),
	[SATISFACTORY_SETTING] = LAYOUT(
        KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
        KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
        DF(BASE), KC_NO, KC_NO, KC_NO, LOGO_TOG,
              RGB_MOD, RGB_RMOD, RGB_TOG),

	[TOHOU] = LAYOUT(
        LT(TOHOU_SETTING,KC_ESC), KC_NO, KC_UP, KC_NO, KC_NO,
        KC_LSFT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO,
        KC_Z,   KC_NO, KC_NO, KC_NO, KC_NO,
                  KC_C, KC_X, KC_LSFT ),
	[TOHOU_SETTING] = LAYOUT(
        KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
        KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
        DF(BASE), KC_NO, KC_NO, KC_NO, LOGO_TOG,
              RGB_MOD, RGB_RMOD, RGB_TOG),
};

bool useLogo = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOGO_TOG:
        if (record->event.pressed) {
            useLogo = !useLogo;
            }
            return false;

        default:
            return true;
    }
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
    if (useLogo) {
        render_logo();
        return;
    }

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
        case UTILITY:
            oled_write_P(PSTR("UTILITY\n"), false);
            break;
        case SETTING:
            oled_write_P(PSTR("SETTING\n"), false);
            break;
        case SATISFACTORY:
            oled_write_P(PSTR("SATISFACTORY\n"), false);
            break;
        case SATISFACTORY_SETTING:
            oled_write_P(PSTR("SATIS_SETTING\n"), false);
            break;
        case TOHOU:
            oled_write_P(PSTR("TOHOU\n"), false);
            break;
        case TOHOU_SETTING:
            oled_write_P(PSTR("TOHOU_SETTING\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    oled_write_P(IS_HOST_LED_ON(USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_HOST_LED_ON(USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_HOST_LED_ON(USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
    oled_write_P(PSTR("\n              "), false);
}
