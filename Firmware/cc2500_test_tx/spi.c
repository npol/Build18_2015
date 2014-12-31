/*
 * spi.c
 *
 *  Created on: Dec 30, 2014
 *      Author: Nishant Pol
 */

#include "spi.h"

volatile uint8_t spi_txbuf[SPI_BUF_SIZE];
volatile uint8_t spi_rxbuf[SPI_BUF_SIZE];
volatile uint8_t spi_txbuf_ptr = 0;
volatile uint8_t spi_rxbuf_ptr = 0;
volatile uint8_t num_bytes_to_tx = 0;
volatile uint8_t spi_tx_done = 0;
volatile uint8_t spi_rx_done = 0;

/** SPI HAL Interface **/
void spi_tx(uint8_t* data, uint8_t num_bytes){
    SPI_CS_ASSERT;
    uint8_t i;
    for(i=0; i < num_bytes; i++){
        spi_txbuf[i] = data[i];
    }
    num_bytes_to_tx = num_bytes;
    spi_tx_done = 0;
    spi_txbuf_ptr = 0;
    spi_rxbuf_ptr = 0;
    SPI_TXINT_ENABLE;
    SPI_RXINT_ENABLE;
    return;
}

void spi_rx(uint8_t* buf, uint8_t num_bytes){
    uint8_t i;
    for(i = 0; i < num_bytes; i++){
        buf[i] = spi_rxbuf[i];
    }
    spi_rx_done = 0;
    return;
}




