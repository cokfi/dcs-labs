



#include  "../header/bsp.h"    // private library - BSP layer
//-------------------------------------------------------------
//           GPIO congiguration
//-------------------------------------------------------------
void GPIOconfig(void)
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
//-------------------------------------------------------------
//           update RGB value
//-------------------------------------------------------------
void updateRGB(int RGB){
    P2OUT |= RGB;
}

//-------------------------------------------------------------
//          Timers congiguration 
//-------------------------------------------------------------
void TIMERconfig(void)
{
  // TimerA Configuration
  TACTL |= TASSEL_1 +TACLR;          // SMCLK, clear TBR, up mode
  TACCR0 = timerDelayMs*30; // Count to 325ms
  
  // TimerB Configuration
  //TBCTL |= TBSSEL_2 + TBCLR;
  //TBCCTL0 |= CCIE;
} 
             
            
  

