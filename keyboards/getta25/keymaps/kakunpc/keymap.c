#include QMK_KEYBOARD_H
#include <process_unicode.h>
#include "keymap_jp.h"

#ifdef OLED_DRIVER_ENABLE
static uint32_t        oled_timer = 0;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE,
  _LED
};



const uint32_t PROGMEM unicode_map[]=
{
    0x1F4A9,//pile of poo
    0x1F37A,//beer
    0x1f914,//thinking face
    0x1F620,//angry face
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
      //,-----------------------------------|
           X(0),X(1),X(2),X(3),
      //|--------+--------+--------+--------|
          KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
      //|--------+--------+--------+--------+--------|
            KC_P7,   KC_P8,   KC_P9,      LT(_LED,KC_NO),
      //|--------+--------+--------+--------+--------|
            KC_P4,   KC_P5,   KC_P6, KC_PPLS,  KC_NO,
      //|--------+--------+--------+--------+--------|
            KC_P1,   KC_P2,   KC_P3,           KC_NO,
      //|--------+--------+--------+--------+--------|
               KC_P0,       KC_PDOT, KC_PENT,  KC_NO
      //`--------------------------------------------'
  ),

  [_LED] = LAYOUT( /* Base */
      //,-----------------------------------|
          _______, _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, XXXXXXX, XXXXXXX, _______,
      //|--------+--------+--------+--------+--------|
          RGB_SAD, RGB_SAI, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
          RGB_HUD, RGB_HUI, XXXXXXX, RGB_TOG, _______,
      //|--------+--------+--------+--------+--------|
          RGB_VAD, RGB_VAI, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
          _______,          _______, RGB_MOD, RGB_RMOD
      //`--------------------------------------------'
  )
};

void matrix_init_user(void) {
    set_unicode_input_mode(UC_WINC);

}

//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _LED:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_range( 0, 0, 0, 0, 1);
      break;
    }
    rgblight_set_effect_range( 1, 8);
#endif
return state;
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
     #ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
     #endif
  }
  return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_layer_state(void) {
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("LED  "), layer_state_is(_LED));
    oled_write_P(PSTR("     "), false);
}

void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("NumL "), led_state.num_lock);
}

void render_layer_messages(void) {
    oled_write_P(PSTR("GETtA 25       For  Your Good Job. "), false);
}

void render_status(void) {
    /* Show Keyboard Layout  */
    render_layer_state();
    render_keylock_status(host_keyboard_led_state());
}

void oled_task_user(void) {
    static const char PROGMEM font_logo[] = {
        0x80,0x81,0x82,0x83,0x84,
        0xa0,0xa1,0xa2,0xa3,0xa4,
        0xc0,0xc1,0xc2,0xc3,0xc4,

        0x85,0x86,0x87,0x88,0x89,
        0xa5,0xa6,0xa7,0xa8,0xa9,
        0xc5,0xc6,0xc7,0xc8,0xc9,

        0x8a,0x8b,0x8c,0x8d,0x8e,
        0xaa,0xab,0xac,0xad,0xae,
        0xca,0xcb,0xcc,0xcd,0xce,0
        };
    oled_write_P(font_logo, false);

    render_status();  // Renders the current keyboard state (layer, lock)
}

#endif
