/*
 * SB1_SMBus_Master_Multibyte.h
 *
 *  Created on: Jun 2, 2014
 *      Author: jiguo1
 */

#ifndef EFM8SB1_SMBUS_MASTER_MULTIBYTE_MAIN_H_
#define EFM8SB1_SMBUS_MASTER_MULTIBYTE_MAIN_H_

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define  SYSCLK         24500000       // System clock frequency in Hz


// Status vector - top 4 bits only
#define  SMB_MTSTA      0xE0           // (MT) start transmitted
#define  SMB_MTDB       0xC0           // (MT) data byte transmitted
#define  SMB_MRDB       0x80           // (MR) data byte received
// End status vector definition

#define  NUM_BYTES_WR   10              // Number of bytes to write
                                       // Master -> Slave
#define  NUM_BYTES_RD   10              // Number of bytes to read
                                       // Master <- Slave


// Global holder for SMBus data.
// All transmit data is read from here
extern uint8_t SMB_DATA_OUT[NUM_BYTES_WR];


#endif /* EFM8SB1_SMBUS_MASTER_MULTIBYTE_MAIN_H_ */

