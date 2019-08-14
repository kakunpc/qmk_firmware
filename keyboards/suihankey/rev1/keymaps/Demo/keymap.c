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

#include <stdio.h>
#include <math.h>


enum layers{
    BASE,
    SKILL_1,
    SKILL_2,
    SKILL_3,
    SETTING
};

enum my_keycodes {
  LOGO_TOG = SAFE_RANGE,
  SK_1_1,
  SK_1_2,
  SK_1_3,
  SK_1_4,
  SK_1_5,
  SK_1_6,
  SK_2_1,
  SK_2_2,
  SK_2_3,
  SK_2_4,
  SK_2_5,
  SK_2_6,
  SK_3_1,
  SK_3_2,
  SK_3_3,
  SK_3_4,
  SK_3_5,
  SK_3_6,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT(
        LT(SETTING,KC_ESC), KC_Q, KC_W, KC_E, KC_R,
        KC_TAB, KC_A, KC_S, KC_D, KC_F,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V,
             MO(SKILL_3), MO(SKILL_2), MO(SKILL_1)),

	[SKILL_1] = LAYOUT(
        KC_NO, SK_1_1, SK_1_2, SK_1_3, KC_NO,
        KC_NO, SK_1_4, SK_1_5, SK_1_6, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
              KC_NO, KC_NO, KC_TRNS),

	[SKILL_2] = LAYOUT(
        KC_NO, SK_2_1, SK_2_2, SK_2_3, KC_NO,
        KC_NO, SK_2_4, SK_2_5, SK_2_6, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                    KC_NO, KC_TRNS, KC_NO),

	[SKILL_3] = LAYOUT(
        KC_NO, SK_3_1, SK_3_2, SK_3_3, KC_NO,
        KC_NO, SK_3_4, SK_3_5, SK_3_6, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_TRNS, KC_NO, KC_NO),
	[SETTING] = LAYOUT(
        KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
        KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, LOGO_TOG,
              RGB_MOD, RGB_RMOD, RGB_TOG),
};

bool useLogo = false;
uint16_t code;
int logoLimit = 1000;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOGO_TOG:
        if (record->event.pressed) {
            useLogo = !useLogo;
            }
            return false;

        default:
            if (record->event.pressed &&
                keycode != KC_NO &&
                keycode != KC_TRNS &&
                keycode != MO(SKILL_1) &&
                keycode != MO(SKILL_2) &&
                keycode != MO(SKILL_3)) {
                code = keycode;
            }else if(code == keycode) {
                code = 0;
            }
            return true;
    }
}

void matrix_init_user(void) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 5);
}

void matrix_scan_user(void) {
    if(logoLimit > 0)
    {
        --logoLimit;
    }
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

char* KeycodeToChar(uint16_t keycode) {
    switch (keycode) {
        case KC_Q:
            return "Q";
        case KC_W:
            return "W";
        case KC_E:
            return "E";
        case KC_R:
            return "R";
        case KC_TAB:
            return "TAB";
        case KC_A:
            return "A";
        case KC_S:
            return "S";
        case KC_D:
            return "D";
        case KC_F:
            return "F";
        case KC_LSFT:
            return "SHIFT";
        case KC_Z:
            return "Z";
        case KC_X:
            return "X";
        case KC_C:
            return "C";
        case KC_V:
            return "V";
        case LT(SETTING, KC_ESC):
            return "ESC";
        case KC_TRNS:
        case KC_NO:
            return "";
        case SK_1_1:
            return "Fire";
        case SK_1_2:
            return "Ice Storm";
        case SK_1_3:
            return "Diamond Cute";
        case SK_1_4:
            return "Braindamd";
        case SK_1_5:
            return "Jugemu";
        case SK_1_6:
            return "Payoen";
        case SK_2_1:
            return "Accelerator";
        case SK_2_2:
            return "Flame";
        case SK_2_3:
            return "Cycloir";
        case SK_2_4:
            return "Actina";
        case SK_2_5:
            return "Fairy Fair";
        case SK_2_6:
            return "Payoen";
        case SK_3_1:
            return "Solved";
        case SK_3_2:
            return "Sign";
        case SK_3_3:
            return "Cosine";
        case SK_3_4:
            return "Tangent";
        case SK_3_5:
            return "Integral";
        case SK_3_6:
            return "Permeation";
        default:
            return "?";
    }
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    default:
        rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 5);
        break;
    case SKILL_1:
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
    case SKILL_2:
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
    case SKILL_3:
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
    }
  return state;
}

void oled_task_user(void) {
    if (useLogo || logoLimit > 0) {
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
        case SETTING:
            oled_write_P(PSTR("SETTING\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    oled_write_P(IS_HOST_LED_ON(USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_HOST_LED_ON(USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_HOST_LED_ON(USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
    char s1[25];
    sprintf(s1, "Last: %s", KeycodeToChar(code));
    oled_write(s1, false);
    oled_write_P(PSTR("\n              "), false);
}
