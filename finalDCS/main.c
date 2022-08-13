#include  <msp430g2553.h>          // MSP430x2xx
#include "header/Apps/motorApp.h"
#include "header/Apps/motorCalibrationApp.h"
#include "header/Apps/painterApp.h"
#include "header/Apps/scriptApp.h"
#include "header/APIs/joystickAPI.h"
#include "header/APIs/communicationAPI.h"

void runApp(int choice)
{
    switch (choice)
    {
    case 1:
        motorControl();
        break;
    case 2:
        painter();
        break;
    case 3:
        motorCalibration();
        break;
    case 4:
        break;
    }

}

void main()
{
    configureJoystick();
    configureUart();

    int current_choice = 1;
    int y;
    while (1)
    {

        if (isButtonPressed())
        {
            sendMessage(BUTTON_PRESSED_MESSAGE);

            int msg = readMessage();
            if (msg == ACKNOWLEDGE_MESSAGE)
                runApp(current_choice);
        }
        else
        {
            readJoysctickPos();
            y = getVy();
            if (y > UP_THRESHOLD)
            {
                sendMessage(UP_MESSAGE);

                if (current_choice > 1)
                    current_choice--;
            }
            else if (y < DOWN_THRESHOLD)
            {
                sendMessage(DOWN_MESSAGE);

                if (current_choice < 4)
                    current_choice++;
            }

        }

    }
}
