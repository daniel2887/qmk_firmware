/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// TODO: Split up this file into multiple files: keymap, homerow mods

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keymap.h"
#include "tap_dance.h"
#include "rgb.h"
#include "oled.h"

enum unicode_names {
    DEGREE,
    ROUGHLY_EQ,
    LEQUALS,
    GEQUALS,
    MAYBE_EQ
};

const uint32_t unicode_map[] PROGMEM = {
    [DEGREE]  = 0x00B0,
    [ROUGHLY_EQ] = 0x2248,
    [LEQUALS]  = 0x2264,
    [GEQUALS]  = 0x2265,
    [MAYBE_EQ]  = 0x225F,
};

// Hacky but meh
// #include "daniel2887_keymap.h"
// Update: replaced that .h file with manually contructed mappings below

#define HOME_S LSFT_T(KC_S)
#define HOME_L LSFT_T(KC_L)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_split_3x6_3(
KC_TAB,      KC_Q,             KC_W,   KC_E,            KC_R,            KC_T,    /*|*/ KC_Y,   KC_U,               KC_I,    KC_O,   KC_P,    KC_BSPC,
MO(L_MOUSE), KC_A,             HOME_S, LT(L_SYMB,KC_D), LT(L_NAV,KC_F),  KC_G,    /*|*/ KC_H,   KC_J,               KC_K,    HOME_L, KC_SCLN, KC_QUOT,
KC_LSFT,     LT(L_MEDIA,KC_Z), KC_X,   KC_C,            KC_V,            KC_B,    /*|*/ KC_N,   KC_M,               KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
                                       KC_LGUI,         LALT_T(KC_APP),  KC_LCTL, /*|*/ KC_SPC, TD(TD_NAV_CW_TOGG), MO(L_FN)
          ),

    [L_GAME] = LAYOUT_split_3x6_3(
TD(TD_GAME_ESC),     KC_Q, KC_W, KC_E,    KC_R,                   KC_T,   /*|*/ KC_Y,   KC_U,         KC_I,    KC_O,   KC_P,    KC_BSPC,
LT(L_MEDIA,KC_LGUI), KC_A, KC_S, KC_D,    KC_F,                   KC_G,   /*|*/ KC_H,   KC_J,         KC_K,    KC_L,   KC_SCLN, TD(TD_GAME_ENTER),
KC_LSFT,             KC_Z, KC_X, KC_C,    KC_V,                   KC_B,   /*|*/ KC_N,   KC_M,         KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
                                 KC_LCTL, LT(L_GAME_NUM,KC_LALT), KC_SPC, /*|*/ KC_SPC, LT(L_NAV,KC_ENT), MO(L_FN)
          ),

    [L_NAV] = LAYOUT_split_3x6_3(
KC_NO,   KC_ESC,  KC_NO,   LCTL(LALT(KC_UP)), KC_NO,   LCTL(LALT(LSFT(KC_T))), /*|*/ KC_PGUP, KC_HOME, KC_UP,               KC_END,               KC_DEL, KC_BSPC,
KC_NO,   KC_NO,   KC_LSFT, KC_TRNS,           KC_NO,   KC_NO,                  /*|*/ KC_PGDN, KC_LEFT, KC_DOWN,             KC_RGHT,              KC_NO,  KC_NO,
KC_LSFT, KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,                  /*|*/ KC_NO,   KC_NO,   LCTL(LALT(KC_LEFT)), LCTL(LALT(KC_RIGHT)), KC_NO,  KC_NO,
                           KC_LGUI,           KC_LALT, KC_LCTL,                /*|*/ KC_BSPC, KC_NO,   KC_NO
          ),

    [L_SYMB] = LAYOUT_split_3x6_3(
KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_GRV,  KC_LBRC, KC_EXLM, KC_RBRC, KC_ASTR, KC_NO,
KC_NO,   KC_NO, KC_LSFT, KC_NO,   KC_TRNS, KC_NO,   /*|*/ KC_AMPR, KC_LPRN, KC_MINS, KC_RPRN, KC_DLR,  KC_CIRC,
KC_LSFT, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_PERC, KC_AT,   KC_EQL,  KC_HASH, KC_BSLS, KC_NO,
                         KC_LGUI, KC_LALT, KC_LCTL, /*|*/ KC_NO,   KC_NO,   MO(L_FN)
          ),

    [L_NUM] = LAYOUT_split_3x6_3(
KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_NO,  KC_7,  KC_8, KC_9, KC_ASTR, KC_NO,
KC_NO,   KC_NO, KC_LSFT, KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_NO,  KC_4,  KC_5, KC_6, KC_NO,   KC_NO,
KC_LSFT, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_DOT, KC_1,  KC_2, KC_3, KC_SLSH, KC_NO,
                         KC_LGUI, KC_LALT, KC_LCTL, /*|*/ KC_0,   KC_NO, KC_NO
          ),

    [L_MEDIA] = LAYOUT_split_3x6_3(
KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_MUTE, /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_VOLD, /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                       KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_NO, KC_NO, KC_NO
          ),

    [L_ARROWS] = LAYOUT_split_3x6_3(
KC_ESC, KC_NO, KC_NO,   KC_UP,   KC_NO,    KC_VOLU, /*|*/ KC_VOLU, KC_NO,   KC_UP,   KC_NO,    KC_NO, KC_NO,
KC_NO,  KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MUTE, /*|*/ KC_MUTE, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO,
KC_NO,  KC_NO, KC_NO,   KC_NO,   KC_NO,    KC_VOLD, /*|*/ KC_VOLD, KC_NO,   KC_NO,   KC_NO,    KC_NO, KC_NO,
                        KC_NO,   KC_NO,    KC_SPC,  /*|*/ KC_SPC,  KC_NO,   MO(L_FN)
          ),

    [L_FN] = LAYOUT_split_3x6_3(
KC_PSCR, RGB_HUI,  RGB_SAI, RGB_VAI, KC_NO,   KC_NO,   /*|*/ KC_NO,  KC_F7, KC_F8, KC_F9, KC_NO, KC_SLEP,
KC_NO,   RGB_RMOD, RGB_TOG, RGB_MOD, KC_NO,   KC_NO,   /*|*/ KC_F12, KC_F4, KC_F5, KC_F6, KC_NO, KC_NO,
KC_LSFT, RGB_HUD,  RGB_SAD, RGB_VAD, KC_NO,   KC_NO,   /*|*/ KC_F11, KC_F1, KC_F2, KC_F3, KC_NO, TD(TD_DEFAULT_LAYER),
                            KC_LGUI, KC_LALT, KC_LCTL, /*|*/ KC_F10, KC_NO, KC_NO
          ),

    [L_UNI] = LAYOUT_split_3x6_3(
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, KC_NO,      X(DEGREE),  KC_NO,       KC_NO,
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, KC_NO,      KC_NO,      KC_NO,       KC_NO,
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, X(LEQUALS), X(GEQUALS), X(MAYBE_EQ), KC_NO,
                     KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, KC_NO
          ),

    [L_GAME_NUM] = LAYOUT_split_3x6_3(
KC_ESC, KC_1,  KC_NO, KC_2,  KC_3,  KC_6,  /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO,  KC_NO, KC_NO, KC_NO, KC_4,  KC_7,  /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO,  KC_NO, KC_NO, KC_NO, KC_5,  KC_8,  /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                      KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, KC_NO
          ),

    [L_MOUSE] = LAYOUT_split_3x6_3(
KC_NO,   KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO,   /*|*/ KC_WH_U, KC_NO,   KC_MS_U, KC_NO,   KC_NO, KC_NO,
KC_NO,   KC_NO, KC_LSFT, KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO,
KC_LSFT, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                         KC_LGUI, KC_LALT, KC_LCTL, /*|*/ KC_BTN1, KC_BTN2, KC_BTN3
          )
};

