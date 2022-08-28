//  main.c
//  EZDeni.com, Ver. 0.9, 8/2022
//
//  Sample file to show serial ouput using hwuart library.
//  Connect the serial receive pin to the TXD pin on the AVR to see
//  the output.


#include <hwuart/hwuart.h>

int main()
{
    char inputChar;

    // Initialize the serial port.
    // BAUDRATE can be defined here, in Makefile, or in hwuart.h
    HWU_Init(BAUDRATE);

    // Output a string
    HWU_TxString("Hello HW UART!\n");

    // Output a debug message
    debug("This is Debug Output.\n");

    // Wait for serial input and echo out 1 character at a time.
    while (1)
    {
        inputChar=HWU_RxChar();
        HWU_TxString("Input: ");
        HWU_TxChar( inputChar );
        HWU_TxChar( '\n' );
    }
}
