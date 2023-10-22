// Copyright 2021 Christoph Rehmann (crehmann)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// Using the right side as master
#define MASTER_RIGHT

#ifdef PS2_MOUSE_ENABLE
#define PS2_MOUSE_SCROLL_BTN_MASK (1<<PS2_MOUSE_BTN_RIGHT)   // using the right mouse button for scrolling (other buttons can be configured)
#define PS2_MOUSE_SCROLL_BTN_SEND 500
#define AUTO_BUTTONS
#define AUTO_BUTTONS_TIMEOUT 650
#define PS2_MOUSE_SCROLL_DIVISOR_H 1
#define PS2_MOUSE_SCROLL_DIVISOR_V 1
#endif

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
// TODO: Remove if this ends up not being necessary, here and in tap_hold.c
//#define PERMISSIVE_HOLD_PER_KEY
#define QUICK_TAP_TERM_PER_KEY
#define RETRO_TAPPING_PER_KEY

#define CAPS_WORD_IDLE_TIMEOUT 3000  // 3 seconds.

#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 5
#define MOUSEKEY_DELAY 100
