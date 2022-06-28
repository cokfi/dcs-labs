



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
void clearConfig(){
     TACTL = 0x00;
     CCTL0 = 0x00; 
     updateRGB(0x00);
     ADC10CTL0 &= ~ENC;
     // TACCTL2= 0x00;
     // TACCR0= 0x00;
     // TACCR2= 0x00;
}
//-------------------------------------------------------------
//           update RGB value
//-------------------------------------------------------------
void updateRGB(int RGB){
    P2OUT &= ~0x7; // shut down RGB
    P2OUT |= RGB;  // power up RGB
}

//-------------------------------------------------------------
//          Timers congiguration 
//-------------------------------------------------------------
void TIMERconfig(void)
{
  // TimerA Configuration
  CCR0 = timerDelayMs*5;
  TACTL = TASSEL_1 + MC_1;                  // ACLK, upmode
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
} 
             
            
  

