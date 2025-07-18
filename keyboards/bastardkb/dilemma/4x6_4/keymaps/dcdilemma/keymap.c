/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum dilemma_keymap_layers { LAYER_BASE = 0, LAYER_NAV, LAYER_POINTER, SYM, FUN, MOUSE, MEDIA, NUM};

// Test
bool     is_alt_tab_active       = false;
bool     is_alt_shift_tab_active = false;
uint16_t alt_tab_timer           = 0;


void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            unregister_code(KC_LSFT);
            is_alt_tab_active       = false;
            is_alt_shift_tab_active = false;
        }
    }
};

// Enablng debug

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

// Tap Dance Type Enums

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

enum custom_keycodes {
    CNALTA = SAFE_RANGE,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

// End of Tap Dance Enums

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    TD_CTL_GUI,
    X_CTL,
    TD_DOUBLE_1,
    TD_DBL_1,
    TD_DOUBLE_2,
    TD_ADV_1,
    TD_WIN_HOME,
    TD_WIN_HOME_2,
    TD_WIN_END,
    TD_WIN_END_2,
    TD_MAC_HOME,
    TD_MAC_END,
    TD_OS_END,
    TD_Tilde_Backtick
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

// Automatically enable sniping-mode on the pointer layer.

#define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER
#define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#define DILEMMA_MINIMUM_DEFAULT_DPI 1400


#define NAV MO(LAYER_NAV)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────────────────────────────────────────────────────────╮
        KC_TILD,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────────────────────────────────────┤
        XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────────────────────────────────────┤
        XXXXXXX, MT(MOD_RGUI, KC_A), MT(MOD_LALT, KC_S), MT(MOD_LSFT, KC_D), MT(MOD_RCTL, KC_F),   KC_G,   KC_H,  MT(MOD_RCTL, KC_J), MT(MOD_RSFT, KC_K), MT(MOD_LALT, KC_L), MT(MOD_RGUI, KC_SCLN), KC_QUOT,
  // ├──────────────────────────────────────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────────────────────────────────────┤
       C(A(KC_TAB)),    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LALT,
  // ╰──────────────────────────────────────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────────────────────────────────────╯
                        LCA(KC_TAB), LT(MEDIA, KC_ESC), LT(LAYER_NAV, KC_SPC), LT(MOUSE, KC_TAB ),    LT(NUM, KC_BSPC),  LT(SYM, KC_ENT), LT(FUN, KC_DEL),  KC_MUTE
  //                    ╰───────────────────────────────────────────────────────────────────╯ ╰──────────────────────────────────────────────────────────────────────╯
  ),

  [LAYER_NAV] = LAYOUT(
  // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  // ├──────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────┤
       RGB_MOD, TD(TD_MAC_HOME), XXXXXXX, TD(TD_MAC_END), XXXXXXX, EE_CLR,       XXXXXXX,   KC_HOME,   KC_UP,  KC_END, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────┤
       RGB_TOG, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_P,    KC_PPLS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PMNS, KC_PEQL,
  // ├──────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────┤
      RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DF(LAYER_BASE),    KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_PDOT,
  // ╰──────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────╯
                  XXXXXXX, _______, TD(TD_CTL_GUI), _______,                    QK_MAGIC_SWAP_LCTL_LGUI, _______, QK_MAGIC_UNSWAP_LCTL_LGUI, XXXXXXX
  //                    ╰───────────────────────────────────────────────────╯ ╰───────────────────────────────────────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_TOG, KC_HOME, TD(X_CTL), KC_END, KC_LSFT, XXXXXXX,    KC_PPLS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PMNS, KC_PEQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, EE_CLR,  QK_BOOT,    QK_BOOT, EE_CLR,  SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                         XXXXXXX, KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1, KC_BTN2, XXXXXXX
  //                    ╰───────────────────────────────────╯ ╰───────────────────────────────────╯
  ),

  [SYM] = LAYOUT(
  // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
       XXXXXXX, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_PPLS,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
       XXXXXXX, KC_LGUI, KC_LALT, KC_LPRN, KC_RPRN, KC_PIPE,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
       XXXXXXX, _______, DRGSCRL, KC_LCBR, KC_RCBR,  TD(TD_Tilde_Backtick),     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
                         XXXXXXX, KC_BTN2, KC_BTN1, KC_BTN3,                     _______, KC_BTN1, KC_BTN2, XXXXXXX
  //                    ╰───────────────────────────────────────────────────╯ ╰───────────────────────────────────────────────────╯
  ),

  [FUN] = LAYOUT(
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
         XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,              XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
         XXXXXXX, KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,                             XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
         XXXXXXX, KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL,                             XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
         XXXXXXX, KC_F10  , KC_F1, KC_F2, KC_F3, KC_PAUS,                           XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
                           XXXXXXX, KC_BTN2, KC_LALT, KC_BTN3,                     _______, KC_BTN1, KC_BTN2, XXXXXXX
    //                    ╰───────────────────────────────────────────────────╯ ╰───────────────────────────────────────────────────╯
    ),

    [MOUSE] = LAYOUT(
        // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
              XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,           XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,
        // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
             XXXXXXX, RSFT(KC_1), XXXXXXX, KC_LBRC, KC_RBRC, S_D_MOD,                 XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX, XXXXXXX,
        // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
             XXXXXXX, KC_LGUI, KC_LALT, KC_LPRN, KC_RPRN, KC_PIPE,                    KC_EQL, KC_4, KC_5, KC_6, KC_RGUI, XXXXXXX,
        // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
             XXXXXXX, _______, DRGSCRL, KC_LCBR, KC_RCBR,  TD(TD_Tilde_Backtick),        KC_0, KC_1,  KC_2, KC_3, KC_DOT, XXXXXXX,
        // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
                               XXXXXXX, KC_BTN2, KC_BTN1, KC_BTN3,                     _______, KC_BTN1, KC_BTN2, XXXXXXX
        //                    ╰───────────────────────────────────────────────────╯ ╰───────────────────────────────────────────────────╯
        ),

