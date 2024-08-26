#include <SI_EFM8SB1_Register_Enums.h>
#include "InitDevice.h"
#include "EFM8SB1_SMBus_Master_Multibyte.h"

uint8_t SMB_DATA_IN[NUM_BYTES_RD];
uint8_t SMB_DATA_OUT[NUM_BYTES_WR];
uint8_t TARGET;
volatile bool SMB_BUSY;
volatile bool SMB_RW;
uint16_t NUM_ERRORS;

SI_SBIT(DISP_EN, SFR_P2, 7);
#define DISP_BC_DRIVEN 0
#define DISP_EFM8_DRIVEN 1
SI_SBIT(SDA, SFR_P1, 1);
SI_SBIT(SCL, SFR_P1, 3);

void SMB_Write(void);
void SMB_Read(void);
void T0_Waitms(uint8_t ms);

void SiLabs_Startup(void) {
  // Disable the watchdog here
}

void main(void) {
  volatile uint8_t dat;
  volatile uint8_t data_count;
  uint8_t i;
  //enter_DefaultMode_from_RESET();
  //DISP_EN = DISP_BC_DRIVEN;

//  while (!SDA) {
//      XBR1 = 0x40;
//      SCL = 0;
//      for (i = 0; i < 255; i++);
//      SCL = 1;
//      while (!SCL);
//      for (i = 0; i < 10; i++);
//      XBR1 = 0x00;
//  }

  enter_Mode2_from_DefaultMode();
  //LED0 = LED_OFF;



  //テストコード
  dat = 0;
  NUM_ERRORS = 0;

  SMB_Write();
  while (1) {}
}






//サポート関数
void SMB_Write(void) {
    PCA0MD = 0x00;
    SMB0CN0_STA = 1;
    SMB0ADR = 0xF9;
    SMB0DAT = 0xAC;
}

void SMB_Read(void) {
    while (SMB_BUSY);
    SMB_BUSY = 1;
    SMB_RW = 1;
    SMB0CN0_STA = 1;
    while (SMB_BUSY);
}

void T0_Waitms(uint8_t ms) {
    TCON &= ~0x30;
    TMOD &= ~0x0f;
    TMOD |= 0x01;
    CKCON0 |= 0x04;

    while (ms) {
        TCON_TR0 = 0;
        TH0 = ((-SYSCLK/1000) >> 8);
        TL0 = ((-SYSCLK/1000) & 0xFF);
        TCON_TF0 = 0;
        TCON_TR0 = 1;
        while (!TCON_TF0);
        ms--;
    }
    TCON_TR0 = 0;
}