void matrix_scan_user(void) {
	rgb_matrix_scan_user();
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return rgb_process_record_user(keycode, record);
}

void keyboard_post_init_user(void) {
	rgb_keyboard_post_init_user();
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
	return rgb_default_layer_state_set_user(state);
}

// This turns the following key press sequence...
// 1. LT(2, KC_A) Down
// 2. KC_L Down (the L key is also mapped to KC_RGHT on layer 2)
// 3. KC_L Up
// 4. LT(2, KC_A) Up
// ... into KC_RGHT instead of 'al' regardless of TAPPING_TERM duration.
// This helps when *quickly* typing a key on an upper layer.
//
// In my specific situation, this helps with F+Q (expected to generate Escape),
// a key combination which I tend to type very quickly. Without this feature,
// I would get 'fq'.
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case LT(L_NAV,KC_SPC):
		case LT(L_NAV,KC_F):
		case LT(L_SYMB,KC_D):
			// Immediately select the hold action when another key is tapped.
			return true;
		default:
			// Do not select the hold action when another key is tapped.
			return false;
	}
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            // Force the dual-role key press to be handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return true;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
		// This is to avoid a situation in which I want to type "CD-PHY"
		// (where D + K should yield '-'), but I actually get "CDdk" due to
		// auto-repeat of the letter D kicking in instead of a layer switch
		// due to the quick double tap of D in that word.
        case LT(L_SYMB,KC_D):
		// Similarly, this is to avoid a situation in which I want to type "df",
		// or any word ending with F, followed by enter or some navigation
		// key (which is on the layer triggered by F).
		case LT(L_NAV,KC_F):
        // Hopefully this works out ok...
		case HOME_S:
		case HOME_L:
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
		case HOME_S:
		case HOME_L:
        case LT(L_GAME_NUM,KC_LALT):
			return 150;
		// E is often used for interactions and is easy to double tap; make it a bit snappier.
        case TD(TD_GAME_2):
            return 175;
        case TD(TD_GAME_ESC):
            return 200;
		// Q is harder to reach and double tap; give it a bit more time.
        case TD(TD_GAME_1):
		// This is to address unintended triggering of the mouse/media layer when
		// typing words like "size" an rolling over "z" and "e". Increase tapping term
		// required to switch into the media layer.
		case LT(L_MEDIA,KC_Z):
            return 300;
        case TD(TD_DEFAULT_LAYER):
            return 1000;
        default:
            return TAPPING_TERM;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
	state = update_tri_layer_state(state, L_NAV, L_SYMB, L_NUM);
	return state;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_UNDS:
        case KC_MINS:
        case KC_LSFT:
        case KC_SLSH:
        case KC_BSLS:
        case KC_1 ... KC_0:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