[MEDIA] = LAYOUT(
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
            XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,             XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
            XXXXXXX, RSFT(KC_1), XXXXXXX, KC_LBRC, KC_RBRC, S_D_MOD,                 XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
            XXXXXXX, KC_LGUI, KC_LALT, KC_LPRN, KC_RPRN, KC_PIPE,                    KC_EQL, KC_4, KC_5, KC_6, KC_RGUI, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
            XXXXXXX, _______, DRGSCRL, KC_LCBR, KC_RCBR,  TD(TD_Tilde_Backtick),        KC_0, KC_1,  KC_2, KC_3, KC_DOT, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
                            XXXXXXX, KC_BTN2, KC_BTN1, KC_BTN3,                     _______, KC_BTN1, KC_BTN2, XXXXXXX
    //                    ╰───────────────────────────────────────────────────╯ ╰───────────────────────────────────────────────────╯
    ),

[NUM] = LAYOUT(
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
            XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,           XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
            XXXXXXX, KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC,                            XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
            XXXXXXX, XXXXXXX, KC_4, KC_5, KC_6, KC_EQL,                             KC_EQL, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
            XXXXXXX, _______, KC_1, KC_2, KC_3,  KC_BSLS,                           XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,
    // ╭──────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────╮
                            XXXXXXX, KC_BTN2, KC_0, KC_BTN3,                     _______, KC_BTN1, KC_BTN2, XXXXXXX
    //                    ╰───────────────────────────────────────────────────╯ ╰───────────────────────────────────────────────────╯
    ),

};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLEE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif // RGB_MATRIX_ENABLE

// #ifdef ENCODER_MAP_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // left knob
        switch (get_highest_layer(layer_state)) {
            case LAYER_BASE: // App switching
                if (clockwise) {
                    //if (!is_alt_tab_active) {
                    //    is_alt_tab_active = true;
                    //    unregister_code(KC_LSFT);
                    //    register_code(KC_LALT);
                    //}
                    alt_tab_timer = timer_read();
                    tap_code(KC_TAB);
                } else {
                    //if (!is_alt_shift_tab_active) {
                    //    is_alt_shift_tab_active = true;
                    //    register_code(KC_LALT);
                    //    register_code(KC_LSFT);
                    //}
                    alt_tab_timer = timer_read();
                    tap_code16(RSFT(KC_TAB));
                    //register_code16(RSFT(KC_TAB));
                    //SEND_STRING(SS_TAP(RSFT(KC_TAB)));
                }
                break;
            case LAYER_NAV: // Mouse wheel U/D
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
                break;
            case MOUSE: // Underglow brightness
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
                break;
            default: // No action
                if (clockwise) {
                    tap_code(KC_NO);
                } else {
                    tap_code(KC_NO);
                }
                break;
        }
    }
    return true;
}
// #endif

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


void x_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_HOME); break;
        case TD_SINGLE_HOLD: register_code16(RCTL(KC_HOME)); break;
        case TD_DOUBLE_TAP: register_code(KC_B); break;
        case TD_DOUBLE_HOLD: register_code(KC_C); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
        default: break;
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_HOME); break;
        case TD_SINGLE_HOLD: unregister_code16(RCTL(KC_HOME)); break;
        case TD_DOUBLE_TAP: unregister_code(KC_B); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_C); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

// Dynamic Y beg

void y_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_HOME); break;
        case TD_SINGLE_HOLD: register_code16(RCTL(KC_HOME)); break;
        case TD_DOUBLE_TAP: register_code(KC_B); break;
        case TD_DOUBLE_HOLD: register_code(KC_C); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
        default: break;
    }
}

