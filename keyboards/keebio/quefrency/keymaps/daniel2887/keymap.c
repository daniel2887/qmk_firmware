#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

// Hacky but meh
#include "daniel2887_keymap.h"

// Notes:
//     Layer 0: Every day layer, with left space acting as Fn
//     Layer 1: Navigation layer
//     Layer 2: Mouse layer
//     Layer 3: Gaming layer, with left space acting as space and PrtSc acting as escape
//     Layer 4: Navigation layer
//     Layer 5: Mouse layer
// To toggle between normal and gaming mode: Fn + Smiley
// Otherwise, the keyboard should feel exactly the same (layer 1 ~ layer 4, layer 2 ~ layer 5)

bool encoder_update_user(uint8_t index, bool clockwise) {
	// Only left encoder supported
	if (index != 0) {
		return true;
	}
	
	if (IS_LAYER_ON(1) || IS_LAYER_ON(4)) {
		if (clockwise) {
			tap_code(KC_MNXT);
		} else {
			tap_code(KC_MPRV);
		}
	} else {
				if (clockwise) {
			tap_code(KC_VOLU);
		} else {
			tap_code(KC_VOLD);
		}
	}
	
    return true;
}
