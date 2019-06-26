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
#include "lufa.h"

typedef struct {
  int Col;
  int Row;
} Position;

typedef struct {
  Position touchPos;
  int      time;
  bool     isActive;
} TouchData;

int count = 0;

static const int col = 4;
static const int row = 5;
TouchData touchData;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
          KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,                 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,\
          KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,                 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,\
          KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,                 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,\
                        KC_NO,  KC_NO,  KC_NO,                 KC_NO,  KC_NO,  KC_NO   \
  ),
};

Position ToPositon(int index) {
  Position result;
  result.Col = index / row;
  result.Row = index % row;
  return result;
}

int ToIndex(Position p) {
    return (p.Col * row) + p.Row;
    }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  int touchRow = record->event.key.col;
  int touchCol = record->event.key.row;
  if (record->event.pressed) {
    touchData.touchPos.Col = touchCol;
    touchData.touchPos.Row = touchRow;
    touchData.isActive     = true;
    touchData.time         = 0;
  }
  return true;
}

void matrix_init_user(void) {
  eeconfig_update_rgblight_default();
  rgblight_enable();
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
}

float func(int index, int touch, float t) {
  Position pos      = ToPositon(index);
  Position touchPos = ToPositon(touch);
  pos.Col -= touchPos.Col;
  pos.Row -= touchPos.Row;
  float d = sqrt(pos.Row * pos.Row + pos.Col * pos.Col) - t;
  if (d > 0.0) return 0.0f;
  float s = 0.2f;
  float r = d * s + 1.0f;
  if (r > 1.0f) r = 1.0f;
  if (r < 0.0f) r = 0.0f;
  return r;
}

void MainLoop(void) {
  if (touchData.isActive) {
    touchData.time++;
    if(touchData.time >100){
        touchData.isActive=false;
    }
  }

  int max = col * row;

  for (int i = 0; i < max; ++i) {
    float c = 0.0f;
    if (touchData.isActive) {
      c = func(i, ToIndex(touchData.touchPos), touchData.time / 10.0f);
    }
    led[i].r = c * 0;
    led[i].g = c * 112;
    led[i].b = c * 127;
  }

  rgblight_set();
}

void matrix_scan_user(void) {
  MainLoop();
}

void oled_task_user(void) {
  char s1[25];
  int index = ToIndex(touchData.touchPos);
  sprintf(s1, "IsActive:%s\n", touchData.isActive?"True":"False");
  oled_write(s1, false);
  memset(s1, 0, sizeof(s1));
  sprintf(s1, "Col:%d Row:%d\n", touchData.touchPos.Col, touchData.touchPos.Row);
  oled_write(s1, false);
  memset(s1, 0, sizeof(s1));
  sprintf(s1, "Time:%d\n", touchData.time);
  oled_write(s1, false);
  memset(s1, 0, sizeof(s1));
  sprintf(s1, "Index:%d", index);
  oled_write(s1, false);
  memset(s1, 0, sizeof(s1));
}

void led_set_user(uint8_t usb_led) {}

void keyboard_post_init_user(void) {}
