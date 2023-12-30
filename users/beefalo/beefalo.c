#include "quantum.h"

#include "beefalo.h"

/* Keymap space functions. */
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__ ((weak))
bool rgb_matrix_indicators_keymap(void) {
    return true;
}

__attribute__ ((weak))
void keyboard_post_init_keymap(void) {}

/* Ugly global data and things. */
// TODO: Move features to their own files.
static bool b_locked[MATRIX_ROWS][MATRIX_COLS];
static const RGB IND_COLOR = {.r = 255, .g = 0, .b = 0}; // Locked key indicator color.

/// Returns integer index of RGB matrix led at `key`.
int key_to_led(keypos_t key) {
    return g_led_config.matrix_co[key.row][key.col];
}

/// Sets RGB matrix led at `key` to `rgb`.
void set_key_rgb(keypos_t key, RGB rgb) {
    // Idk what happens if `key_to_led()` returns `NO_LED`.
    rgb_matrix_set_color(key_to_led(key), rgb.r, rgb.g, rgb.b);
}

void tap_key(uint16_t keycode) {
    register_code(keycode);
    send_keyboard_report();
    unregister_code16(keycode);
    send_keyboard_report();
}

/* User space functions. */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool locking = false;

    keypos_t key = record->event.key;

    if (locking && keycode != B_KLOCK && record->event.pressed) {
        b_locked[key.row][key.col] = !b_locked[key.row][key.col];
        return false;
    }
    else if (!locking && b_locked[key.row][key.col]) {
        return false;
    }

    switch (keycode) {
    case B_KLOCK:
        locking = (record->event.pressed);
        break;
    case B_BTN1:
        if (record->event.pressed) {
            tap_key(KC_BTN1);
        }
        break;
    default:
        break;
    }

    return process_record_keymap(keycode, record);
}

bool rgb_matrix_indicators_user(void) {
    for (size_t r = 0; r < MATRIX_ROWS; ++r) {
        for (size_t c = 0; c < MATRIX_COLS; ++c) {
            if (b_locked[r][c]) {
                set_key_rgb((keypos_t) {c, r}, IND_COLOR);
            }
        }
    }

    return rgb_matrix_indicators_keymap();
}

void keyboard_post_init_user(void) {
    // debug_enable=true;

    keyboard_post_init_keymap();
}
