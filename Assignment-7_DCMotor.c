#include <p18f4550.h>
// unsigned char count = 0;
// bit TIMER, SPEED_UP;

void timer2Init(void)
{
    T2CON = 0b00000010;
    PR2 = 0x95;
}
void delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
    {
        for (j = 0; j < 1000; j++);
    }
}
void main()
{
    unsigned int i;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    LATCbits.LATC1 = 0;
    CCP1CON = 0b00111100;
    // CCP1CON<4::5> = <1::1> 
    CCPR1L = 0x0F; 
    timer2Init();
    TMR2ON = 1;
    while (1)
    {
        for (i = 15; i < 150; i++)
        {
            CCPR1L = i;
            delay(100);
        }
        for (i = 150; i > 15; i--)
        {
            CCPR1L = i;
            delay(100);
        }
    }
}