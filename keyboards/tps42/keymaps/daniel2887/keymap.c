/* Copyright 2021 Christoph Rehmann (crehmann)
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
#include "keymap.h"
#include "tap_dance.h"

#ifdef PS2_MOUSE_ENABLE
    #include "ps2_mouse.h"
    #include "ps2.h"
#endif

#if 0
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
#endif

#define UC_DEGREE 0x00B0
#define UC_ROUGHLY_EQ 0x2248
#define UC_LEQUALS 0x2264
#define UC_GEQUALS 0x2265
#define UC_MAYBE_EQ 0x225F

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT(
KC_TAB,      KC_Q,             KC_W,   KC_E,            KC_R,            KC_T,    /*|*/ KC_Y,   KC_U,               KC_I,    KC_O,   KC_P,    KC_BSPC,
MO(L_MOUSE), KC_A,             HOME_S, LT(L_SYMB,KC_D), LT(L_NAV,KC_F),  KC_G,    /*|*/ KC_H,   KC_J,               KC_K,    HOME_L, KC_SCLN, KC_QUOT,
KC_LSFT,     LT(L_MEDIA,KC_Z), KC_X,   KC_C,            KC_V,            KC_B,    /*|*/ KC_N,   KC_M,               KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
                                       KC_LGUI,         LALT_T(KC_APP),  KC_LCTL, /*|*/ KC_SPC, TD(TD_NAV_CW_TOGG), MO(L_FN)
          ),

    [L_GAME] = LAYOUT(
TD(TD_GAME_ESC),     KC_Q, KC_W, KC_E,    KC_R,                   KC_T,   /*|*/ KC_Y,   KC_U,         KC_I,    KC_O,   KC_P,    KC_BSPC,
LT(L_MEDIA,KC_LGUI), KC_A, KC_S, KC_D,    KC_F,                   KC_G,   /*|*/ KC_H,   KC_J,         KC_K,    KC_L,   KC_SCLN, TD(TD_GAME_ENTER),
KC_LSFT,             KC_Z, KC_X, KC_C,    KC_V,                   KC_B,   /*|*/ KC_N,   KC_M,         KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
                                 KC_LCTL, LT(L_GAME_NUM,KC_LALT), KC_SPC, /*|*/ KC_SPC, LT(L_NAV,KC_ENT), MO(L_FN)
          ),

    [L_NAV] = LAYOUT(
KC_NO,   KC_ESC,  KC_NO,   LCTL(LALT(KC_UP)), KC_NO,   LCTL(LALT(LSFT(KC_T))), /*|*/ KC_PGUP, KC_HOME, KC_UP,               KC_END,               KC_DEL, KC_BSPC,
KC_NO,   KC_NO,   KC_LSFT, KC_TRNS,           KC_NO,   KC_NO,                  /*|*/ KC_PGDN, KC_LEFT, KC_DOWN,             KC_RGHT,              KC_NO,  KC_NO,
KC_LSFT, KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,                  /*|*/ KC_NO,   KC_NO,   LCTL(LALT(KC_LEFT)), LCTL(LALT(KC_RIGHT)), KC_NO,  KC_NO,
                           KC_LGUI,           KC_LALT, KC_LCTL,                /*|*/ KC_BSPC, KC_NO,   KC_NO
          ),

    [L_SYMB] = LAYOUT(
KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_GRV,  KC_LBRC, KC_EXLM, KC_RBRC, KC_ASTR, KC_NO,
KC_NO,   KC_NO, KC_LSFT, KC_NO,   KC_TRNS, KC_NO,   /*|*/ KC_AMPR, KC_LPRN, KC_MINS, KC_RPRN, KC_DLR,  KC_CIRC,
KC_LSFT, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_PERC, KC_AT,   KC_EQL,  KC_HASH, KC_BSLS, KC_NO,
                         KC_LGUI, KC_LALT, KC_LCTL, /*|*/ KC_NO,   KC_NO,   MO(L_FN)
          ),

    [L_NUM] = LAYOUT(
KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_NO,  KC_7,  KC_8, KC_9, KC_ASTR, KC_NO,
KC_NO,   KC_NO, KC_LSFT, KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_NO,  KC_4,  KC_5, KC_6, KC_NO,   KC_NO,
KC_LSFT, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_DOT, KC_1,  KC_2, KC_3, KC_SLSH, KC_NO,
                         KC_LGUI, KC_LALT, KC_LCTL, /*|*/ KC_0,   KC_NO, KC_NO
          ),

    [L_MEDIA] = LAYOUT(
KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_MUTE, /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_VOLD, /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                       KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_NO, KC_NO, KC_NO
          ),

    [L_ARROWS] = LAYOUT(
KC_ESC, KC_NO, KC_NO,   KC_UP,   KC_NO,    KC_VOLU, /*|*/ KC_VOLU, KC_NO,   KC_UP,   KC_NO,    KC_NO, KC_NO,
KC_NO,  KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MUTE, /*|*/ KC_MUTE, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO,
KC_NO,  KC_NO, KC_NO,   KC_NO,   KC_NO,    KC_VOLD, /*|*/ KC_VOLD, KC_NO,   KC_NO,   KC_NO,    KC_NO, KC_NO,
                        KC_NO,   KC_NO,    KC_SPC,  /*|*/ KC_SPC,  KC_NO,   MO(L_FN)
          ),

    [L_FN] = LAYOUT(
KC_PSCR, KC_NO, KC_NO, KC_NO,      KC_NO,   KC_NO,   /*|*/ KC_NO,  KC_F7, KC_F8, KC_F9, KC_NO, KC_SLEP,
KC_NO,   KC_NO, KC_NO, MO(L_SYMB), KC_NO,   KC_NO,   /*|*/ KC_F12, KC_F4, KC_F5, KC_F6, KC_NO, QK_BOOT,
KC_LSFT, KC_NO, KC_NO, KC_NO,      KC_NO,   KC_NO,   /*|*/ KC_F11, KC_F1, KC_F2, KC_F3, KC_NO, TD(TD_DEFAULT_LAYER),
                       KC_LGUI,    KC_LALT, KC_LCTL, /*|*/ KC_F10, KC_NO, KC_NO
          ),

    [L_UNI] = LAYOUT(
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, KC_NO,             UC(UC_DEGREE),  KC_NO,           KC_NO,
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, UC(UC_ROUGHLY_EQ), KC_NO,          KC_NO,           KC_NO,
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, UC(UC_LEQUALS),    UC(UC_GEQUALS), UC(UC_MAYBE_EQ), KC_NO,
                     KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, KC_NO
          ),

    [L_GAME_NUM] = LAYOUT(
KC_ESC, KC_1,  KC_NO, KC_2,  KC_3,  KC_6,  /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO,  KC_NO, KC_NO, KC_NO, KC_4,  KC_7,  /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO,  KC_NO, KC_NO, KC_NO, KC_5,  KC_8,  /*|*/ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                      KC_NO, KC_NO, KC_NO, /*|*/ KC_NO, KC_NO, KC_NO
          ),

    [L_MOUSE] = LAYOUT(
#if defined PS2_MOUSE_ENABLE
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /*|*/ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, /*|*/ KC_BTN5, KC_BTN4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /*|*/ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                           KC_LGUI, KC_LALT, KC_LCTL, /*|*/ KC_BTN1, KC_BTN2, KC_BTN3
#else
KC_NO,   KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO,   /*|*/ KC_WH_U, KC_NO,   KC_MS_U, KC_NO,   KC_NO, KC_NO,
KC_NO,   KC_NO, KC_LSFT, KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO,
KC_LSFT, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   /*|*/ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                         KC_LGUI, KC_LALT, KC_LCTL, /*|*/ KC_BTN1, KC_BTN2, KC_BTN3
#endif // defined PS2_MOUSE_ENABLE
          )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, L_NAV, L_SYMB, L_NUM);
    state = update_tri_layer_state(state, L_SYMB, L_FN, L_UNI);
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
        // Don't immediately disable CW on this TD;
        // let the TD function (in tap_dance.c) toggle CW off/on
        case TD(TD_NAV_CW_TOGG):
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// Borrowed from keyboard pierce, keymap durken1
#if defined AUTO_BUTTONS && defined PS2_MOUSE_ENABLE

