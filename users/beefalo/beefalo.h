#pragma once

#include "quantum.h"

#define SAFE_RANGE_USER SAFE_RANGE

#ifndef B_BOUNCE_TIME
#define B_BOUNCE_TIME 64
#endif

// Maybe at some point I want to allow for keycodes to be gated behind ifdefs?
// I.e., whole features to be optional? Idk.
enum beefalo_keycodes {
    B_UNUSED = SAFE_RANGE_USER - 1,
    B_KLOCK, // Locks keys from being pressed.
    B_BTN1, // Press and release KC_BTN1 instantly.
    #ifdef B_BOUNCE_DETECT
    B_BNCDT, // Toggles bounce detection.
    #endif
    SAFE_RANGE_KEYMAP,
};

typedef char foobar[(SAFE_RANGE_KEYMAP <= QK_USER_MAX + 1) ? 0 : -1];

/* Ugly reused functions. */
int key_to_led(keypos_t key);
void set_key_rgb(keypos_t key, RGB rgb);
