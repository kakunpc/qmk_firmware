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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
        KC_D, KC_F, KC_J, KC_K,
            KC_C,       KC_M,
                 KC_ENT
                )};

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
    return true;
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
