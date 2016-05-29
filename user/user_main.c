#include "osapi.h"
#include "os_type.h"
#include "user_config.h"
#include "stdout/stdout.h"
#include "mcp23017/mcp23017.h"


os_timer_t scanTimer;

static uint8_t deviceAddr = 0;
static MCP23017_Self mcpSelf;

void scanTimerCB(void *pArg) {
    static uint16_t i = 0x1;

    i ^= 1 << 8;
    i ^= 1 << 0;

    bool rv = false;
    mcp23017_pinModeAB(&mcpSelf, deviceAddr, MCP23017_OUTPUT);
    //os_printf("mcp23017_pinMode(0, MCP23017_OUTPUT);\n");
    rv = mcp23017_digitalWriteAB(&mcpSelf, deviceAddr, i);
    //os_printf("mcp23017_digitalWrite(deviceAddr, 0, %d)=%s\n", i, rv?"ACK":"NACK");
    //os_printf("Done!\n");

    //DHT();
} // End of timerCallback

void init() {
    //gpio_setup();
    i2c_master_gpio_init();
    i2c_master_init();
    os_printf("i2c_master_gpio_init: I2C_MASTER_SDA_GPIO=GPIO%d, I2C_MASTER_SCL_GPIO=GPIO%d", I2C_MASTER_SDA_GPIO, I2C_MASTER_SCL_GPIO);
    mcp23017_init(&mcpSelf);
    os_timer_setfn(&scanTimer, scanTimerCB, NULL);
    os_timer_arm(&scanTimer, 300, 1);
}

void user_init(void) {
    stdout_init();
    system_init_done_cb(init);
} // End of user_init
