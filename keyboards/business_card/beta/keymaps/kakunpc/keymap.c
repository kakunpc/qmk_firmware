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
#include "rgblight_list.h"
#include "oled_driver.h"

void UpdateText(char *text);

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { HOME = SAFE_RANGE, NAME, ADDRESS, SKILL, SOCIAL, ABOUT, RANDOM };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                 NAME, ADDRESS, SKILL, SOCIAL, ABOUT, RANDOM),
};

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

static const int col = 3;
static const int row = 2;
TouchData        touchData;
int              type        = HOME;
int              timer       = 0;
bool             randomState = false;
int              randomTimer = 0;
char             ledText[60];
char             ledView[60];
int              ledViewCount = 0;
int              ledMaxCount  = 0;
int              textTimer    = 0;
int              randomR      = 0;
int              randomG      = 122;
int              randomB      = 127;
int                 HomeMessageTimer = 0;

Position ToPositon(int index) {
  Position result;
  result.Col = index / row;
  result.Row = index % row;
  return result;
}

int ToIndex(Position p) { return (p.Col * row) + p.Row; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  int touchRow = row - 1 - record->event.key.col;
  int touchCol = col - 1 - record->event.key.row;
  if (record->event.pressed) {
    touchData.touchPos.Col = touchCol;
    touchData.touchPos.Row = touchRow;
    touchData.isActive     = true;
    touchData.time         = 0;
  }

  switch (keycode) {
    case NAME:
      if (record->event.pressed) {
        type = NAME;
        SEND_STRING("1");
        UpdateText("NAME\nkakunpc");
        randomState = false;
      }
      break;
    case ADDRESS:
      if (record->event.pressed) {
        type = ADDRESS;
        SEND_STRING("2");
        UpdateText("ADDRESS\nDUMMY!!!");
        randomState = false;
      }
      break;
    case SKILL:
      if (record->event.pressed) {
        type = SKILL;
        SEND_STRING("3");
        UpdateText("SKILL\nProgrammer.\nUnity and C#.");
        randomState = false;
      }
      break;
    case SOCIAL:
      if (record->event.pressed) {
        type = SOCIAL;
        SEND_STRING("4");
        UpdateText("SOCIAL\nTwitter:kakunpc\nGithub:kakunpc");
        randomState = false;
      }
      break;
    case ABOUT:
      if (record->event.pressed) {
        type = ABOUT;
        SEND_STRING("5");
        UpdateText("ABOUT\nBusiness Card Beta\ndesigned by kakunpc.");
        randomState = false;
      }
      break;
    case RANDOM:
      if (record->event.pressed) {
        type = RANDOM;
        SEND_STRING("6");
        UpdateText("Random Color.");
        randomR     = rand() % 255;
        randomG     = rand() % 255;
        randomB     = rand() % 255;
        randomState = false;
      }
      break;

    case HOME:
    default:
      if (record->event.pressed) {
        type = HOME;
      }
      break;
  }
  timer = 10000;
  return true;
}

void UpdateText(char *text) {
  sprintf(ledText, "%s", text);
  memset(ledView, '\0', sizeof(ledView));
  ledViewCount = 0;
  ledMaxCount  = sizeof(ledText);
  textTimer    = 0;
}

void ChangeHome(void) {
  randomState = true;
  type        = HOME;
  HomeMessageTimer = 0;
  UpdateText("Press the key\n to get information.");
}

void matrix_init_user(void) {
  eeconfig_update_rgblight_default();
  rgblight_enable();
  rgblight_sethsv_white();
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  ChangeHome();
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
  if (type != HOME) {
    timer--;
    if (timer < 0) {
      timer = 0;
      ChangeHome();
    }
  }
  else{
      HomeMessageTimer++;
      if(HomeMessageTimer > 30000){
          HomeMessageTimer =0;
          ChangeHome();
      }
  }

  if (randomState) {
    randomTimer--;
    if (randomTimer < 0) {
      int      index         = rand() % (col * row);
      Position p             = ToPositon(index);
      touchData.touchPos.Col = p.Col;
      touchData.touchPos.Row = p.Row;
      touchData.isActive     = true;
      touchData.time         = 0;
      randomR                = rand() % 255;
      randomG                = rand() % 255;
      randomB                = rand() % 255;
      randomTimer            = 600;
    }
  }

  if (touchData.isActive) {
    touchData.time++;
    if (touchData.time > 1000) {
      touchData.isActive = false;
    }
  }

  int max = col * row;

  for (int i = 0; i < max; ++i) {
    float c = 0.0f;
    if (touchData.isActive) {
      c = func(i, ToIndex(touchData.touchPos), touchData.time / 60.0f);
    }
    led[i].r = c * randomR;
    led[i].g = c * randomG;
    led[i].b = c * randomB;
  }

  rgblight_set();

  if (ledViewCount < ledMaxCount) {
    textTimer++;
    if (textTimer > 30) {
      textTimer = 0;
      memcpy(ledView, ledText, ledViewCount);
      ledViewCount++;
      dprintf("%s\n", ledView);
    }
  }
}

void matrix_scan_user(void) {
  MainLoop();
}

void oled_task_user(void) {
  oled_write(ledView, false);
}

void led_set_user(uint8_t usb_led) {}

void keyboard_post_init_user(void) {}
