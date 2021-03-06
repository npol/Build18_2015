#include <msp430.h> 
#include "utils.h"
#include "spi.h"
#include "cc2500.h"

/* Debug LED Macros */
#define DBG_ASSERT              (P1OUT |= BIT0)
#define DBG_DEASSERT            (P1OUT &= ~BIT0)

/** Application Functions **/
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    /* Pin Setup */
    P1OUT = 0x00;
    P2OUT = 0x00;
    P3OUT = 0x00;
    P1DIR = BIT0;				//P1.0: LED out

    /* Clock Setup 8MHz SMCLK from DCO */
    if(CALBC1_8MHZ == 0xff) while(1);
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;

    /* USCIA_UART setup: 9600baud */
    //9600baud No parity, 1stop, 8-bit, LSB first
    UCA0CTL1 |= UCSWRST;
    UCA0CTL1 = UCSSEL_2 + UCSWRST;
    UCA0BR1 = 0x03;//UCBRx = 833
    UCA0BR0 = 0x41;
    UCA0MCTL = UCBRS_2;
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;
    UCA0CTL1 &= ~UCSWRST;
    IE2 |= UCA0TXIE;

    /* USCIB_SPI setup */
    //1MHZ Clk, LSB first
    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 = UCCKPH + UCMST + UCMSB + UCMODE_0;//UCSYNC?
    UCB0CTL1 = UCSSEL_2 + UCSWRST;
    UCB0BR0 = 0x08;//1MHz

    P1SEL |= BIT5 + BIT6 + BIT7; //P1.5: SCK; P1.6: MISO; P1.7: MOSI
    P1SEL2 |= BIT5 + BIT6 + BIT7;
    P1DIR |= BIT4;//P1.4: CS
    UCB0CTL1 &= ~UCSWRST;

    __bis_SR_register(GIE);

    uint8_t data[] = {0x10, 0x11, 0x12, 0x13};
    while(1){
        /*
        spi_tx(data, 4);
        uint8_t data_rx[] = {0, 0, 0, 0};
        while(SPI_BUSY);
        spi_rx(data_rx, 4);
        if((data[0] != data_rx[0]) && (data[1] != data_rx[1]) && (data[2] != data_rx[2]) && (data[3] != data_rx[3])) DBG_DEASSERT;
        else DBG_ASSERT;
        uint16_t i;
        for(i=0; i<1000; i++);
        */
        read_status_byte();
        write_cfg_reg(REG_ADDR, 0x4f);
        uint16_t i;
        for(i=0; i<1000; i++);
    }
}





/** UART and SPI Interrupts **/
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void){
	if(IFG2 & UCA0TXIFG){
		/* UART Tx Interrupt: TXBUF ready for new character */
		UCA0TXBUF = 0x4f;
	} else if(IFG2 & UCB0TXIFG){
	    /* SPI Tx Interrupt: TXBUF ready for new character */
		if(num_bytes_to_tx == 0){
		    spi_tx_done = 1;
		    SPI_TXINT_DISABLE;
		} else {
		    UCB0TXBUF = spi_txbuf[spi_txbuf_ptr];
		    spi_txbuf_ptr++;
			num_bytes_to_tx--;
		}
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void){
    if(IFG2 & UCB0RXIFG){
        spi_rxbuf[spi_rxbuf_ptr] = UCB0RXBUF;
        spi_rxbuf_ptr++;
        if(spi_tx_done){
            spi_rx_done = 1;
            SPI_CS_DEASSERT;
        }
    }
}