void y_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_HOME); break;
        case TD_SINGLE_HOLD: unregister_code16(RCTL(KC_HOME)); break;
        case TD_DOUBLE_TAP: unregister_code(KC_B); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_C); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

// Dynamic Y end

typedef struct {
    uint16_t keycode;
} test_user_data_t;

void generic_register(tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((test_user_data_t*)user_data)->keycode;
    xtap_state.state = cur_dance(state);
    //switch (state->count) {
    dprintf("Generic register - start : %d\n", keycode);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            dprintf("Generic register - Case 1 - process within test_fin xtap_state.state : %d\n", xtap_state.state);
            dprintf("Generic register - Case 1 - process within test_fin : %d\n", keycode);
            register_code16(keycode);
            break;
        case TD_DOUBLE_TAP:
            dprintf("Generic register - Case 2 - process within test_fin xtap_state.state : %d\n", xtap_state.state);
            dprintf("Generic register - Case 2 - process within test_fin : %d\n", keycode);
            //for (uint8_t i=0; i<10; i++) {
                //dprintf("Case 2 - inside for loop : %d\n", i);
                //register_code16(RCTL(keycode));break;
            register_code16(RSFT(keycode));break;
            //}
        case TD_SINGLE_HOLD:
            dprintf("Generic register - Case 3 - process within test_fin xtap_state.state : %d\n", xtap_state.state);
            dprintf("Generic Register - Case 3 - process within test_fin - Single Hold : %d\n", keycode);
            //for (uint8_t i=0; i<10; i++) {
                //dprintf("Case 3 - inside for loop : %d\n", i);
                //register_code16((RSFT(keycode)));break;
            register_code16(RSFT(RCTL((keycode))));break;
            //}
        dprintf("Generic register xtap_state.state : %d\n", xtap_state.state);
        default:break;
    }
};

void generic_unregister(tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((test_user_data_t*)user_data)->keycode;
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            dprintf("Generic Unregister - Case 1 - process within test_fin xtap_state.state : %d\n", xtap_state.state);
            dprintf("Generic Unregister - Case 1 - process within test_fin : %d\n", keycode);
            unregister_code16(keycode);break;
        case TD_DOUBLE_TAP:
            dprintf("Generic Unregister - Case 2 - process within test_fin : %d\n", keycode);
            //for (uint8_t i=0; i<10; i++) {
                //unregister_code16(RCTL(keycode));break;
            unregister_code16(RSFT(keycode));break;
            //}
        case TD_SINGLE_HOLD:
            dprintf("Generic Unegister - Case 3 - process within test_fin : %d\n", keycode);
            //for (uint8_t i=0; i<10; i++) {
                //dprintf("Case 3 - inside for loop : %d\n", i);
                //unregister_code16(RCTL(RSFT(keycode)));break;
            unregister_code16(RSFT(RCTL(keycode)));break;
            //}
        default:break;
    }
    xtap_state.state = TD_NONE;
};


// Mac specific stuff


void mac_generic_register(tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((test_user_data_t*)user_data)->keycode;
    xtap_state.state = cur_dance(state);
    //switch (state->count) {
    dprintf("Generic mac_register - start : %d\n", keycode);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            dprintf("Generic mac_register - Case 1 - process within test_fin xtap_state.state : %d\n", xtap_state.state);
            dprintf("Generic mac_register - Case 1 - process within test_fin : %d\n", keycode);
            register_code16(keycode);break;
        case TD_DOUBLE_TAP:
            dprintf("Generic mac_register - Case 2 - process within test_fin xtap_state.state : %d\n", xtap_state.state);
            dprintf("Generic mac_register - Case 2 - process within test_fin : %d\n", keycode);
            //for (uint8_t i=0; i<10; i++) {
                //dprintf("Case 2 - inside for loop : %d\n", i);
                //register_code16(RCTL(keycode));break;
            register_code16(RGUI(keycode));break;
            //}
        case TD_SINGLE_HOLD:
            dprintf("Generic mac_register - Case 3 - process within test_fin xtap_state.state : %d\n", xtap_state.state);
            dprintf("Generic mac_register - Case 3 - process within test_fin - Single Hold : %d\n", keycode);
            //for (uint8_t i=0; i<10; i++) {
                //dprintf("Case 3 - inside for loop : %d\n", i);
                //register_code16((RSFT(keycode)));break;
            register_code16(RGUI(RSFT((keycode))));break;
            //}
        dprintf("Generic mac_register xtap_state.state : %d\n", xtap_state.state);
        default:break;
    }
};

