#include <msp430.h>

#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  if (CALBC1_1MHZ==0xFF)					// If calibration constant erased
  {											
    while(1);                               // do not load, trap CPU!!	
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1DIR |= RXLED + TXLED;
  P1OUT &= 0x00;
  
  UCA0CTL1 |= UCSSEL_2;                     // CLK = SMCLK
  UCA0BR0 = 104;                           // 
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = UCBRS0;               // 
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM3 w/ int until Byte RXed
}

//  Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
  while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
  UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
}