#include QMK_KEYBOARD_H
#include <process_unicode.h>
#include "keymap_jp.h"       // qmk_firmware-master/quantum/keymap_extras/keymap_jp.h 日本語キーボード設定用
#include <sendstring_jis.h>  // macro sendstring for jis keyboard マクロ文字列送信時に日本語キーボード設定での文字化け回避

enum custom_keycodes {
    EMOJI_DO = SAFE_RANGE,
	EMOJI_KA,
	EMOJI_BE,
	EMOJI_NN
};

const uint32_t PROGMEM unicode_map[]=
{
    0x1f914,//thinking face
    0x1F4A9,//pile of poo
    0x1F620,//angry face
    0x1F37A,//beer
	
    0x00000,//Dummy
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = 
    {
        {EMOJI_DO,EMOJI_KA,EMOJI_BE,EMOJI_NN},
        {X(0),X(1),X(2),X(3)}
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            
            case EMOJI_DO:
                SEND_STRING(":naruhodo11::naruhodo12::naruhodo13:"SS_LSFT("\n"));
                SEND_STRING(":naruhodo21::naruhodo22::naruhodo23:"SS_LSFT("\n"));
                SEND_STRING(":naruhodo31::naruhodo32::naruhodo33:"SS_LSFT("\n"));
                return false;
            case EMOJI_KA:
                SEND_STRING(":notargs11::notargs12::notargs13:"SS_LSFT("\n"));
                SEND_STRING(":notargs21::notargs22::notargs23:"SS_LSFT("\n"));
                SEND_STRING(":notargs31::notargs32::notargs33:"SS_LSFT("\n"));
                return false;
            case EMOJI_BE:
                SEND_STRING(":mikudayo_11::mikudayo_12::mikudayo_13:"SS_LSFT("\n"));
                SEND_STRING(":mikudayo_21::mikudayo_22::mikudayo_23:"SS_LSFT("\n"));
                SEND_STRING(":mikudayo_31::mikudayo_32::mikudayo_33:"SS_LSFT("\n"));
                return false;
            case EMOJI_NN:
                SEND_STRING(":notargs:");
                return false;
        }
    }
    return true;
};

void matrix_init_user(void) {
    set_unicode_input_mode(UC_WINC);
}

