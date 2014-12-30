#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    /* Pin Setup */
    P1OUT = 0x00;
    P1DIR = BIT0;				//P1.0: debug LED
    P2OUT = 0x00;
    P2DIR = BIT1;				//P2.1: RFID out

    /* Clock Setup 8MHz SMCLK from DCO */
    if(CALBC1_8MHZ == 0xff) while(1);
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;

    /* TimerA1 Setup: 124.23kHz output on OUT1 */
    TA1CCR0 = 63;//frequency control
    TA1CCR1 = 30;//Duty cycle
    TA1CTL = TASSEL_2 + ID_0 + MC_1;
    TA1CCTL1 = OUTMOD_3;
    P2SEL |= BIT1;

    /* USCIA_UART setup: 9600baud */
    //9600baud No parity, 1stop, 8-bit, LSB first
    UCA0CTL1 |= UCSWRST;
    UCA0CTL1 = UCSSEL_2 + UCSWRST;//TODO: Change to UCSSEL_1 for ACLK
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
    UCB0CTL0 = UCCKPH + UCMST + UCMODE_0;
    UCB0CTL1 = UCSSEL_2 + UCSWRST;//TODO: Change to UCSSEL_1 for ACLK
    UCB0BR0 = 0x08;//1MHz
    P1SEL |= BIT5 + BIT6 + BIT7;
    P1SEL2 |= BIT5 + BIT6 + BIT7;
    P1DIR |= BIT4;//CS
    UCB0CTL1 &= ~UCSWRST;
    IE2 |= UCB0TXIE;

    	//TODO: Use Timer0 to call strobe
    //TODO: UART Buffer

    __bis_SR_register(GIE);

    while(1){
    	TA1CCR1 = 10;
    	int n = 1;
    	int i = 0;
    	for(i=0; i<n*64; i++);
    	TA1CCR1 = 30;
    	for(i=0; i<n*64; i++);
    }
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void){
	if(IFG2 & UCA0TXIFG){
		/* UART Tx Interrupt: TXBUF ready for new character */
		UCA0TXBUF = 0x4f;
	} else if(IFG2 & UCB0TXIFG){
		int i;
		for(i=0; i<8; i++);//Delay for CS to end after SCK ends
		P1OUT |= BIT4;
		/* SPI Tx Interrupt: TXBUF ready for new character */
		P1OUT &= ~BIT4;
		UCB0TXBUF = 0x33;
	}
}
