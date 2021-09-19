
#include "keyboard_fn.h"

#include "host.h"
#include "keymap.h"
#include "ble_service.h"
#include "board_support.h"
#include "kb_nrf_print.h"

static BACKLIGHT_STATE_LED=0;
static BACKLIGHT_LEVELS_t=0;

//FN_HANDLER_DEF();

__attribute__((weak)) void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) {
        switch (id) {
        case SWITCH_DEVICE:
            switch (opt) {

            case TTT:
               
                 kb_nrf_print("for sleep recall.........");
               // sleep_mode_enter();
                break;
            case BACKLIGHT_TOP:
              if(BACKLIGHT_STATE_LED == 1){
                  BACKLIGHT_STATE_LED=0;
                   kb_nrf_print("turn LED off....");
                   pwm_backlight_set(BACKLIGHT_STATE_LED);
              }else{
                  BACKLIGHT_STATE_LED=1;
                  kb_nrf_print("turn LED on....");
                  pwm_backlight_set(BACKLIGHT_STATE_LED);
              }
            
                break;
            case BACKLIGHT_INC:
                if(BACKLIGHT_LEVELS_t>=4){
                  kb_nrf_print("4 is top, skipped... ");
                   break;
                }
                BACKLIGHT_LEVELS_t=BACKLIGHT_LEVELS_t+1;
                pwm_backlight_set(BACKLIGHT_LEVELS_t);
                 kb_nrf_print("BACKLIGHT_LEVELS ++....");
                 kb_nrf_print("BACKLIGHT_LEVELS_t is  %d", BACKLIGHT_LEVELS_t);
               
                break;
            case BACKLIGHT_DEC:
                if(BACKLIGHT_LEVELS_t<=1){
                
                  kb_nrf_print("1 is smallest...skipped... ");
                   break;
                }
                BACKLIGHT_LEVELS_t=BACKLIGHT_LEVELS_t-1;
                 pwm_backlight_set(BACKLIGHT_LEVELS_t);
                 kb_nrf_print("BACKLIGHT_LEVELS --....");
               
                 kb_nrf_print("BACKLIGHT_LEVELS_t is  %d", BACKLIGHT_LEVELS_t);
                break;

            default:
                break;
            }
            break;
        default:
            break;
        }
    }

}
