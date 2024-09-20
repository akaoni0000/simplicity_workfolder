#include <SI_EFM8SB1_Register_Enums.h>                  // SI_SFR declarations
#include "InitDevice.h"
#include "EFM8SB1_SMBus_Master_Multibyte.h"

uint8_t SMB_DATA_IN[NUM_BYTES_RD];
uint8_t SMB_DATA_OUT[NUM_BYTES_WR];
uint8_t TARGET;                             // Target SMBus slave address
volatile bool SMB_BUSY;
volatile bool SMB_RW;                                                             // direction of the current transfer
uint16_t NUM_ERRORS;                        // Counter for the number of errors.
SI_LOCATED_VARIABLE_NO_INIT (reserved, uint8_t, SI_SEG_XDATA, 0x0000);
//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------
SI_SBIT (DISP_EN, SFR_P2, 7);          // Display Enable
#define DISP_BC_DRIVEN   0             // 0 = Board Controller drives display
#define DISP_EFM8_DRIVEN 1             // 1 = EFM8 drives display
SI_SBIT (SDA, SFR_P1, 2);                 // SMBus on P1.2
SI_SBIT (SCL, SFR_P1, 3);                 // and P1.3
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void SMB_LCD_Init (void);
void SMB_LCD_Data (void);
void SMB_Read (void);
void T0_Waitms (uint8_t ms);
int bbb;
int start_flag;
int data_count;
int LCD_RS;
//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup (void)
{
  // Disable the watchdog here
}
 
//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main (void)
{
	volatile uint8_t dat;         // Test counter
	volatile uint8_t data_count;  // SMB_DATA_IN and SMB_DATA_OUT counter
	uint8_t i;                    // Dummy variable counters
	//Enter default mode
	enter_DefaultMode_from_RESET();
	DISP_EN = DISP_BC_DRIVEN;
	while(!SDA)
	{
	  XBR1 = 0x40;                     // Enable Crossbar
	  SCL = 0;                         // Drive the clock low
	  for(i = 0; i < 255; i++);        // Hold the clock low
	  SCL = 1;                         // Release the clock
	  while(!SCL);                     // Wait for open-drain
	  for(i = 0; i < 10; i++);         // Hold the clock high
	  XBR1 = 0x00;                     // Disable Crossbar
	}
	enter_Mode2_from_DefaultMode();
	LED0 = LED_OFF;

	dat = 0;                            // Output data counter
	NUM_ERRORS = 0;                     // Error counter
	bbb = 0;

	SMB_DATA_OUT[0] = 0x38;//0011 1000 38
	      SMB_DATA_OUT[1] = 0x39;//0011 1001 39
	      SMB_DATA_OUT[2] = 0x14;//0001 0100 14
	      SMB_DATA_OUT[3] = 0x73;//0111 0011 73
	      SMB_DATA_OUT[4] = 0x56;//0101 0110 56
	      SMB_DATA_OUT[5] = 0x6C;//0110 1100 6C
	      SMB_DATA_OUT[6] = 0x38;//0011 1000 38
	      SMB_DATA_OUT[7] = 0x01;//0000 0001 01
	      SMB_DATA_OUT[8] = 0x0C;//0000 1100 0C
	SMB_LCD_Init();
	SMB_LCD_Data();
	while(1)
//	while (1)
//	  {
////	    SMB_DATA_OUT[0] = 0x38;//0011 1000 38
////	    SMB_DATA_OUT[1] = 0x39;//0011 1001 39
////	    SMB_DATA_OUT[2] = 0x14;//0001 0100 14
////	    SMB_DATA_OUT[3] = 0x73;//0111 0011 73
////	    SMB_DATA_OUT[4] = 0x56;//0101 0110 56
////	    SMB_DATA_OUT[5] = 0x6C;//0110 1100 6C
////	    SMB_DATA_OUT[6] = 0x38;//0011 1000 38
////	    SMB_DATA_OUT[7] = 0x01;//0000 0001 01
////	    SMB_DATA_OUT[8] = 0x0C;//0000 1100 0C
////	    TARGET = SLAVE_ADDR;             // Target the Slave for next SMBus
////	                     // transfer
//	    SMB_Write();
//	    T0_Waitms (50);                  // Wait 50 ms until the next cycle
//	                     // so that LED blinks slow enough to see
//	    bbb+=1;
//	    if (bbb>=10){
//	        bbb=1;
//	    }
//	  }                           // Start transfer
	//SMB_Write();
	T0_Waitms (50);                  // Wait 50 ms until the next cycle
									   // so that LED blinks slow enough to see
}

