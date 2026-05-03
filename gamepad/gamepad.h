#ifndef GPIO_PINS_H
#define GPIO_PINS_H

#include <stdint.h>


// R2 L2 R1 L1  Y  B  A  X
//  *  *  * HM R3 L3 St Sl
typedef enum {
    PAD_BUTTON_NONE = 0,
    PAD_BUTTON_X = 1 << 0,
    PAD_BUTTON_A = 1 << 1,
    PAD_BUTTON_B = 1 << 2,
    PAD_BUTTON_Y = 1 << 3,
    PAD_BUTTON_L1 = 1 << 4,
    PAD_BUTTON_R1 = 1 << 5,
    PAD_BUTTON_L2 = 1 << 6,
    PAD_BUTTON_R2 = 1 << 7,

    PAD_BUTTON_SELECT = 1 << 8,
    PAD_BUTTON_START = 1 << 9,
    PAD_BUTTON_L3 = 1 << 10,
    PAD_BUTTON_R3 = 1 << 11,
    PAD_BUTTON_HOME = 1 << 12,

    PAD_BUTTON_HAT_UP,
    PAD_BUTTON_HAT_LEFT,
    PAD_BUTTON_HAT_RIGHT,
    PAD_BUTTON_HAT_DOWN
} ButtonAssign;

typedef enum {
    GPIO_PORT_INPUT = 0,
    GPIO_PORT_OUTPUT = 1
} GPIODirection;

typedef struct {
    uint8_t port;
    uint8_t number;
    GPIODirection isOutputPort;
    uint16_t buttonAssign;
} PortData;

typedef struct {
    uint16_t buttons;
    uint8_t hat;

    // left analog stick
    int8_t lxValue;
    int8_t lyValue;

    // right analog stick
    int8_t rxValue;
    int8_t ryValue;
    
} GamepadData;


void gamepad_init_gpio_pins();
int  gamepad_read_gpio_pin(PortData port);
void gamepad_write_gpio_pin(PortData port, uint8_t value);

void gamepad_data_reset(GamepadData* pdata);
void gamepad_read_buttons(GamepadData* pdata);
void gamepad_read_hat_switch(GamepadData* pdata);
void gamepad_read_analog_sticks(GamepadData* pdata);
void gamepad_data_to_usb_data(GamepadData* pdata, uint8_t usb_data[]);


//extern const PortData PortBuiltinLED;

extern const PortData PortD5;
extern const PortData PortD6;
extern const PortData PortC1;
extern const PortData PortC2;

extern const PortData PortC0;
extern const PortData PortC3;
extern const PortData PortD1;

extern const PortData PortD2;
extern const PortData PortC4;
extern const PortData PortA1;
extern const PortData PortA2;

extern const PortData PortC5;
extern const PortData PortC7;
extern const PortData PortC6;
extern const PortData PortD0;

#endif
