#include QMK_KEYBOARD_H
#include "tap_dance.h"
#include "keymap.h"
#include "rgb.h"

// Tap dance instantaneous state
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// See use of TD_NAV_CW_TOGG
static td_tap_t nct_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static void td_default_layer(tap_dance_state_t *state, void *user_data) {
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

// Function associated with all tap dances
static td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// See use of TD_NAV_CW_TOGG
static void nct_finished(tap_dance_state_t *state, void *user_data) {
    nct_tap_state.state = cur_dance(state);
    switch (nct_tap_state.state) {
        case TD_SINGLE_TAP:
            caps_word_on();
            break;
        case TD_SINGLE_HOLD:
            layer_on(L_NAV);
            break;
        default:
            break;
    }
}

// See use of TD_NAV_CW_TOGG
static void nct_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (nct_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(L_NAV);
    }
    nct_tap_state.state = TD_NONE;
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
	// ref: https://github.com/qmk/qmk_firmware/blob/master/docs/feature_tap_dance.md#example-6-using-tap-dance-for-momentary-layer-switch-and-layer-toggle-keys-idexample-6
	[TD_NAV_CW_TOGG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nct_finished, nct_reset),
};

