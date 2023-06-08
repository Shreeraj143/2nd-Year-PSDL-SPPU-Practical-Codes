#include <xc.h> //xc.h provides definitions and settings specific to the PIC microcontroller
#include <p18f4550.h> //p18f4550.h is a device-specific header file for the PIC18F4550 microcontroller

void delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
    {
        for (j = 0; j < 5000; j++);
    }
}

void main(void)
{
    TRISB = 0x00; //sets the TRISB register to 0x00, configuring all pins of PORTB as outputs.
    LATB = 0xFF; //sets the LATB register to 0xFF, which means setting all pins of PORTB to high (logic level 1).
    while (1)
    {
        LATB = ~LATB; //toggles the value of LATB
        delay(200);
    }
}
