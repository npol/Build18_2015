/*
 * cc2500.h
 *
 *  Created on: Dec 30, 2014
 *      Author: Nishant Pol
 */

#ifndef CC2500_H_
#define CC2500_H_

#include <msp430.h>
#include "utils.h"
#include "spi.h"

uint8_t read_status_reg(uint8_t stat_reg);
uint8_t strobe_cmd(uint8_t strobe_reg);
uint8_t read_cfg_reg(uint8_t cfg_reg);
uint8_t write_cfg_reg(uint8_t cfg_reg, uint8_t data);
uint8_t read_status_byte(void);

/** Configuration Registers, Preserved in sleep **/
#define REG_IOCFG2      0x00
#define REG_IOCFG1      0x01
#define REG_IOCFG0      0x02
#define REG_FIFOTHR     0x03
#define REG_SYNC1       0x04
#define REG_SYNC0       0x05
#define REG_PKTLEN      0x06
#define REG_PKTCTRL1    0x07
#define REG_PKTCTRL0    0x08
#define REG_ADDR        0x09
#define REG_CHANNR      0x0a
#define REG_FSCTRL1     0x0b
#define REG_FSCTRL0     0x0c
#define REG_FREQ2       0x0d
#define REG_FREQ1       0x0e
#define REG_FREQ0       0x0f
#define REG_MDMCFG4     0x10
#define REG_MDMCFG3     0x11
#define REG_MDMCFG2     0x12
#define REG_MDMCFG1     0x13
#define REG_MDMCFG0     0x14
#define REG_DEVIATN     0x15
#define REG_MCSM2       0x16
#define REG_MCSM1       0x17
#define REG_MCSM0       0x18
#define REG_FOCCFG      0x19
#define REG_BSCFG       0x1a
#define REG_AGCTRL2     0x1b
#define REG_AGCTRL1     0x1c
#define REG_AGCTRL0     0x1d
#define REG_WOREVT1     0x1e
#define REG_WOREVT0     0x1f
#define REG_WORCTRL     0x20
#define REG_FREND1      0x21
#define REG_FREND0      0x22
#define REG_FSCAL3      0x23
#define REG_FSCAL2      0x24
#define REG_FSCAL1      0x25
#define REG_FSCAL0      0x26
#define REG_RCCTRL1     0x27
#define REG_RCCTRL0     0x28
#define REG_FSTEST      0x29
#define REG_PTEST       0x2a
#define REG_AGCTEST     0x2b
#define REG_TEST2       0x2c
#define REG_TEST1       0x2d
#define REG_TEST0       0x2e

/** Strobe Registers **/
#define STR_SRES        0x30
#define STR_SFSTXON     0x31
#define STR_SXOFF       0x32
#define STR_SCAL        0x33
#define STR_SRX         0x34
#define STR_STX         0x35
#define STR_SIDLE       0x36
#define STR_SWOR        0x38
#define STR_SPWD        0x39
#define STR_SFRX        0x3a
#define STR_SFTX        0x3b
#define STR_SWORRST     0x3c
#define STR_SNOP        0x3d

/** Status Registers, Reset in sleep **/
#define STA_PARTNUM     0xf0
#define STA_VERSION     0xf1
#define STA_FREQEST     0xf2
#define STA_LQI         0xf3
#define STA_RSSI        0xf4
#define STA_MARCSTATE   0xf5
#define STA_WORTIME1    0xf6
#define STA_WORTIME0    0xf7
#define STA_PKTSTATUS   0xf8
#define STA_VCO_VC_DAC  0xf9
#define STA_TXBYTES     0xfa
#define STA_RXBYTES     0xfb
#define STA_RCCTRL1_STA 0xfc
#define STA_RCCTRL0_STA 0xfd

#define PATABLE         0x3e
#define FIFO            0x3f



#endif /* CC2500_H_ */
