// Copyright 2022-2023 Google LLC
// MIT License
#pragma once
#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

bool achordion_process_record(uint16_t keycode, keyrecord_t* record);
void achordion_task(void);
uint16_t achordion_timeout(uint16_t keycode);
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record);

#ifdef __cplusplus
}
#endif
