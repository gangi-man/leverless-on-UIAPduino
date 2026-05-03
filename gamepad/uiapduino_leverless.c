#include "ch32fun.h"
#include "rv003usb.h"
#include "gamepad.h"

#define USB_DATA_LENGTH 7

static uint8_t USB_send_data[2][USB_DATA_LENGTH] = { 0x00 };
volatile uint8_t current_send_data_index = 0;

int main()
{
    SystemInit();
    gamepad_init_gpio_pins();

    GamepadData pad_data;
    gamepad_data_reset(&pad_data);
    gamepad_data_to_usb_data(&pad_data, USB_send_data[current_send_data_index]);

    Delay_Ms(16);
    usb_setup();

	while(1) {
        gamepad_read_buttons(&pad_data);
        gamepad_read_hat_switch(&pad_data);
        gamepad_read_analog_sticks(&pad_data);

        uint8_t next_index = current_send_data_index ^ 1;
        gamepad_data_to_usb_data(&pad_data, USB_send_data[next_index]);
        current_send_data_index = next_index;
        Delay_Ms(8);
    }
}

void usb_handle_user_in_request( struct usb_endpoint * e, uint8_t * scratchpad, int endp, uint32_t sendtok, struct rv003usb_internal * ist )
{
    if( endp )
    {
        usb_send_data(USB_send_data[current_send_data_index], USB_DATA_LENGTH, 0, sendtok);
    }
    else
    {
        // If it's a control transfer, nak it.
        usb_send_empty(sendtok);
    }
}