static uint16_t auto_buttons_timer;
extern int tp_buttons; // mousekey button state set in action.c and used in ps2_mouse.c

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    if (auto_buttons_timer) {
        auto_buttons_timer = timer_read();
    } else {
        if (!tp_buttons) {
            layer_on(L_MOUSE);
            auto_buttons_timer = timer_read();
        }
    }
}

void matrix_scan_user(void) {
    if (auto_buttons_timer && (timer_elapsed(auto_buttons_timer) > AUTO_BUTTONS_TIMEOUT)) {
        if (!tp_buttons) {
            layer_off(L_MOUSE);
            auto_buttons_timer = 0;
        }
    }
}

#endif // defined AUTO_BUTTONS && defined PS2_MOUSE_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#if defined AUTO_BUTTONS && defined PS2_MOUSE_ENABLE
    if (keycode != KC_BTN1 && keycode != KC_BTN2 && keycode != KC_BTN3) {
        // Some non-mouse key changed state; turn off mouse layer and reset the auto buttons timer
        layer_off(L_MOUSE);
        auto_buttons_timer = 0;
    }
#endif // defined AUTO_BUTTONS && defined PS2_MOUSE_ENABLE
    return true;
}

#ifdef PS2_MOUSE_ENABLE
static void ps2_mouse_normal_movement(void) {
    // set TrackPoint sensitivity
    PS2_MOUSE_SEND(0xE2, "tpsens: 0xE2");
    PS2_MOUSE_SEND(0x81, "tpsens: 0x81");
    PS2_MOUSE_SEND(0x4A, "tpsens: 0x4A");
    PS2_MOUSE_SEND(0x96, "tpsens: 0x96"); // Default = 0x80

    // set TrackPoint Negative Inertia factor
    PS2_MOUSE_SEND(0xE2, "tpnegin: 0xE2");
    PS2_MOUSE_SEND(0x81, "tpnegin: 0x81");
    PS2_MOUSE_SEND(0x4D, "tpnegin: 0x4D");
    PS2_MOUSE_SEND(0x04, "tpnegin: 0x04"); // Default = 0x06

    // set TrackPoint speed
    // (transfer function upper plateau speed)
    PS2_MOUSE_SEND(0xE2, "tpsp: 0xE2");
    PS2_MOUSE_SEND(0x81, "tpsp: 0x81");
    PS2_MOUSE_SEND(0x60, "tpsp: 0x60");
    PS2_MOUSE_SEND(0xFF, "tpsp: 0xFF"); // Default = 0x61
}

