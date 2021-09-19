/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once

#include <stdint.h>
#include "keymap.h"
#include "config.h"
#include "app_timer.h"
#include "ble_service.h"
#include "keyboard_fn.h"
#include "action_layer.h"
#include "action_code.h"
#include "action_util.h"
#include "action_macro.h"

extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const action_t fn_actions[];

action_t keymap_fn_to_action(uint8_t keycode)
{
    return (action_t)fn_actions[FN_INDEX(keycode)];
}

uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    return keymaps[(layer)][(key.row)][(key.col)];
}


/**
 * COMMAND延迟处理事件
 */
enum command_delay_hander_event {
    COMMAND_DFU,         //跳转Bootloader
    COMMAND_SLEEP,       //手动休眠
    COMMAND_SYSTEMOFF,   //手动关机
    COMMAND_DEL_STORAGE, //清空配置存储
    COMMAND_BOND,        //清空绑定
    COMMAND_SWITCH       //切换蓝牙设备
};

/**
 * @brief 睡眠原因
 * 
 */
enum SLEEP_REASON {
    // 无连接自动休眠
    SLEEP_NO_CONNECTION,
    // 按键超时自动休眠
    SLEEP_TIMEOUT,
    // 手动关机休眠
    SLEEP_MANUALLY,
    // 手动关机休眠，并禁用按键唤醒
    SLEEP_MANUALLY_NO_MATRIX_WAKEUP,
    // 非开机唤醒后休眠
    SLEEP_NOT_PWRON
};

