#pragma once

#include "quantum.h"

#define SAFE_RANGE_USER SAFE_RANGE

// Maybe at some point I want to allow for keycodes to be gated behind ifdefs?
// I.e., whole features to be optional? Idk.
enum beefalo_keycodes {
    B_UNUSED = SAFE_RANGE_USER - 1,
    B_KLOCK, // Locks keys from being pressed.
    B_BTN1, // Press and release KC_BTN1 instantly.
    SAFE_RANGE_KEYMAP,
};

/* Ugly reused functions. */
int key_to_led(keypos_t key);
void set_key_rgb(keypos_t key, RGB rgb);
