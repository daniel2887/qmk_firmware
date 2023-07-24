#pragma once

struct layer_state_t;
struct keyrecord_t;

void rgb_matrix_scan_user(void);
bool rgb_process_record_user(uint16_t keycode, keyrecord_t *record);
void rgb_keyboard_post_init_user(void);
layer_state_t rgb_default_layer_state_set_user(layer_state_t state);
