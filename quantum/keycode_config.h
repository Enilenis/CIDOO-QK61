/* Copyright 2016 Jack Humbert
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

#pragma once

#ifdef __cplusplus
#    define _Static_assert static_assert
#endif

#include "eeconfig.h"
#include "keycode.h"
#include "action_code.h"

uint16_t keycode_config(uint16_t keycode);
uint8_t  mod_config(uint8_t mod);

/* NOTE: Not portable. Bit field order depends on implementation */
typedef union {
    uint16_t raw;
    struct {
        bool swap_control_capslock : 1;
        bool capslock_to_control : 1;
        bool swap_lalt_lgui : 1;
        bool swap_ralt_rgui : 1;
        bool no_gui : 1;
        bool swap_grave_esc : 1;
        bool swap_backslash_backspace : 1;
        bool nkro : 1;
        bool swap_lctl_lgui : 1;
        bool swap_rctl_rgui : 1;
        bool oneshot_enable : 1;
        bool swap_escape_capslock : 1;
        bool autocorrect_enable : 1;
        bool User_Send_Type : 1;
    };
} keymap_config_t;

_Static_assert(sizeof(keymap_config_t) == sizeof(uint16_t), "Keycode (magic) EECONFIG out of spec.");

extern keymap_config_t keymap_config;
