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
#include "rgblight.h"
#include "rgblight_list.h"

#define ENCODER_WAIT 255

uint8_t ledIds[] = {1, 2, 3, 4, 5, 6, 0};

int ledcolors[][3] = {
    {HSV_BLUE},  // Start
    {HSV_BLUE},  // BT-B
    {HSV_BLUE},  // BT-C
    {HSV_BLUE},  // BT-D
    {HSV_BLUE},  // BT-A
    {HSV_RED},   // FX-L
    {HSV_RED},   // FX-R
};

int l_color[] = {HSV_BLUE};
int r_color[] = {HSV_RED};

static long l_time = 0;
static uint16_t l_keycode = KC_NO;
static long r_time = 0;
static uint16_t r_keycode = KC_NO;

enum layers{
    _BASE = 0,
    _COMMAND
};

enum custom_keycodes {
    NOTES_UP = SAFE_RANGE,
	NOTES_DOWN,
	TIMING_UP,
	TIMING_DOWN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
             KC_ENT, LT(_COMMAND,KC_KP_6),
        KC_D, KC_F, KC_J, KC_K,
            KC_C,       KC_M),
    /* Command */
    [_COMMAND] = LAYOUT(
             KC_NO, _______,
        NOTES_DOWN, NOTES_UP, TIMING_DOWN, TIMING_UP,
            KC_KP_8,    KC_KP_0)
};

/* Rotary encoder settings */
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        rgblight_sethsv_at(0, 0, 0, 8);
        l_time = ENCODER_WAIT;
        uint16_t new_code;
        if (clockwise) {
            new_code = KC_S;
        } else {
            new_code = KC_A;
        }
        if( new_code != l_keycode){
            unregister_code(l_keycode);
            l_keycode = new_code;
            register_code(l_keycode);
        }
    } else if (index == 1) {
            rgblight_sethsv_at(0, 0, 0, 7);
            r_time = ENCODER_WAIT;
        uint16_t new_code;
        if (clockwise) {
            new_code = KC_L;
        } else {
            new_code = KC_SCLN;
        }
        if( new_code != r_keycode){
            unregister_code(r_keycode);
            r_keycode = new_code;
            register_code(r_keycode);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if(biton32(layer_state) == _BASE){
        int col   = record->event.key.col;
        int row   = record->event.key.row;
        int index = ledIds[col + (row * 4)];
        if (record->event.pressed) {
            int h = ledcolors[index][0];
            int s = ledcolors[index][1];
            int v = ledcolors[index][2];
            rgblight_sethsv_at(h, s, v, index);
        } else {
            rgblight_sethsv_at(0, 0, 0, index);
        }
    }

    if (record->event.pressed) {
        switch(keycode) {        
            case NOTES_UP:
                register_code(KC_ENTER);
                register_code(KC_KP_9);
                wait_ms(25);
                unregister_code(KC_KP_9);
                unregister_code(KC_ENTER);
                return false;
            case NOTES_DOWN:
                register_code(KC_ENTER);
                register_code(KC_KP_3);
                wait_ms(25);
                unregister_code(KC_KP_3);
                unregister_code(KC_ENTER);
                return false;
            case TIMING_UP:
                register_code(KC_ENTER);
                register_code(KC_KP_8);
                wait_ms(25);
                unregister_code(KC_KP_8);
                unregister_code(KC_ENTER);
                return false;
            case TIMING_DOWN:
                register_code(KC_ENTER);
                register_code(KC_KP_2);
                wait_ms(25);
                unregister_code(KC_KP_2);
                unregister_code(KC_ENTER);
                return false;
        }
    }

    return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
      case _BASE:
            rgblight_sethsv_at(0, 0, 0, 0);
            rgblight_sethsv_at(0, 0, 0, 1);
            rgblight_sethsv_at(0, 0, 0, 2);
            rgblight_sethsv_at(0, 0, 0, 3);
            rgblight_sethsv_at(0, 0, 0, 4);
            rgblight_sethsv_at(0, 0, 0, 5);
            rgblight_sethsv_at(0, 0, 0, 6);
        break;
      case _COMMAND:
            rgblight_sethsv_at(0, 0, 0, 0);
            rgblight_sethsv_blue_at(1);
            rgblight_sethsv_red_at(2);
            rgblight_sethsv_blue_at(3);
            rgblight_sethsv_red_at(4);
            rgblight_sethsv_at(0, 0, 0, 5);
            rgblight_sethsv_at(0, 0, 0, 6);
        break;
    }

  return state;
}

void matrix_scan_user(void) {
    if (r_time > 0) {
        --r_time;
    }
    if (r_time == 0) {
        rgblight_sethsv_at(r_color[0], r_color[1], r_color[2], 7);
        r_time = -1;
        if(r_keycode != KC_NO ){
            unregister_code(r_keycode);
            r_keycode = KC_NO;
        }
    }

    if (l_time > 0) {
        --l_time;
    }
    if (l_time == 0) {
        rgblight_sethsv_at(l_color[0], l_color[1], l_color[2], 8);
        l_time = -1;
        if(l_keycode != KC_NO ){
            unregister_code(l_keycode);
            l_keycode = KC_NO;
        }
    }
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    for (int i = 0; i < 9; ++i) {
        rgblight_sethsv_at(0, 0, 0, i);
    }
    rgblight_sethsv_at(r_color[0], r_color[1], r_color[2], 7);
    rgblight_sethsv_at(l_color[0], l_color[1], l_color[2], 8);
}
