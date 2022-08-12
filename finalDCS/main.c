#include  <msp430g2553.h>          // MSP430x2xx

#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1
/**
 * main.c
 */
static unsigned int motorSequence = 0x10;

static unsigned int v_x = 0x00;
static int v_y;
static int current_adc_channel = 0;
static int counter =0;

void configureADC()
{
    ADC10CTL0 = 0;
    ADC10CTL0 |= ADC10ON + MSC+ADC10SHT_2; // Turn Module On
    ADC10CTL1 |= CONSEQ_3; // Repeat Sequence of Channels Mode
    ADC10CTL1 |= SHS_0; // SH
    ADC10CTL1 |= INCH_1; // Highest Channel in the sequence is A1
    ADC10CTL1 |= ADC10DF + ADC10DIV_4; // 2's Complement format
}

void configureUart()
{
    if (CALBC1_1MHZ==0xFF)                    // If calibration constant erased
    {
      while(1);                               // do not load, trap CPU!!
    }
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL = CALDCO_1MHZ;

    P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1DIR |= RXLED + TXLED;
    P1OUT &= 0x00;

    UCA0CTL1 |= UCSSEL_2;                     // CLK = SMCLK
    UCA0BR0 = 104;                           //
    UCA0BR1 = 0x00;                           //
    UCA0MCTL = UCBRS0;               //
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void enableUartInterrupt(){
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

void startADC()
{
    ADC10CTL0 |= ENC; // Enable Conversions (Must be reset before changing configuration)
    ADC10CTL0 |= ADC10SC; // Start Conversion
}

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Connect P2 to LEDs to see values
    P2SEL = 0;
    P2DIR = 0xFF;
    configureUart();
//    configureADC();
//    startADC();
    enableUartInterrupt();
    while (1)
    {
//        P2OUT = (unsigned int)ADC10MEM>>8;
        __bis_SR_register(LPM0_bits + GIE);
    }
}




//-------------------------------------------------------------
//           interrupt vector uartTx
//-------------------------------------------------------------
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{

            UCA0TXBUF = 0x511&0xff;                 // TX next sample
            if (counter >=1){
                IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
                counter = 0;
            }
            counter++;

}

//-------------------------------------------------------------
//           interrupt vector uartRx
//-------------------------------------------------------------
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    if (UCA0RXBUF == 'u')                     // 'u' received?
    {
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF =  0x511>>8;
      }
}
