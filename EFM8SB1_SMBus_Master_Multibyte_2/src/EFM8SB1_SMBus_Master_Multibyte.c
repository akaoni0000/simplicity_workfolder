#include <SI_EFM8SB1_Register_Enums.h>                  // SI_SFR declarations
#include "InitDevice.h"
#include "EFM8SB1_SMBus_Master_Multibyte.h"

uint8_t SMB_DATA_IN[NUM_BYTES_RD];
uint8_t SMB_DATA_OUT[NUM_BYTES_WR];

void SMB_LCD_Init (void);
void SMB_LCD_Data (void);
void T0_Waitms (uint8_t ms);

int LCD_RS;
void SiLabs_Startup (void) {}
int main (void)
{
	enter_DefaultMode_from_RESET();
	enter_Mode2_from_DefaultMode();

	SMB_LCD_Init();
	SMB_LCD_Data();
	while(1);
}

void SMB_LCD_Init (void)
{

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

}

void SMB_LCD_Data (void)
{
  LCD_RS = 0;
  SMB_DATA_OUT[0] = 0x80;//C0
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  LCD_RS = 1;
  SMB_DATA_OUT[0] = 0x30;//0011 1000 38
  SMB0CN0_STA = 1;
  T0_Waitms (100);

  LCD_RS = 0;
  SMB_DATA_OUT[0] = 0x0F;// 0000 1100 0C
  SMB0CN0_STA = 1;
  T0_Waitms (100);
}


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
