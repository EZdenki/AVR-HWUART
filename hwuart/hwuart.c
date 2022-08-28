/*  hwuart.c
    EZDenki.com, Ver. 0.9, 8/2022

    Simple hardware UART serial library for AVRs that have built-in USARTs.
    Allows for synchronous serial (i.e. RS-232) communication between the AVR
    and other serial devices, such as a serial terminal.

    This is set up to work on the ATTiny2313 but should also work for other
    AVRs, possibly with some tweaking.

    Note that possible baudrates are highly dependent upon the clock speed
    used. If a greater range of baud rates are required, then a software UART
    solution might be preferred.

    BAUDRATE (the desired baudrate) and F_CPU (AVR operating clock frequency)
    must be specified in hwuart.h or passed via Makefile.
*/

#include <avr/io.h>
#include <stdlib.h>
#include "hwuart.h"


//  NOTE: If F_CPU and BAUDRATE are not defined in Makefile, then
//  uncomment the following:
//#define F_CPU 8000000
//#define BAUDRATE 9600

//  BAUD_PRESCALE is used to set the USART Baud Rate Registers (UBRRH and UBRRL)
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// Set DEBUG to 1 for serial debugging output or to 0 for no output.
// Thanks to Youtuber Ralph S. Bacon, vid. #224, for this tip!
//#define DEBUG 1


//#if DEBUG == 1
//#define debug(x) HWU_SendString( x )
//#else
//#define debug(x)
//#endif


void HWU_Init(unsigned long USART_BAUDRATE)
{
    UCSRB |= (1 << TXEN) | (1 << RXEN) ;                 /* Turn on transmission and reception */
    UCSRC |= (0 << UMSEL) | (1 << UCSZ0) | (1 << UCSZ1); /* Use 8-bit character sizes */
    UBRRL = BAUD_PRESCALE;                               /* Load lower 8-bits of the baud rate value */
    UBRRH = (BAUD_PRESCALE >> 8);                        /* Load upper 8-bits*/
}

char HWU_RxChar()
{
	while ( !(UCSRA & (1 << RXC)) );  /* Wait till data is received */
	return(UDR);			            /* Return the byte*/
}

void HWU_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
	UDR = ch ;
}

void HWU_TxString(char *str)
{
	uint8_t j=0;

	while (str[j]!=0)		/* Send string till null */
	{
		HWU_TxChar(str[j]);
		j++;
	}
}
