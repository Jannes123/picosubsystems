/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_SUBSYSTEMS_H
#define _PICO_SUBSYSTEMS_H


#ifdef __cplusplus
extern "C" {
#endif

bool xtimer_callback(struct repeating_timer *jtimer_ptr);
//static inline alarm_id_t add_alarm_in_us(uint64_t us, alarm_callback_t callback, void *user_data, bool fire_if_past);

#endif