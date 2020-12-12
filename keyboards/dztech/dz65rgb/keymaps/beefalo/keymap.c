#ifdef QMK_KEYBOARD_H // Added so clangd understands how to provide autocompletions
#include QMK_KEYBOARD_H
#else
#define RGB_MATRIX_ENABLE
#include "../../config.h"
#include "../../v2/config.h"
#include "config.h"
#include "../../dz65rgb.h"
#endif

enum {
    _DF, // Default Layer
    _FN, // Function Layer
    _SP, // Special Layer
    _DG, // Danger Layer
};

enum customKeyCode {
    CC_FNLK = SAFE_RANGE, // Function Lock
    CC_WNLK, // Windows Lock
    CC_ALTCODE, // Alt Code Macro
    CC_ALTCODE_MAX = CC_ALTCODE + 256, // Maximum entries in altCodeMap
};

enum altCodeNames { // Alt Code Map Index
    AMI_SMALL_E_DIA,
    AMI_BIG_E_DIA,
    AMI_MAP_SIZE,
};

const uint32_t altCodeMap[AMI_MAP_SIZE] = {
    [AMI_SMALL_E_DIA] = 0x00EB, // ë
    [AMI_BIG_E_DIA] = 0x00CB, // Ë
};

#define AC(INDEX) (CC_ALTCODE + INDEX)
#define AC_EDIA AC(AMI_SMALL_E_DIA)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DF] = LAYOUT_65_ansi(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGDN,
        MO(_FN), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(_FN), MO(_SP), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT_65_ansi(
        KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_DEL,  KC_INS,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, KC_KP_0, KC_PSCR,
        _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6,          KC_PENT, KC_SLCK,
        _______,          KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______, KC_PAUS,
        _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    ),
    [_SP] = LAYOUT_65_ansi(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
        XXXXXXX, RGB_TOG, RGB_MOD, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
        CC_FNLK, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AC_EDIA, XXXXXXX,          XXXXXXX, XXXXXXX,
        _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,
        XXXXXXX, CC_WNLK, XXXXXXX,                            MO(_DG),                   XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_DG] = LAYOUT_65_ansi(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            _______,                   XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

void sendAltCode(uint16_t keycode) {
    uint16_t mapIndex = keycode - CC_ALTCODE;
    if (mapIndex >= AMI_MAP_SIZE) { // Return if mapIndex is not a valid altCodeMap index
        return;
    }
    uint32_t altCode = altCodeMap[keycode - CC_ALTCODE];

    uint16_t keySequence[5];
    size_t sequenceLength = sizeof(keySequence)/sizeof(keySequence[0]);

    for (size_t i = sequenceLength; i-- > 0;) {
        keySequence[i] = altCode % 10;
        altCode /= 10;

        if (keySequence[i] == 0) { // Replace 0 with 10 to make sequence value align with keycodes
            keySequence[i] = 10;
        }

        keySequence[i] = (KC_KP_1 - 1) + keySequence[i];
    }

    bool numLockOn = host_keyboard_leds() & (1<<USB_LED_NUM_LOCK);
    bool altHeld = (keyboard_report->mods & (KC_LALT | KC_RALT)) == 0;

    if (!numLockOn) { // Turn num lock off if it was on
        register_code(KC_NLCK);
        send_keyboard_report();
        unregister_code(KC_NLCK);
        send_keyboard_report();
    }
    if (!altHeld) { // Hold alt if it was not held
        register_code(KC_LALT);
        send_keyboard_report();
    }

    for (size_t i = 0; i < sequenceLength + 1; i++) {
        if (i > 0) { // Remove previous key if it exists
            del_key(keySequence[i - 1]);
        }
        if (i < sequenceLength) { // Add current key if it exists
            add_key(keySequence[i]);
        }
        send_keyboard_report(); // Include both changes in a single report
    }

    if (!altHeld) { // Release alt if it was not held
        unregister_code(KC_LALT);
        send_keyboard_report();
    }
    if (!numLockOn) { // Turn num lock back on if it was on
        register_code(KC_NLCK);
        send_keyboard_report();
        unregister_code(KC_NLCK);
        send_keyboard_report();
    }
}

bool isFunctionLocked = false;
bool isWindowsLocked = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case CC_FNLK:
            isFunctionLocked = !isFunctionLocked;
            return false;
        case CC_WNLK:
            isWindowsLocked = !isWindowsLocked;
            return false;
        case MO(_FN):
            if (isFunctionLocked) {
                return false;
            }
            break;
        case KC_LGUI:
            if (isWindowsLocked) {
                return false;
            }
            break;
        default:
            if (keycode >= CC_ALTCODE && keycode < CC_ALTCODE_MAX)
            {
                sendAltCode(keycode);
                return false;
            }
            break;
        }
    }

    return true;
}

#ifdef RGB_MATRIX_ENABLE
#define INDICATOR_HUE 0
#define INDICATOR_FNLK_INDEX 30
#define INDICATOR_WNLK_INDEX 59
#define INDICATOR_NLCK_INDEX 14
#define INDICATOR_CLCK_INDEX 29
#define INDICATOR_SLCK_INDEX 43

void rgb_matrix_indicators_user(void) {
    HSV hsv = rgb_matrix_get_hsv();
    hsv.h = INDICATOR_HUE;
    RGB rgb = hsv_to_rgb(hsv);
    #define RGB_VALUES rgb.r, rgb.g, rgb.b

    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(INDICATOR_NLCK_INDEX, RGB_VALUES);
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(INDICATOR_CLCK_INDEX, RGB_VALUES);
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(INDICATOR_SLCK_INDEX, RGB_VALUES);
    }

    if (isFunctionLocked) {
        rgb_matrix_set_color(INDICATOR_FNLK_INDEX, RGB_VALUES);
    }
    if (isWindowsLocked) {
        rgb_matrix_set_color(INDICATOR_WNLK_INDEX, RGB_VALUES);
    }

    #undef RGB_VALUES
}
#endif // RGB_MATRIX_ENABLE
