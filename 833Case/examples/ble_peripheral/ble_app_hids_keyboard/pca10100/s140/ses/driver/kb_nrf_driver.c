#include "host.h"
#include "host_driver.h"
#include "kb_nrf_keyboard.h"

#include "log/kb_nrf_print.h"
/* Host driver */
static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

host_driver_t kb_nrf_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer
};


static uint8_t keyboard_leds(void)
{
    //return keyboard.leds();
    return 0;
}
static void send_keyboard(report_keyboard_t *report)
{
    kb_send_report(report);
}
static void send_mouse(report_mouse_t *report)
{
}
static void send_system(uint16_t data)
{
}
static void send_consumer(uint16_t data)
{
}
