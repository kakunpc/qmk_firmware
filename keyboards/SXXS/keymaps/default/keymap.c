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


int ledIds[] = {1,2,3,4,5,6,0};

int ledcolors[][3] = {
    {   0,   0, 255 },  // Start
    {   0,   0, 255 },  // BT-A
    {   0,   0, 255 },  // BT-B
    {   0,   0, 255 },  // BT-C
    {   0,   0, 255 },  // BT-D
    { 255,   0,   0 },  // FX-L
    { 255,   0,   0 },  // FX-R
};

int l_color[] = {   0,   0, 255 };
int r_color[] = { 255,   0,   0 };

static short l_time = 0;
static short r_time = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
        KC_D,    KC_F,  KC_J, KC_K,
        KC_C,    KC_M,  KC_ENT
    )
};

/* Rotary encoder settings */
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
      if(l_time == -1){
        setrgb(0,0,0 , (LED_TYPE *)&led[8]);
        rgblight_set();
        l_time = 50;
      }
    if (clockwise) {
      tap_code(KC_S);
    } else {
      tap_code(KC_A);
    }
  } else if (index == 1) {
      if(r_time == -1){
        setrgb(0,0,0 , (LED_TYPE *)&led[7]);
        rgblight_set();
        r_time = 50;
      }
    if (clockwise) {
      tap_code(KC_L);
    } else {
      tap_code(KC_SCLN);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int col = record->event.key.col;
    int row = record->event.key.row;
    int index =  ledIds[col + (row * 4)];
    if (record->event.pressed) {
        int r = ledcolors[index][0];
        int g = ledcolors[index][1];
        int b = ledcolors[index][2];

        setrgb( r, g, b, (LED_TYPE *)&led[index]);
    }
    else{
        setrgb(0,0,0 , (LED_TYPE *)&led[index]);
    }
    rgblight_set();;
    return true;
}

void matrix_scan_user(void) {
    if(r_time > 0){
        --r_time;
    }
    if( r_time == 0 ){
        setrgb(r_color[0], r_color[1], r_color[2], (LED_TYPE *)&led[7]);
        rgblight_set();
        r_time = -1;
        return;
    }

    if(l_time > 0){
        --l_time;
    }
    if( l_time == 0 ){
        setrgb(l_color[0], l_color[1], l_color[2], (LED_TYPE *)&led[8]);
        rgblight_set();
        l_time = -1;
        return;
    }
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  for(int i = 0; i < 9;++i){
    setrgb(0,0,0 , (LED_TYPE *)&led[i]);
  }
  setrgb(r_color[0], r_color[1], r_color[2], (LED_TYPE *)&led[7]);
  setrgb(l_color[0], l_color[1], l_color[2], (LED_TYPE *)&led[8]);
  rgblight_set();
}
