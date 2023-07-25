#include QMK_KEYBOARD_H

#include "keymap.h"
#include "tap_dance.h"

// Press <= tapping_term: tap
// Press > tapping_term: hold
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

// TODO: Remove if this ends up not being necessary
#if 0
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
		case LT(L_NAV,KC_F):
		case LT(L_SYMB,KC_D):
			// Immediately select the hold action when another key is tapped.
			return true;
		default:
			// Do not select the hold action when another key is tapped.
			return false;
	}
}
#endif

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
		case HOME_S:
		case HOME_L:
            return true;
        default:
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
		// quick-tap-ms enables repeated CTRL-Z by holding CTRL and double
		// tapping and holding Z.
		case LT(L_MEDIA,KC_Z):
            return 200; // milliseconds

		// This is to avoid a situation in which I want to type "CD-PHY"
		// (where D + K should yield '-'), but I actually get "CDdk" due to
		// auto-repeat of the letter D kicking in instead of a layer switch
		// due to the quick double tap of D in that word.
        case LT(L_SYMB,KC_D):
		// Similarly, this is to avoid a situation in which I want to type "df",
		// or any word ending with F, followed by enter or some navigation
		// key (which is on the layer triggered by F).
		case LT(L_NAV,KC_F):
        default:
            return 0;
    }
}

