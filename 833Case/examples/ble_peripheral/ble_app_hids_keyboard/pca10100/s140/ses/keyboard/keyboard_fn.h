#pragma once
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "action.h"

enum fn_functions {
    KEYBOARD_CONTROL,
    SWITCH_DEVICE,
    RGBLIGHT_CONTROL = 4, // RGB灯光相关
    RGBMATRIX_CONTROL, // RGB阵列灯光
};

enum fn_keyboard_control {
    CONTROL_SLEEP, // 睡眠键盘
    CONTROL_NKRO, // 切换NKRO状态
    CONTROL_BATTERY_PERCENTAGE, // 输出电池剩余电量
    CONTROL_BOOTLOADER = 0x0F // 进入bootloader
};

enum fn_switch_device {
    SWITCH_DEVICE_BLE_0 = 0x08,
    SWITCH_DEVICE_BLE_1 = 0x09,
    SWITCH_DEVICE_BLE_2 = 0x0a,
    TTT = 0x07,
    BACKLIGHT_TOP = 0x0b,
    BACKLIGHT_INC = 0x0c,
    BACKLIGHT_DEC = 0x0d,
};
