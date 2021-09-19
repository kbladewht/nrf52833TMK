
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

#include "board_support.h"
#include "nrf_soc.h"
#include "nrf_gpio.h"
#include "nordic_common.h"
#include "nrf_delay.h"
#include "app_timer.h"
#include "app_scheduler.h"
#include "nrfx_timer.h"
#include "app_scheduler.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "kb_nrf_print.h"
#include "nrf_log_default_backends.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_pwm.h"


//Auto Sleep
APP_TIMER_DEF(auto_sleep_timer_id);//create timer



static uint32_t board_wake_up_buttom_prepare(void)
{
    static nrf_gpio_pin_pull_t col_pull_config;
    static nrf_gpio_pin_sense_t col_sense_config;
    static bool row_state;
   
    col_pull_config = NRF_GPIO_PIN_PULLUP;
    col_sense_config = NRF_GPIO_PIN_SENSE_LOW;
  
    for(uint8_t idx = 0; idx < MATRIX_COLS; idx++){
        nrf_gpio_cfg_sense_input(col_pins[idx], col_pull_config, col_sense_config);
    }
    //设置行输出状态,默认输出低电平
    for(uint8_t idx = 0; idx < MATRIX_ROWS; idx++){
        nrf_gpio_cfg_output(row_pins[idx]);
        nrf_gpio_pin_clear(row_pins[idx]);//输出低电平
    }
    return NRF_SUCCESS;
}




/**@brief Function for putting the chip into sleep mode.
 *
 * @note This function will not return.
 */
 void sleep_mode_enter(void)
{
  ret_code_t err_code;
    err_code = board_wake_up_buttom_prepare();

     // Turn off Indicator LED
    nrf_gpio_cfg_default(STATE_LED);

      // Stop app timers
    err_code = app_timer_stop(auto_sleep_timer_id);
    APP_ERROR_CHECK(err_code); 

    // Go to system-off mode (this function will not return; wakeup will cause a reset).
     kb_nrf_print("sd_power_system_off is being invoked..");
    err_code = sd_power_system_off();
    //APP_ERROR_CHECK(err_code);
}




//Auto sleep timeout handler
static void auto_sleep_timeout_handler(void * p_context)
{
    kb_nrf_print("sleep mode enter start")
    sleep_mode_enter();
}

//Auto Sleep init
static void auto_sleep_init(void)
{
    ret_code_t err_code;
    err_code = app_timer_create(&auto_sleep_timer_id,
                                APP_TIMER_MODE_SINGLE_SHOT,
                                auto_sleep_timeout_handler);
    APP_ERROR_CHECK(err_code);
    err_code = app_timer_start(auto_sleep_timer_id, AUTO_SLEEP_TIMEOUT, NULL);
    APP_ERROR_CHECK(err_code);
    kb_nrf_print("auto sleep init");
}





//Indicator led

//led timer
APP_TIMER_DEF(led_blink_timer_id);

bool indicator_led_is_blink = false;
bool indicator_led_original_state;


void indicator_led_active(void)
{
    if(STATE_LED_ACTIVE){
        nrf_gpio_pin_set(STATE_LED);
    }
    else{
        nrf_gpio_pin_clear(STATE_LED);
    }
}

void indicator_led_inactive(void)
{
    if(STATE_LED_ACTIVE){
        nrf_gpio_pin_clear(STATE_LED);
    }
    else{
        nrf_gpio_pin_set(STATE_LED);
    }
}

bool indicator_led_is_active(void)
{
    uint32_t state = nrf_gpio_pin_read(STATE_LED);
    if(state == STATE_LED_ACTIVE){
        return true;
    }
    else{
        return false;
    }
}

void indicator_led_blink_start(blink_freq freq)
{
    indicator_led_original_state = indicator_led_is_active();
    ret_code_t err_code;
    if(indicator_led_is_blink){
        err_code = app_timer_stop(led_blink_timer_id);
        APP_ERROR_CHECK(err_code);
    }
    if(freq == BLINK_FAST){
        err_code = app_timer_start(led_blink_timer_id,
                               LED_BLINK_FAST_INTERVAL,
                               NULL);
    }
    else{
        err_code = app_timer_start(led_blink_timer_id,
                               LED_BLINK_SLOW_INTERVAL,
                               NULL);
    }
    APP_ERROR_CHECK(err_code);
    indicator_led_is_blink = true;
}


void indicator_led_blink_stop(void)
{
    ret_code_t err_code;
    // stop blinking
    if(indicator_led_is_blink){
        err_code = app_timer_stop(led_blink_timer_id);
        APP_ERROR_CHECK(err_code);
        // reset to original state
        if(indicator_led_original_state){
            indicator_led_active();
        }
        else{
            indicator_led_inactive();
        }
    }
    indicator_led_is_blink = false;
}

