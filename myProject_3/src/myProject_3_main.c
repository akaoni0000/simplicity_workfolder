#include <SI_EFM8SB1_Register_Enums.h>
#include <stdio.h>


//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------
//sbit LED = P1^2; // Green LED: '1' = ON; '0' = OFF
sbit LED = P0^4;

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void PORT_Init(void);

int i;
//------------------------------------------------------------------------------------
// MAIN Routinemki
//------------------------------------------------------------------------------------
void main (void) {

  PORT_Init(); // Set up Crossbar and GPIO
  PCA0MD &= ~0x60;
  XBR2 = 0x40;
  while (1) {
  // Infinite loop to keep the program running
  //LED = 1; // Turn on LED
    LED = 0;
    for(i=1; i<=15000000; i++){}
    LED = 1;
    for(i=1; i<=15000000; i++){}
    //for(i=1; i<=15; i++){}
  }
}
//------------------------------------------------------------------------------------
// PORT_Init
//------------------------------------------------------------------------------------
//
// This routine initializes the Crossbar and GPIO pins
//
// Pinout:
// P1.6 - LED (GPIO)
//
void PORT_Init(void)
{
XBR2 = 0x40; // Enable crossbar and weak pull-ups // Enable P1.6 (LED) as a push-pull output
}
