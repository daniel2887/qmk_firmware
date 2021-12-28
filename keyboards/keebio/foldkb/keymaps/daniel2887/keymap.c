/* Copyright 2021 Danny Nguyen <danny@keeb.io>

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

#define GAMING_LAYER_NUM 3

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

// Turn off LEDs when normal (non-gaming) layers are enabled.
const rgblight_segment_t PROGMEM normal_layers_leds[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_CYAN}       // Turn off all RGBLED_NUM LEDs, starting with LED 0
);

// Light up all LEDs when gaming layers are enabled.
const rgblight_segment_t PROGMEM gaming_layers_leds[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_RED}       // Light all RGBLED_NUM LEDs, starting with LED 0
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    normal_layers_leds,
    gaming_layers_leds
);

static void rgb_set_normal(void) {
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	// Dimmer cyan
	// rgblight_sethsv_noeeprom(128, 255, 32);
	// Dimmer white
	rgblight_sethsv_noeeprom(0, 0, 96);
	
}

static void rgb_set_gaming(void) {
	//rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 2);
	rgblight_sethsv_noeeprom(HSV_GREEN);
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
	//rgblight_set_layer_state(0, 1);
	rgb_set_normal();
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    //rgblight_set_layer_state(1, layer_state_cmp(state, GAMING_LAYER_NUM));
	if (layer_state_cmp(state, GAMING_LAYER_NUM)) {
		rgb_set_gaming();
	} else {
		rgb_set_normal();
	}
    return state;
}