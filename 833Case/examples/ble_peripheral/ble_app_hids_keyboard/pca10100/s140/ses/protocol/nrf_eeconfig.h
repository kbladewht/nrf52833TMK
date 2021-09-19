#include <stdint.h>
#include <stdbool.h>
#include <string.h>


//eeconfig 数据结构体
typedef struct
{
    uint16_t magic;
    uint8_t debug;
    uint8_t default_layer;
    uint8_t keymap;
    uint8_t mousekey_accel;
    uint8_t backlight;
}__attribute__((aligned(4))) eeconfig_data_t;