static void ps2_mouse_scroll_movement(void) {
    // set TrackPoint sensitivity
    PS2_MOUSE_SEND(0xE2, "tpsens: 0xE2");
    PS2_MOUSE_SEND(0x81, "tpsens: 0x81");
    PS2_MOUSE_SEND(0x4A, "tpsens: 0x4A");
    PS2_MOUSE_SEND(0x30, "tpsens: 0x30"); // Default = 0x80

    // set TrackPoint Negative Inertia factor
    PS2_MOUSE_SEND(0xE2, "tpnegin: 0xE2");
    PS2_MOUSE_SEND(0x81, "tpnegin: 0x81");
    PS2_MOUSE_SEND(0x4D, "tpnegin: 0x4D");
    PS2_MOUSE_SEND(0x06, "tpnegin: 0x06"); // Default = 0x06

    // set TrackPoint speed
    // (transfer function upper plateau speed)
    PS2_MOUSE_SEND(0xE2, "tpsp: 0xE2");
    PS2_MOUSE_SEND(0x81, "tpsp: 0x81");
    PS2_MOUSE_SEND(0x60, "tpsp: 0x60");
    PS2_MOUSE_SEND(0x61, "tpsp: 0x61"); // Default = 0x61
}

static ps2_mouse_scroll_state_t cur_scroll_state = SCROLL_NONE;
void ps2_mouse_scroll_user(ps2_mouse_scroll_state_t scroll_state) {
    if (cur_scroll_state == SCROLL_NONE && scroll_state == SCROLL_SENT) {
        // Starting scrolling
        ps2_mouse_scroll_movement();
    } else if (cur_scroll_state == SCROLL_SENT && scroll_state == SCROLL_NONE) {
        // Stopping scrolling
        ps2_mouse_normal_movement();
    }
    cur_scroll_state = scroll_state;
}

void ps2_mouse_init_user() {
    uint8_t rcv;

    // see p24 https://blogs.epfl.ch/icenet/documents/Ykt3Eext.pdf
    ps2_mouse_normal_movement();

    // inquire pts status
    rcv = ps2_host_send(0xE2);
    rcv = ps2_host_send(0x2C);
    rcv = ps2_host_recv_response();
    if ((rcv & 1) == 1) {
        // if on, disable pts
        rcv = ps2_host_send(0xE2);
        rcv = ps2_host_send(0x47);
        rcv = ps2_host_send(0x2C);
        rcv = ps2_host_send(0x01);
    }
}
#endif
