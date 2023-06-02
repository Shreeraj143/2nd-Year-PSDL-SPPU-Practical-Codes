#include <xc.h>
void main(void)
{
    TRISD = 0;
    LATD = 0;
    unsigned int number[5] = {1, 1, 1, 1, 1};
    unsigned int sum = 0;
    for (unsigned int i = 0; i < 5; i++)
    {
        sum = sum + number[i];
    }
    PORTD = sum;
    return;
}
