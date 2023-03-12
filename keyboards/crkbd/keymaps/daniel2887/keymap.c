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

#include QMK_KEYBOARD_H
#include <stdio.h>

#define L_BASE 0
#define L_GAME 1
#define L_NAV 2
#define L_SYMB 3
#define L_NUM 4
#define L_MEDIA 5
#define L_ARROWS 6
#define L_FN 7
#define L_UNI 8
#define L_GAME_NUM 9
#define L_MOUSE 10

// Tap Dance declarations
// This needs to be defined here as it's used inside the keymap header
// that gets included afterwards.
enum {
    TD_DEFAULT_LAYER = 0,
    TD_GAME_1,
	TD_GAME_2,
	TD_GAME_3,
	TD_GAME_4,
	TD_GAME_5,
	TD_GAME_ESC,
	TD_GAME_ENTER,
};

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
KC_TAB,      KC_Q,             KC_W,   KC_E,            KC_R,            KC_T,    /*|*/ KC_Y,   KC_U,              KC_I,    KC_O,   KC_P,    KC_BSPC,
MO(L_MOUSE), KC_A,             HOME_S, LT(L_SYMB,KC_D), LT(L_NAV,KC_F),  KC_G,    /*|*/ KC_H,   KC_J,              KC_K,    HOME_L, KC_SCLN, KC_QUOT,
KC_LSFT,     LT(L_MEDIA,KC_Z), KC_X,   KC_C,            KC_V,            KC_B,    /*|*/ KC_N,   KC_M,              KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
                                       KC_LGUI,         LALT_T(KC_APP),  KC_LCTL, /*|*/ KC_SPC, LT(L_NAV,CW_TOGG), MO(L_FN)
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

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_left()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case L_BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
		case L_GAME:
            oled_write_P(PSTR("Gaming\n"), false);
            break;
        case L_NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case L_SYMB:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
		case L_NUM:
            oled_write_P(PSTR("Numpad\n"), false);
            break;
		case L_MOUSE:
            oled_write_P(PSTR("Mouse\n"), false);
            break;
		case L_FN:
            oled_write_P(PSTR("F-keys\n"), false);
            break;
		case L_GAME_NUM:
            oled_write_P(PSTR("Gaming Nums\n"), false);
            break;
		case L_UNI:
            oled_write_P(PSTR("Unicode symbols\n"), false);
            break;
		case L_ARROWS:
            oled_write_P(PSTR("Arrows\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
		oled_write_ln_P(PSTR("\n"), false);
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE

// From https://www.reddit.com/r/MechanicalKeyboards/comments/ix65z0/looking_for_qmk_led_idle_timeout_info/
// Slightly modified by me
// Backlight timeout feature
#define RGB_TIMEOUT 10    // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static uint8_t old_rgb_value = -1;
static bool rgb_on = true;

void matrix_scan_user(void) {
		// idle_timer needs to be set one time
		if (idle_timer == 0)
			idle_timer = timer_read();

		if ((timer_elapsed(idle_timer) > 30000) && rgb_on) {
			halfmin_counter++;
			idle_timer = timer_read();
		}

		if ((halfmin_counter >= RGB_TIMEOUT * 2) && rgb_on) {
			rgblight_disable_noeeprom();
			rgb_on = false;
			halfmin_counter = 0;
		}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
#ifdef OLED_ENABLE
		set_keylog(keycode, record);
#endif // OLED_ENABLE

		if (rgb_on == false || old_rgb_value == -1) {
			if (old_rgb_value == -1)
				old_rgb_value = 1;

			old_rgb_value = 1;
			rgblight_enable_noeeprom();

			rgb_on = true;
		}
		idle_timer = timer_read();
		halfmin_counter = 0;
	}
	return true;
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

void td_default_layer(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        default_layer_set(1U << L_BASE);
    } else if (state->count == 2) {
        default_layer_set(1U << L_GAME);
    } else if (state->count == 3) {
        default_layer_set(1U << L_ARROWS);
    } else {
        reset_tap_dance(state);
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_DEFAULT_LAYER] = ACTION_TAP_DANCE_FN(td_default_layer),
    [TD_GAME_1] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_1),
	[TD_GAME_2] = ACTION_TAP_DANCE_DOUBLE(KC_E, KC_2),
	[TD_GAME_3] = ACTION_TAP_DANCE_DOUBLE(KC_R, KC_3),
	[TD_GAME_4] = ACTION_TAP_DANCE_DOUBLE(KC_F, KC_4),
	[TD_GAME_5] = ACTION_TAP_DANCE_DOUBLE(KC_V, KC_5),
	[TD_GAME_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
	[TD_GAME_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_ENTER),
};

layer_state_t layer_state_set_user(layer_state_t state) {
	state = update_tri_layer_state(state, L_NAV, L_SYMB, L_NUM);
	return state;
}

static void default_layer_rgb_set_normal(void) {
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	rgblight_sethsv_noeeprom(127, 0, 90);
}

static void default_layer_rgb_set_gaming(void) {
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	rgblight_sethsv_noeeprom(85, 255, 110);
}

static void default_layer_rgb_set_unknown(void) {
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	rgblight_sethsv_noeeprom(0, 0, 0);
}

void keyboard_post_init_user(void) {
	default_layer_rgb_set_normal();
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
	if (layer_state_cmp(state, L_GAME)) {
		default_layer_rgb_set_gaming();
	} else if (layer_state_cmp(state, L_BASE)) {
		default_layer_rgb_set_normal();
	} else {
		default_layer_rgb_set_unknown();
	}
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
