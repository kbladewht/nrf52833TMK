#include <stdint.h>
#include <stdbool.h>
#include "nrf_gpio.h"
#include "nordic_common.h"
#include "config.h"

typedef enum
{
    BLINK_FAST = 0,
    BLINK_SLOW = 1,
} blink_freq;



void sleep_mode_enter(void);

void indicator_led_active(void);
void indicator_led_inactive(void);
bool indicator_led_is_active(void);
void indicator_led_blink_start(blink_freq freq);
void indicator_led_blink_stop(void);



void pwm_backlight_set(uint8_t backlight_level);

void board_init(void);
void auto_sleep_timer_refresh(void);
