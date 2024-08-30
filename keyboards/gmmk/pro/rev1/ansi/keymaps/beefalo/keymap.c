#include QMK_KEYBOARD_H

#include "beefalo.h"

enum LayerNames {
    _DF, // Default.
    _FN, // Function.
    _SP, // Special.
    _DG, // Danger.
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DF] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           B_BNCDT,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        MO(_FN), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN), MO(_SP), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, _______,          KC_INS,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, KC_PDOT, _______,          KC_PSCR,
        _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, _______,          KC_PENT,          KC_SCRL,
        _______,          KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3,          _______, _______, KC_PAUS,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [_SP] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, B_KLOCK,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_VOLU,
        XXXXXXX, RGB_TOG, RGB_MOD, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, B_BTN1,  XXXXXXX,          KC_VOLD,
        XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, B_BTN1,           XXXXXXX,          XXXXXXX,
        _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, NK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            MO(_DG),                            XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_DG] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, NK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            _______,                            XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_DF] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN] = { ENCODER_CCW_CW(_______, _______) },
    [_SP] = { ENCODER_CCW_CW(_______, _______) },
    [_DG] = { ENCODER_CCW_CW(_______, _______) },
};
#endif // ENCODER_MAP_ENABLE

#ifdef RGB_MATRIX_ENABLE
static const RGB IND_COLOR = {.r = 255, .g = 0, .b = 0};
static const keypos_t IND_NLCK_POS = {.row = 6, .col = 5};
static const keypos_t IND_CLCK_POS = {.row = 1, .col = 5};
static const keypos_t IND_SLCK_POS = {.row = 2, .col = 5};

bool rgb_matrix_indicators_keymap(void) {
    if (host_keyboard_led_state().num_lock) {
        set_key_rgb(IND_NLCK_POS, IND_COLOR);
    }
    if (host_keyboard_led_state().caps_lock) {
        set_key_rgb(IND_CLCK_POS, IND_COLOR);
    }
    if (host_keyboard_led_state().scroll_lock) {
        set_key_rgb(IND_SLCK_POS, IND_COLOR);
    }

    return true;
}
#endif // RGB_MATRIX_ENABLE
