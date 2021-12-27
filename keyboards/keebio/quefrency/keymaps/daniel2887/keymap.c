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
    {0, RGBLED_NUM, HSV_BLACK}       // Turn off all RGBLED_NUM LEDs, starting with LED 0
);

// Light up all LEDs when gaming layers are enabled.
const rgblight_segment_t PROGMEM gaming_layers_leds[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_WHITE}       // Light all RGBLED_NUM LEDs, starting with LED 0
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    normal_layers_leds,
    gaming_layers_leds
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
	rgblight_set_layer_state(0, 1);
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, GAMING_LAYER_NUM));
    return state;
}