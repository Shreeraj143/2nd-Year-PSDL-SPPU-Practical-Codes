#include <xc.h>
void main(void)
{
    int i;
    int source[] = {0x21, 0x22, 0x23, 0x24, 0x25};
    int dest[] = {0x00, 0x00, 0x00, 0x00, 0x00};
    for (i = 0; i <= 4; i++)
    {
        dest[i] = source[i];
    }
    return;
}