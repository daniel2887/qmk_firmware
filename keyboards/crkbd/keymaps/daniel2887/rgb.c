#include QMK_KEYBOARD_H
#include "rgb.h"
#include "keymap.h"
#include "oled.h"

// From https://www.reddit.com/r/MechanicalKeyboards/comments/ix65z0/looking_for_qmk_led_idle_timeout_info/
// Slightly modified by me
// Backlight timeout feature
#define RGB_TIMEOUT 10    // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static uint8_t old_rgb_value = -1;
static bool rgb_on = true;

void rgb_matrix_scan_user(void) {
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
}

bool rgb_process_record_user(uint16_t keycode, keyrecord_t *record) {
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

void rgb_keyboard_post_init_user(void) {
	default_layer_rgb_set_normal();
}

layer_state_t rgb_default_layer_state_set_user(layer_state_t state) {
	if (layer_state_cmp(state, L_GAME)) {
		default_layer_rgb_set_gaming();
	} else if (layer_state_cmp(state, L_BASE)) {
		default_layer_rgb_set_normal();
	} else {
		default_layer_rgb_set_unknown();
	}
    return state;
}