static void indicator_led_toggle(void)
{
    nrf_gpio_pin_toggle(STATE_LED);
}

static void blink_timeout_handler(void * p_context)
{
    indicator_led_toggle();
}

//Config the pin as output
static void indicator_led_init(void)
{


    ret_code_t err_code;
    //config as output
    nrf_gpio_cfg_output(STATE_LED);
    //init blink timer
    err_code = app_timer_create(&led_blink_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                blink_timeout_handler);
    APP_ERROR_CHECK(err_code);
    NRF_LOG_INFO("Indicator led init");
}



// setting VDD and GPIO voltage to 3.3V when power via VDDH
static void gpio_output_voltage_setup(void)
{
    // Configure UICR_REGOUT0 register only if it is set to default value.
    if ((NRF_UICR->REGOUT0 & UICR_REGOUT0_VOUT_Msk) ==
        (UICR_REGOUT0_VOUT_DEFAULT << UICR_REGOUT0_VOUT_Pos))
    {
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

        NRF_UICR->REGOUT0 = (NRF_UICR->REGOUT0 & ~((uint32_t)UICR_REGOUT0_VOUT_Msk)) |
                            (UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos);

        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

        // System reset is needed to update UICR registers.
        NVIC_SystemReset();
    }
}

void board_init()
{
   gpio_output_voltage_setup();


    kb_nrf_print("indicator_led_init");
   // indicator_led_init();
    //auto_sleep_init();
    //initPwm(BACKLIGHT_LEVELS);
    //pwm_backlight_set(BACKLIGHT_LEVELS);
}


//Backlight
void backlight_set(uint8_t level)
{
    //demo4(level);
}

//refresh timer
void auto_sleep_timer_refresh(void)
{
    ret_code_t err_code;
    err_code = app_timer_stop(auto_sleep_timer_id);
    APP_ERROR_CHECK(err_code);
    err_code = app_timer_start(auto_sleep_timer_id, AUTO_SLEEP_TIMEOUT, NULL);
    APP_ERROR_CHECK(err_code);
    //kb_nrf_print("auto sleep timer freshed")
}

static nrf_drv_pwm_t m_pwm0 = NRF_DRV_PWM_INSTANCE(0);
#define USED_PWM(idx) (1UL << idx)

static uint8_t m_used = 0;
static nrf_pwm_values_common_t duty_values[BACKLIGHT_LEVELS + 1];

static const nrf_drv_pwm_config_t config = 
{
    .output_pins = 
    {
        BLCP,                  // 
        NRF_DRV_PWM_PIN_NOT_USED, 
        NRF_DRV_PWM_PIN_NOT_USED,
        NRF_DRV_PWM_PIN_NOT_USED  
    },
    .irq_priority = APP_IRQ_PRIORITY_LOWEST, //最低优先级
    .base_clock   = NRF_PWM_CLK_125kHz,       //PWM时钟频率设置为1MHz pwm周期为时钟频率除以计数最大值
    .count_mode   = NRF_PWM_MODE_UP,        //向上计数模式
    .top_value    = PWM_MAX_COUNT,          //计数最大值
    
    .load_mode    = NRF_PWM_LOAD_COMMON,    //通用装载模式
    .step_mode    = NRF_PWM_STEP_AUTO       //序列中的周期自动推进
};


 void initPwm(uint8_t backlight_level)
{


   // nrf_drv_pwm_init(&m_pwm0, &config, NULL);
   // APP_ERROR_CHECK(nrf_drv_pwm_init(&m_pwm0, &config, NULL));
    m_used |= USED_PWM(0);


    nrf_pwm_values_common_t step = (PWM_MAX_COUNT - PWM_TOP_LUM) / BACKLIGHT_LEVELS;
    for(uint8_t i = 0; i <= BACKLIGHT_LEVELS; i++)
    {
        duty_values[i] = PWM_MAX_COUNT - step * i;
    }
}

 void pwm_backlight_set(uint8_t backlight_level)
{
    if (backlight_level == 0){
      nrfx_pwm_uninit(&m_pwm0);
      return;
    }
    
    nrf_drv_pwm_init(&m_pwm0, &config, NULL);

    nrf_pwm_sequence_t const pwm0_seq =
    {
        .values.p_common = &duty_values[backlight_level],
        .length           = NRF_PWM_VALUES_LENGTH(duty_values),
        .repeats          = 1,
        .end_delay        = 0
    };


    (void)nrf_drv_pwm_simple_playback(&m_pwm0, &pwm0_seq, 1,     NRF_DRV_PWM_FLAG_LOOP);  
}
