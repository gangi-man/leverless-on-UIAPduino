#include "gamepad.h"
#include "ch32v003_GPIO_branchless.h"

//const PortData PortBuiltinLED = { GPIO_port_C, 0, GPIO_PORT_OUTPUT };

const PortData PortD5 = { GPIO_port_D, 5, GPIO_PORT_INPUT, PAD_BUTTON_HAT_UP };
const PortData PortD6 = { GPIO_port_D, 6, GPIO_PORT_INPUT, PAD_BUTTON_HAT_LEFT };
const PortData PortC1 = { GPIO_port_C, 1, GPIO_PORT_INPUT, PAD_BUTTON_HAT_RIGHT };
const PortData PortC2 = { GPIO_port_C, 2, GPIO_PORT_INPUT, PAD_BUTTON_HAT_DOWN };

const PortData PortC0 = { GPIO_port_C, 0, GPIO_PORT_INPUT, PAD_BUTTON_HOME };
const PortData PortC3 = { GPIO_port_C, 3, GPIO_PORT_INPUT, PAD_BUTTON_SELECT };
const PortData PortD1 = { GPIO_port_D, 1, GPIO_PORT_INPUT, PAD_BUTTON_START };

const PortData PortD2 = { GPIO_port_D, 2, GPIO_PORT_INPUT, PAD_BUTTON_X };
const PortData PortC4 = { GPIO_port_C, 4, GPIO_PORT_INPUT, PAD_BUTTON_Y };
const PortData PortA1 = { GPIO_port_A, 1, GPIO_PORT_INPUT, PAD_BUTTON_R1 };
const PortData PortA2 = { GPIO_port_A, 2, GPIO_PORT_INPUT, PAD_BUTTON_L1 };

const PortData PortC5 = { GPIO_port_C, 5, GPIO_PORT_INPUT, PAD_BUTTON_A };
const PortData PortC7 = { GPIO_port_C, 7, GPIO_PORT_INPUT, PAD_BUTTON_B };
const PortData PortC6 = { GPIO_port_C, 6, GPIO_PORT_INPUT, PAD_BUTTON_R2 };
const PortData PortD0 = { GPIO_port_D, 0, GPIO_PORT_INPUT, PAD_BUTTON_L2 };


static void gpio_init_pin(PortData port) {
    if (port.isOutputPort)
        GPIO_pinMode(GPIOv_from_PORT_PIN(port.port, port.number),
                     GPIO_pinMode_O_pushPull,
                     GPIO_Speed_10MHz);
    else
        GPIO_pinMode(GPIOv_from_PORT_PIN(port.port, port.number),
                     GPIO_pinMode_I_pullUp,
                     GPIO_Speed_10MHz);
}

void gamepad_init_gpio_pins() {
    GPIO_port_enable(GPIO_port_A);
    GPIO_port_enable(GPIO_port_C);
    GPIO_port_enable(GPIO_port_D);

    gpio_init_pin(PortD5);
    gpio_init_pin(PortD6);
    gpio_init_pin(PortC1);
    gpio_init_pin(PortC2);

    gpio_init_pin(PortC0);
    gpio_init_pin(PortC3);
    gpio_init_pin(PortD1);

    gpio_init_pin(PortD2);
    gpio_init_pin(PortC4);
    gpio_init_pin(PortA1);
    gpio_init_pin(PortA2);

    gpio_init_pin(PortC5);
    gpio_init_pin(PortC7);
    gpio_init_pin(PortC6);
    gpio_init_pin(PortD0);
}

int gamepad_read_gpio_pin(PortData port) {
    return GPIO_digitalRead(GPIOv_from_PORT_PIN(port.port, port.number));
}

void gamepad_write_gpio_pin(PortData port, uint8_t value) {
    if (value)
        GPIO_digitalWrite(GPIOv_from_PORT_PIN(port.port, port.number), high);
    else
        GPIO_digitalWrite(GPIOv_from_PORT_PIN(port.port, port.number), low);
}

void gamepad_data_reset(GamepadData* pdata) {
    pdata->buttons = 0;
    pdata->hat = 0x08;

    pdata->lxValue = 0;
    pdata->lyValue = 0;
    pdata->rxValue = 0;
    pdata->ryValue = 0;
}

static uint16_t read_pad_button(PortData port) {
    if (port.isOutputPort)
        return 0;

    if (!gamepad_read_gpio_pin(port))
        return port.buttonAssign;
    else
        return 0;
}

void gamepad_read_buttons(GamepadData* pdata) {
    uint16_t result = 0;

    result |= read_pad_button(PortC0);
    result |= read_pad_button(PortC3);
    result |= read_pad_button(PortD1);

    result |= read_pad_button(PortD0);
    result |= read_pad_button(PortC6);
    result |= read_pad_button(PortC7);
    result |= read_pad_button(PortC5);

    result |= read_pad_button(PortA2);
    result |= read_pad_button(PortA1);
    result |= read_pad_button(PortC4);
    result |= read_pad_button(PortD2);

    pdata->buttons = result;
}

void gamepad_read_hat_switch(GamepadData* pdata) {
    uint8_t up = read_pad_button(PortD5);
    uint8_t left = read_pad_button(PortD6);
    uint8_t right = read_pad_button(PortC1);
    uint8_t down = read_pad_button(PortC2);

    if (up && down)
        up = down = 0;
    if (left && right)
        left = right = 0;

    uint8_t hat_value = 0x08;

    if (up) {
        if (right)
            hat_value = 0x01;
        else if (left)
            hat_value = 0x07;
        else
            hat_value = 0x00;
    }

    if (down) {
        if (right)
            hat_value = 0x03;
        else if (left)
            hat_value = 0x05;
        else
            hat_value = 0x04;
    }

    if (!up && !down) {
        if (right)
            hat_value = 0x02;
        if (left)
            hat_value = 0x06;
    }

    pdata->hat = hat_value;
}

void gamepad_read_analog_sticks(GamepadData* pdata) { // This project doesn't care analog sticks.
    pdata->lxValue = 0;
    pdata->lyValue = 0;
    pdata->rxValue = 0;
    pdata->ryValue = 0;
}

void gamepad_data_to_usb_data(GamepadData* pdata, uint8_t usb_data[]) {
    uint8_t* button = (uint8_t*)(&pdata->buttons);
    usb_data[0] = *button++;
    usb_data[1] = *button;

    usb_data[2] = pdata->hat;

    usb_data[3] = pdata->lxValue;
    usb_data[4] = pdata->lyValue;
    usb_data[5] = pdata->rxValue;
    usb_data[6] = pdata->ryValue;
}