void mac_generic_unregister(tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((test_user_data_t*)user_data)->keycode;
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            dprintf("Generic mac_Unregister - Case 1 - process within test_fin xtap_state.state : %d\n", xtap_state.state);
            dprintf("Generic mac_Unregister - Case 1 - process within test_fin : %d\n", keycode);
            unregister_code16(keycode);break;
        case TD_DOUBLE_TAP:
            dprintf("Generic mac_Unregister - Case 2 - process within test_fin : %d\n", keycode);
            //for (uint8_t i=0; i<10; i++) {
                //unregister_code16(RCTL(keycode));break;
            unregister_code16(RGUI(keycode));break;
            //}
        case TD_SINGLE_HOLD:
            dprintf("Generic mac_Unegister - Case 3 - process within test_fin : %d\n", keycode);
            //for (uint8_t i=0; i<10; i++) {
                //dprintf("Case 3 - inside for loop : %d\n", i);
                //unregister_code16(RCTL(RSFT(keycode)));break;
            unregister_code16(RGUI(RSFT(keycode)));break;
            //}
        default:break;
    }
    xtap_state.state = TD_NONE;
};

// end Mac

// Example of passing and receiving keycode
#define ACTION_TAP_DANCE_DBL(kc1, kc2) \
    { .fn = {tap_dance_pair_on_each_tap, tap_dance_pair_finished, tap_dance_pair_reset, NULL}, .user_data = (void *)&((tap_dance_pair_t){kc1, kc2}), }

// Dynamic TD Function
#define ACTION_TAP_DANCE_FN_ADVANCED_USER_1(user_fn_on_each_tap, kc1) \
    { .fn = {user_fn_on_each_tap}, .user_data = (void *)&((test_user_data_t){kc1}), }
// End dynamic TD Function

#define ACTION_TAP_DANCE_FN_ADVANCED_USER_2(user_fn_on_dance_finished, user_fn_on_dance_reset, kc1) \
        { .fn = {user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = (void *)&((test_user_data_t){kc1}), }

#define ACTION_TAP_DANCE_FN_ADVANCED_USER_3(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, kc1) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = (void *)&((test_user_data_t){kc1}), }



// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_CTL_GUI] = ACTION_TAP_DANCE_DOUBLE(QK_MAGIC_SWAP_LCTL_LGUI, QK_MAGIC_UNSWAP_LCTL_LGUI),
    [TD_DOUBLE_1] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_B),
    [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    [TD_DBL_1] = ACTION_TAP_DANCE_DBL(KC_A, KC_B),
    [TD_DOUBLE_2] = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_Y),
    [TD_WIN_HOME] = ACTION_TAP_DANCE_FN_ADVANCED_USER_2(generic_register, generic_unregister, KC_HOME),
    [TD_WIN_END] = ACTION_TAP_DANCE_FN_ADVANCED_USER_2(generic_register, generic_unregister, KC_END),
    [TD_WIN_HOME_2] = ACTION_TAP_DANCE_FN_ADVANCED_USER_3(NULL, generic_register, generic_unregister, KC_HOME),
    [TD_WIN_END_2] = ACTION_TAP_DANCE_FN_ADVANCED_USER_3(NULL, generic_register, generic_unregister, KC_END),
    [TD_MAC_HOME] = ACTION_TAP_DANCE_FN_ADVANCED_USER_3(NULL, mac_generic_register, mac_generic_unregister, KC_LEFT),
    [TD_MAC_END] = ACTION_TAP_DANCE_FN_ADVANCED_USER_3(NULL, mac_generic_register, mac_generic_unregister, KC_RIGHT),
    [TD_OS_END] = ACTION_TAP_DANCE_FN_ADVANCED_USER_2(generic_register, generic_unregister, KC_END),
    [TD_Tilde_Backtick] = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_TILD),
};

void press_unpress(bool pressed, int code1, int code2) {
  if(pressed) {
    register_code16(code1);
    register_code16(code2);
  } else {
    unregister_code16(code2);
    unregister_code16(code1);
  }
};

// End of Tap Dance Dynamic Function testing

// OS Detection

#if defined(OS_DETECTION_ENABLE)
bool process_detected_host_os_user(os_variant_t detected_os) {
    if (is_keyboard_master()) {

        switch (detected_os) {
            case OS_IOS:
            case OS_MACOS:
                xprintf("MacOS Detected\n");
                keymap_config.swap_lctl_lgui = true;
                break;
            default:
                keymap_config.swap_lctl_lgui = false;
                break;
        }
    }

    return true;
}
#endif // OS_DETECTION_ENABLE

// End OS Detection


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
    //dprintf("%s keycode\n", keycode);

    dprintf("process --> KL: kc: 0x%04X, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif
  return true;
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
    //print("Running post_process_record_user.\n");
    dprintf("post_process --> KL: kc: 0x%04X, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif
}


