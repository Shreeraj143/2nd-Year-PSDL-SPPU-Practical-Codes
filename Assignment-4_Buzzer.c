//The given code snippet is an interrupt service routine (ISR) for Timer1 in a PIC18F4550 microcontroller.



#include <xc.h>  // xc.h provides definitions and settings specific to the PIC microcontroller
#include<pic18f4550.h>  //pic18f4550.h is a device-specific header file for the PIC18F4550 microcontroller.
#define Buzzer LATAbits.LATA5  //This line defines a macro Buzzer that represents the specific pin LATA5 of the LATA register. 


unsigned int count = 0; //This variable will be used to count the number of interrupts that have occurred.


// This section defines an interrupt service routine (ISR) for Timer1. It specifies that whenever a Timer1 interrupt occurs, the code inside the curly braces { } will be executed.
void interrupt Timer1_ISR()
{
    if (TMR1IF == 1) //This condition checks if the Timer1 interrupt flag (TMR1IF) is set to 1, indicating that a Timer1 interrupt has occurred.
    {
        TMR1L = 0x20; //These lines set the low and high bytes of Timer1 (TMR1L and TMR1H) to specific values. This sets the initial value of Timer1 to 0x20D1. 
        TMR1H = 0xD1; //This is done to set the period of the Timer1 interrupt.
        count++;
        if (count >= 1000) //If the condition is true, it means that approximately 1000 Timer1 interrupts have occurred, and the code inside the if statement will be executed.
        {
            Buzzer = ~Buzzer; //In this case, the buzzer pin is toggled by using the Buzzer macro, and the count variable is reset to 0.
            count = 0;
        }
    }
    TMR1IF = 0;  //This line clears the Timer1 interrupt flag (TMR1IF) by setting it to 0. This is necessary to acknowledge and clear the interrupt condition.
}


void main()
{
    // These lines configure the data direction registers (TRISB and TRISAbits.TRISA5) to set all pins of PORTB and pin RA5 of PORTA as outputs. 
    TRISB = 0; 
    TRISAbits.TRISA5 = 0;

    GIE = 1; //  (Global Interrupt Enable) is set to 1, enabling global interrupts.
    PEIE = 1; // (Peripheral Interrupt Enable) is set to 1, enabling peripheral interrupts.
    TMR1IE = 1; // (Timer1 Interrupt Enable) is set to 1, enabling Timer1 interrupts.
    TMR1IF = 0; //  (Timer1 Interrupt Flag) is set to 0, clearing the Timer1 interrupt flag.
    T1CON = 0x80; // This line sets the Timer1 control register (T1CON) to 0x80. This configuration sets the prescaler to 1:1 and sets the Timer1 oscillator as the clock source.
    TMR1L = 0x20; // (Timer1 Low Byte Register) is set to 0x20, representing the lower 8 bits of the Timer1 initial value.
    TMR1H = 0xD1; // (Timer1 High Byte Register) is set to 0xD1, representing the upper 8 bits of the Timer1 initial value. Hence initial value is set to 0x20D1
    TMR1ON = 1; // This line sets the Timer1 ON bit (TMR1ON) to 1, enabling Timer1. Timer1 will start counting according to the configured prescaler and clock source.
    while (1); // This line starts an infinite loop (while (1)) to keep the microcontroller continuously running. The program will remain in this loop indefinitely, allowing the microcontroller to respond to interrupts and perform any required tasks.
}
