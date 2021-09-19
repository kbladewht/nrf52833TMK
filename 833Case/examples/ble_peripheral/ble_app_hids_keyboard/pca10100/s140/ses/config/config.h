#include "nrf_gpio.h"

#ifndef CONFIG_H
#define CONFIG_H

#define KB_NRF_DEBUG
/*Auto Sleep Config*/
#define AUTO_SLEEP_TIMEOUT  APP_TIMER_TICKS(120000) //in Milliseconds

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6464
#define DEVICE_VER      0x0001
#define MANUFACTURER    TMK
#define PRODUCT         RCRD
#define DESCRIPTION     RCRD keyboard firmware for template

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 4

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    1

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE



#define PWM_INSTANCE 0
#define PWM_MAX_COUNT 1000
#define PWM_TOP_LUM 200


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#define BATTERY_PIN NRF_SAADC_INPUT_VDDHDIV5  //P029

#define STATE_LED_ACTIVE 1 



#define LED_BLINK_FAST_INTERVAL APP_TIMER_TICKS(100)
#define LED_BLINK_SLOW_INTERVAL APP_TIMER_TICKS(2000)


/*scan interval (ms)*/
#define SCAN_INTERVAL APP_TIMER_TICKS(10)
//State indicatior LED gpio

/*Backlight config*/
#define BACKLIGHT_ENABLE 0
#define BACKLIGHT_LEVELS 2
//#define BACKLIGHT_STATE_LED 0 

//输出PWM信号控制单色背光灯引脚
#define BLCP NRF_GPIO_PIN_MAP(0, 2)

#define STATE_LED NRF_GPIO_PIN_MAP(0, 10)

#define P111_1 NRF_GPIO_PIN_MAP(0,30) //AIN6
#define P003_2 NRF_GPIO_PIN_MAP(0,31) //AIN7
#define P028_3 NRF_GPIO_PIN_MAP(1,5)  //113
#define P113_4 NRF_GPIO_PIN_MAP(0,28)  //AIN4
#define P002_5 NRF_GPIO_PIN_MAP(0,3)  //AIN1

#define P029_6 NRF_GPIO_PIN_MAP(0,25) //110

#define P031_7 NRF_GPIO_PIN_MAP(0,22)
#define P006_8 NRF_GPIO_PIN_MAP(0,20)
#define P008_9 NRF_GPIO_PIN_MAP(0,29)
#define P026_10 NRF_GPIO_PIN_MAP(0,15)


#define P000_11 NRF_GPIO_PIN_MAP(1,9)
#define P005_12 NRF_GPIO_PIN_MAP(0,8)

#define P109_13 NRF_GPIO_PIN_MAP(1,2)

#define P006_14 NRF_GPIO_PIN_MAP(1,4)
#define P015_15 NRF_GPIO_PIN_MAP(1,6)

#define P012_16 NRF_GPIO_PIN_MAP(0,17)  //AIN0
#define P022_17 NRF_GPIO_PIN_MAP(0,4)  //AIN2
#define P020_18 NRF_GPIO_PIN_MAP(0,0)
#define P100_19 NRF_GPIO_PIN_MAP(0,24)

#define P024_20 NRF_GPIO_PIN_MAP(0,13)
#define P104_21 NRF_GPIO_PIN_MAP(0,9)
#define P106_22 NRF_GPIO_PIN_MAP(0,5)  //AIN3
#define P010_23 NRF_GPIO_PIN_MAP(0,29) //1.11 is not going to use

static const uint8_t row_pins[MATRIX_ROWS] = {P111_1, P003_2, P028_3, P113_4, P002_5, P029_6};
static const uint8_t col_pins[MATRIX_COLS] = {P010_23, P106_22, P104_21, P024_20};
/*
 * Feature disable options
     
 */

/* disable debug print */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

// temp comment
/* disable action features */
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#endif
