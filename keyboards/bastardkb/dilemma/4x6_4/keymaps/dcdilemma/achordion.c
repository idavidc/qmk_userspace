// Copyright 2022-2024 Google LLC
// MIT License
#include "achordion.h"

static uint16_t mod_tap_keycode = KC_NO;
static uint16_t mod_tap_pressed_time = 0;

bool achordion_process_record(uint16_t keycode, keyrecord_t* record) {
  if (record->event.pressed && (mod_tap_keycode != KC_NO)) {
    if (achordion_chord(mod_tap_keycode, NULL, keycode, record)) {
      mod_tap_keycode = KC_NO;
    }
  }

  const uint8_t action = mod_tap_layer_action(keycode);
  if (action == QK_MOD_TAP || action == QK_LAYER_TAP) {
    if (record->event.pressed) {
      mod_tap_keycode = keycode;
      mod_tap_pressed_time = record->event.time;
    } else {
      if (mod_tap_keycode == keycode) {
        mod_tap_keycode = KC_NO;
      }
    }
  }

  return true;
}

void achordion_task(void) {
  if (mod_tap_keycode != KC_NO &&
      timer_elapsed(mod_tap_pressed_time) > achordion_timeout(mod_tap_keycode)) {
    mod_tap_keycode = KC_NO;
  }
}

__attribute__((weak)) uint16_t achordion_timeout(uint16_t keycode) {
  return 1000;
}

__attribute__((weak)) bool achordion_opposite_hands(keyrecord_t* tap_hold_record,
                                                    keyrecord_t* other_record) {
  uint8_t row = other_record->event.key.row;
  uint8_t col = other_record->event.key.col;
  bool is_other_right_hand = (col >= MATRIX_COLS / 2);
  bool is_tap_hold_right_hand = (tap_hold_record->event.key.col >= MATRIX_COLS / 2);
  return is_other_right_hand != is_tap_hold_right_hand;
}

__attribute__((weak)) bool achordion_chord(uint16_t tap_hold_keycode,
                                           keyrecord_t* tap_hold_record,
                                           uint16_t other_keycode,
                                           keyrecord_t* other_record) {
  if (other_keycode == KC_BTN1 || other_keycode == KC_BTN2) { return true; }
  if (tap_hold_record && other_record) {
    return achordion_opposite_hands(tap_hold_record, other_record);
  }
  return true;
}
