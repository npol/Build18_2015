/*
 * spi..h
 *
 *  Created on: Dec 30, 2014
 *      Author: Nishant Pol
 */

#ifndef SPI__H_
#define SPI__H_

#include <msp430.h>
#include "utils.h"

/* SPI Macros: Active Low */
#define SPI_CS_ASSERT           (P1OUT &= ~BIT4)
#define SPI_CS_DEASSERT         (P1OUT |= BIT4)
#define SPI_TXINT_ENABLE        (IE2 |= UCB0TXIE)
#define SPI_TXINT_DISABLE       (IE2 &= ~UCB0TXIE)
#define SPI_RXINT_ENABLE        (IE2 |= UCB0RXIE)
#define SPI_RXINT_DISABLE       (IE2 &= ~UCB0RXIE)
#define SPI_BUSY                (!spi_rx_done)

void spi_tx(uint8_t* data, uint8_t num_bytes);
void spi_tx_byte(uint8_t data);
void spi_rx(uint8_t* buf, uint8_t num_bytes);
uint8_t spi_rx_byte(void);

/* SPI Buffers */
#define SPI_BUF_SIZE 8
extern volatile uint8_t spi_txbuf[];
extern volatile uint8_t spi_rxbuf[];
extern volatile uint8_t spi_txbuf_ptr;
extern volatile uint8_t spi_rxbuf_ptr;
extern volatile uint8_t num_bytes_to_tx;
extern volatile uint8_t spi_tx_done;
extern volatile uint8_t spi_rx_done;




#endif /* SPI__H_ */
