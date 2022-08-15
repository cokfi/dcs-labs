#include  <msp430g2553.h>          // MSP430x2xx
#include "header/Apps/motorApp.h"
#include "header/Apps/motorCalibrationApp.h"
#include "header/Apps/painterApp.h"
#include "header/Apps/scriptApp.h"
#include "header/APIs/joystickAPI.h"
#include "header/APIs/communicationAPI.h"

void runApp(char choice)
{
    switch (choice)
    {
    case '1':
        motorControl();
        break;
    case '2':
        painter();
        break;
    case '3':
        motorCalibration();
        break;
    case '4':
        break;
    default:
        break;
    }

}

void main()
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    configureJoystick();
    configureUart();
    __bic_SR_register(GIE);
    enableUartRxInterrupt();
    __bis_SR_register(CPUOFF + GIE);// debug RX
    int current_choice = 1;
    unsigned int y;
    while (1)
    {
        if (isButtonPressed())
        {

              while (sendMessage(BUTTON_PRESSED_MESSAGE))
                  {
                      //trap
                  }
              __bis_SR_register(CPUOFF + GIE);//    //trap

              runApp(getState());
        }
        else
        {
            readJoysctickPos();
            y = getVy();
            if (y > UP_THRESHOLD)
            {
                while (sendMessage(UP_MESSAGE))
                {
                    //trap
                }

                if (current_choice > 1)
                    current_choice--;
            }
            else if (y < DOWN_THRESHOLD)
            {
                while (sendMessage(DOWN_MESSAGE))
                {
                    //trap
                }
                if (current_choice < 4)
                    current_choice++;
            }

        }

    }
}
