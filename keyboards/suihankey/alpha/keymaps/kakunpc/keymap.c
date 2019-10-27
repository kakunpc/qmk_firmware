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
    _BASE,
    _SKILL_1,
    _SKILL_2,
    _SKILL_3,
    _UTILITY,
    _SETTING,
    _SATISFACTORY,
    _SATISFACTORY_SETTING,
    _TOHOU,
    _TOHOU_SETTING,
    _MINECRAFT,
    _MINECRAFT_SETTING,
    _OW,
    _OW_SETTING,
};

enum my_keycodes {
  LOGO_TOG = SAFE_RANGE,
  DF_BASE,
  DF_SATISFACTORY,
  DF_TOHOU,
  DF_MINECRAFT,
  DF_OW
};

uint16_t default_layer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_MINUS, KC_Q, KC_W, KC_E, KC_QUOTE,
        KC_LSFT, KC_A, KC_S, KC_D, LT(_UTILITY,KC_SPC),
        LT(_SKILL_3,KC_SPC), LT(_SKILL_2,KC_SPC), LT(_SKILL_1,KC_SPC)),

	[_SKILL_1] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,
        KC_F11, KC_Q, KC_W, KC_E, KC_F12,
        KC_LSFT, KC_A, KC_S, KC_D, KC_NO,
              KC_NO, KC_NO, KC_NO),

	[_SKILL_2] = LAYOUT(
        LCTL(KC_1), LCTL(KC_2), LCTL(KC_3), LCTL(KC_4), LCTL(KC_5),
        LCTL(KC_MINUS), KC_Q, KC_W, KC_E, LCTL(KC_QUOTE),
        KC_LSFT, KC_A, KC_S, KC_D, KC_NO,
                    KC_NO, KC_NO, KC_NO),

	[_SKILL_3] = LAYOUT(
        KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_F11, KC_F7, KC_F8, KC_F9, KC_F10,
        LCTL(KC_6), LCTL(KC_7), LCTL(KC_8), LCTL(KC_9), LCTL(KC_0),
                                            KC_NO, KC_NO, KC_NO),

	[_UTILITY] = LAYOUT(
        LT(_SETTING,KC_ESC), KC_Q, KC_W, KC_E, KC_B,
        KC_TAB, KC_A, KC_S, KC_D, KC_I,
        KC_Z,   KC_C, KC_O, KC_M, KC_P,
        LT(_SKILL_3,KC_SPC), LT(_SKILL_2,KC_SPC), LT(_SKILL_1,KC_SPC)),

	[_SETTING] = LAYOUT(
        KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
        KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
        DF_SATISFACTORY, DF_TOHOU, DF_MINECRAFT, DF_OW, LOGO_TOG,
              RGB_MOD, RGB_RMOD, RGB_TOG),

	[_SATISFACTORY] = LAYOUT(
        LT(_SATISFACTORY_SETTING,KC_ESC), KC_Q, KC_W, KC_E, KC_R,
        KC_TAB, KC_A, KC_S, KC_D, KC_F,
        KC_LSFT,   KC_Z, KC_X, KC_C, KC_V,
                  KC_T, KC_SPC, KC_SPC),
	[_SATISFACTORY_SETTING] = LAYOUT(
        KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
        KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
        DF_BASE, KC_NO, KC_NO, KC_NO, LOGO_TOG,
              RGB_MOD, RGB_RMOD, RGB_TOG),

	[_TOHOU] = LAYOUT(
        LT(_TOHOU_SETTING,KC_ESC), KC_NO, KC_UP, KC_NO, KC_NO,
        KC_LSFT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO,
        KC_Z,   KC_NO, KC_NO, KC_NO, KC_NO,
                  KC_C, KC_X, KC_LSFT ),
	[_TOHOU_SETTING] = LAYOUT(
        KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
        KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
        DF_BASE, KC_NO, KC_NO, KC_NO, LOGO_TOG,
              RGB_MOD, RGB_RMOD, RGB_TOG),


	[_MINECRAFT] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F,
                   LT(_MINECRAFT_SETTING,KC_ESC), KC_SPC, KC_SPC),

	[_MINECRAFT_SETTING] = LAYOUT(
        KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
        KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
        DF_BASE, KC_NO, KC_NO, KC_NO, LOGO_TOG,
              RGB_MOD, RGB_RMOD, RGB_TOG),


	[_OW] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F,
                   LT(_OW_SETTING,KC_H), KC_C, KC_SPC),

	[_OW_SETTING] = LAYOUT(
        KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
        KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
        DF_BASE, KC_NO, KC_NO, KC_NO, LOGO_TOG,
              RGB_MOD, RGB_RMOD, RGB_TOG),
};

bool useLogo = false;

void persistent_default_layer_set(uint16_t value) {
    // eeconfig_update_default_layer(default_layer);
    default_layer_set(1UL << value);
    default_layer = value;
    // eeconfig_update_rgblight(rgblight_config.raw);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOGO_TOG:
        if (record->event.pressed) {
            useLogo = !useLogo;
            }
            return false;

  case DF_BASE:
        if (record->event.pressed) {
        persistent_default_layer_set(_BASE);
            }
            return false;
  case DF_SATISFACTORY:
        if (record->event.pressed) {
        persistent_default_layer_set(_SATISFACTORY);
            }
            return false;
  case DF_TOHOU:
        if (record->event.pressed) {
        persistent_default_layer_set(_TOHOU);
            }
            return false;
  case DF_MINECRAFT:
        if (record->event.pressed) {
        persistent_default_layer_set(_MINECRAFT);
            }
            return false;

        case DF_OW:
        if (record->event.pressed) {
        persistent_default_layer_set(_OW);
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
        case _BASE:
            switch (default_layer)
            {
            case _SATISFACTORY:
                oled_write_P(PSTR("SATISFACTORY\n"), false);
                break;
            case _TOHOU:
                oled_write_P(PSTR("TOHOU\n"), false);
                break;
            case _MINECRAFT:
                oled_write_P(PSTR("MINECRAFT\n"), false);
                break;
            case _OW:
                oled_write_P(PSTR("OVERWATCH\n"), false);
                break;
            default:
                oled_write_P(PSTR("Default\n"), false);
                break;
            }
            break;
        case _SKILL_1:
            oled_write_P(PSTR("SKILL_1\n"), false);
            break;
        case _SKILL_2:
            oled_write_P(PSTR("SKILL_2\n"), false);
            break;
        case _SKILL_3:
            oled_write_P(PSTR("SKILL_3\n"), false);
            break;
        case _UTILITY:
            oled_write_P(PSTR("UTILITY\n"), false);
            break;
        case _SETTING:
            oled_write_P(PSTR("SETTING\n"), false);
            break;
        case _SATISFACTORY_SETTING:
            oled_write_P(PSTR("SATIS_SETTING\n"), false);
            break;
        case _TOHOU_SETTING:
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