void SMB_LCD_Init (void)
{
   //SMB_BUSY=1;
   //while(1){

//       data_count=0;
//       for(data_count=0;data_count<=9;data_count++){
//           T0_Waitms (100);
//           LCD_RS = 0;
//           SMB_DATA_OUT[0] = 0x38;//0011 1000 38
//           SMB_DATA_OUT[1] = 0x39;//0011 1001 39
//           SMB_DATA_OUT[2] = 0xFF;//0001 0100 14
//           SMB_DATA_OUT[3] = 0x73;//0111 0011 73
//           SMB_DATA_OUT[4] = 0x56;//0101 0110 56
//           SMB_DATA_OUT[5] = 0x6C;//0110 1100 6C
//           SMB_DATA_OUT[6] = 0x38;//0011 1000 38
//           SMB_DATA_OUT[7] = 0x01;//0000 0001 01
//           SMB_DATA_OUT[8] = 0x0C;//0000 1100 0C
//           SMB0CN0_STA = 1;
//           data_count+=1;
//       }
   //}
  LCD_RS = 0;
  SMB_DATA_OUT[0] = 0x38;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  SMB_DATA_OUT[0] = 0x39;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  SMB_DATA_OUT[0] = 0x14;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  SMB_DATA_OUT[0] = 0x53;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  SMB_DATA_OUT[0] = 0x73;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  SMB_DATA_OUT[0] = 0x6C;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  SMB_DATA_OUT[0] = 0x38;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  SMB_DATA_OUT[0] = 0x0C;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  SMB_DATA_OUT[0] = 0x01;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

//  SMB_DATA_OUT[0] = 0x0F;// 0000 1100 0C
//  SMB0CN0_STA = 1;
//  T0_Waitms (100);

}

void SMB_LCD_Data (void)
{
//  while(1){
//      for(data_count=0;data_count<=0;data_count++){
//                 T0_Waitms (100);
//                 LCD_RS = 1;
//                 SMB_DATA_OUT[0] = 0x30;
//                 SMB0CN0_STA = 1;
//                 data_count+=1;
//      }
//  }
  LCD_RS = 0;
  SMB_DATA_OUT[0] = 0x80;//C0
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  //while(1){
      LCD_RS = 1;
      SMB_DATA_OUT[0] = 0x30;//0011 1000 38
      SMB0CN0_STA = 1;
      T0_Waitms (100);
  //}
      LCD_RS = 0;
      SMB_DATA_OUT[0] = 0x0F;// 0000 1100 0C
      SMB0CN0_STA = 1;
      T0_Waitms (100);
}


//while (SMB_BUSY);                   // Wait for SMBus to be free.
//SMB_BUSY = 1;                       // Claim SMBus (set to busy)
//SMB0CN0_STA = 1;                            // Start transfer

void SMB_Read (void)
{
   while (SMB_BUSY);               // Wait for bus to be free.
   SMB_BUSY = 1;                       // Claim SMBus (set to busy)
   SMB_RW = 0;                         // Mark this transfer as a READ

   SMB0CN0_STA = 1;                            // Start transfer

   while (SMB_BUSY);               // Wait for transfer to complete
}

//-----------------------------------------------------------------------------
// T0_Waitms
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) uint8_t ms - number of milliseconds to wait
//                        range is full range of character: 0 to 255
//
// Configure Timer0 to wait for <ms> milliseconds using SYSCLK as its time
// base.
//
//-----------------------------------------------------------------------------
void T0_Waitms (uint8_t ms)
{
   TCON &= ~0x30;                      // Stop Timer0; Clear TCON_TF0
   TMOD &= ~0x0f;                      // 16-bit free run mode
   TMOD |=  0x01;

   CKCON0 |= 0x04;                      // Timer0 counts SYSCLKs

   while (ms) {
      TCON_TR0 = 0;                         // Stop Timer0
      TH0 = ((-SYSCLK/1000) >> 8);     // Overflow in 1ms
      TL0 = ((-SYSCLK/1000) & 0xFF);
      TCON_TF0 = 0;                         // Clear overflow indicator
      TCON_TR0 = 1;                         // Start Timer0
      while (!TCON_TF0);                    // Wait for overflow
      ms--;                            // Update ms counter
   }

   TCON_TR0 = 0;                            // Stop Timer0
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
