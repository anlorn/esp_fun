#include "dht22.h"
#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"
#include "user_interface.h"
#include "espconn.h"
#include "mem.h"


static os_timer_t some_timer;


void some_timerfunc(void *arg)
{
    DHT();
    os_printf("Life is pain!!!!!!\n");
}

void ICACHE_FLASH_ATTR
gpio_setup() {
    DHTInit();
    os_timer_disarm(&some_timer);
    os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);
    os_timer_arm(&some_timer, 5000, 1);
}

void ICACHE_FLASH_ATTR
user_init()
{
    uart_div_modify(0, UART_CLK_FREQ / 78440);
    os_printf("SDK version:%s\n", system_get_sdk_version());
    gpio_setup();
}
