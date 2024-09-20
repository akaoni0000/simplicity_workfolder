#include <SI_EFM8SB1_Register_Enums.h>
#include "EFM8SB1_SMBus_Master_Multibyte.h"
int aaa=0;
extern bbb;
extern start_flag;
extern data_count;
extern LCD_RS;
//-----------------------------------------------------------------------------
SI_INTERRUPT(SMBUS0_ISR, SMBUS0_IRQn)
{
  bool FAIL = 0;
  static uint8_t sent_byte_counter;
  static uint8_t rec_byte_counter;

  if (SMB0CN0_ARBLOST == 0)                   // Check for errors
  {
    switch (SMB0CN0 & 0xF0)           // Status vector
    {
     // Master Transmitter/Receiver: START condition transmitted.
     case SMB_MTSTA:
      SMB0DAT = 0x7C;
      SMB0CN0_STA = 0;                   // Manually clear START bit
      rec_byte_counter = 0;      // Reset the counter
      sent_byte_counter = 0;     // Reset the counter
      break;

     case SMB_MTDB:
      if (SMB0CN0_ACK)                   // Slave SMB0CN0_ACK?
      {
          if (sent_byte_counter <= 1)
          {
                     if(sent_byte_counter == 0){
                         if(LCD_RS==0){
                             SMB0DAT = 0x00;
                         }
                         else if(LCD_RS==1){
                             SMB0DAT = 0x40;
                         }
                     }
                     else if(sent_byte_counter == 1){
                         SMB0DAT = SMB_DATA_OUT[0];
                     }
                     sent_byte_counter++;
          }
          else
          {
              SMB0CN0_STO = 1;          // Set SMB0CN0_STO to terminate transfer
                         //SMB_BUSY = 0;     // And free SMBus interface
          }
      }
      break;
    } // end switch
  }

  SMB0CN0_SI = 0;                             // Clear interrupt flag
}





