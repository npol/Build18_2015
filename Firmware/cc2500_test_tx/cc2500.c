/*
 * cc2500.c
 *
 *  Created on: Dec 30, 2014
 *      Author: Nishant Pol
 */

#include "cc2500.h"

uint8_t get_status_reg(uint8_t stat_reg){
    //TODO: Implement
    return 0;
}

uint8_t strobe_cmd(uint8_t strobe_reg){
    spi_tx_byte(strobe_reg);
    return spi_rx_byte();
}

uint8_t read_cfg_reg(uint8_t cfg_reg){
    uint8_t temp_buf[2];
    temp_buf[0] = cfg_reg;
    //Don't care about second byte
    spi_tx(temp_buf, 2);
    spi_rx(temp_buf, 2);
    return temp_buf[1];//Value of register to read
}

uint8_t write_cfg_reg(uint8_t cfg_reg, uint8_t data){
    uint8_t temp_buf[2];
    temp_buf[0] = cfg_reg;
    temp_buf[1] = data;
    spi_tx(temp_buf, 2);
    spi_rx(temp_buf, 2);
    return temp_buf[0];//Chip status byte
}

uint8_t read_status_byte(void){
    return strobe_cmd(STR_SNOP);
}




