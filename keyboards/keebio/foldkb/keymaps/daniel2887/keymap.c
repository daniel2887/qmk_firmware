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
//     Layer 3: Symbols layer
//     Layer 4: Numpad layer
//     Layer 5: F-keys
//     Layer 6: Gaming layer, with left space acting as space and PrtSc acting as escape
//     Layer 7: Navigation layer
//     Layer 8: Mouse layer
//     Layer 9: Numpad layer
// To toggle between normal and gaming mode: Fn + Smiley
// Otherwise, the keyboard should feel exactly the same (layer 1 ~ layer 4, layer 2 ~ layer 5)

#define _NAV 1
#define _MOUSE 2
#define _SYM 3
#define _NUM 4
#define _FN 5
#define _GAMING 6

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

layer_state_t layer_state_set_user(layer_state_t state) {
	state = update_tri_layer_state(state, _NAV, _SYM, _NUM);
	return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
	//rgblight_set_layer_state(1, layer_state_cmp(state, _GAMING));
	if (layer_state_cmp(state, _GAMING)) {
		rgb_set_gaming();
	} else {
		rgb_set_normal();
	}
    return state;
}

// From https://www.reddit.com/r/MechanicalKeyboards/comments/ix65z0/looking_for_qmk_led_idle_timeout_info/
// Slightly modified by me
// Backlight timeout feature
#define RGB_TIMEOUT 15    // in minutes
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
		case LT(1,KC_F):
		case LT(3,KC_D):
			// Immediately select the hold action when another key is tapped.
			return true;
		default:
			// Do not select the hold action when another key is tapped.
			return false;
	}
}

// This turns the following key press sequence...
// 1. LT(2, KC_A) Down
// 2. KC_L Down (the L key is also mapped to KC_RGHT on layer 2)
// 3. LT(2, KC_A) Up
// 4. KC_L Up
// ... into KC_RGHT instead of 'al'.
// This helps when quickly typing a key on an upper layer, and accidentally
// ending up "rolling" into that key (releasing the layer key while that
// target key is still held).
//
// In my specific situation, this helps with D+K (expected to generate dash),
// a key combination which I tend to type very quickly. Without this feature,
// I would get 'dk'.
// ... unfortunately it also breaks times when I *do* want to roll, like 'ds'
// in the world "builds". So disabled for now.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //case LT(3,KC_D):
            // Immediately select the hold action when another key is pressed.
            //return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
