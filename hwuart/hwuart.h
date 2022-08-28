//  hwuart.h
//  EZDenki.com, Ver. 0.9, 8/2022
//  See hwuart.c for details.

#ifndef HWHWU_H
#define HWHWU_H

// Note that following F_CPU and BAUDRATE defines/macros may be
// set in the Makefile.
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef BAUDRATE
#define BAUDRATE 9600
#endif

// The following 6-line macro can be also defined in the main code
// if desired. Note that the DEBUG define should also be either
// in the Makefile or in the main calling C code.
// Set DEBUG to 0 to supress debug output, or 1 to include it.
// =================================
#define DEBUG 1
#if DEBUG == 1
#define debug(x) HWU_TxString( x)
#else
#define debug(x)
#endif
// =================================

void HWU_Init( unsigned long USART_BAUDRATE );
char HWU_RxChar();
void HWU_TxChar( char );
void HWU_TxString( char *str );

#endif
