#include <xc.h>             // The xc.h header file is commonly used in Microchip PIC microcontroller programming. It contains various definitions, settings, and macros specific to the particular microcontroller family or series being used.
#include <P18f4550.h>       // The P18f4550.h header file is specific to the PIC18F4550 microcontroller. It is a device-specific header file that provides access to register definitions, configuration bits, and other resources specific to the PIC18F4550 microcontroller.
#define LCD_EN LATAbits.LA1 // It suggests that this bit is used for controlling the Enable (EN) pin of an LCD module.
#define LCD_RS LATAbits.LA0 // It implies that this bit is used for controlling the Register Select (RS) pin of the LCD, which differentiates between command and data mode.
#define LCDPORT LATB        // It implies that this register is used for sending data or commands to the data bus of the LCD module.

void lcd_delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
    {
        for (j = 0; j < 100; j++);
    }
}

void SendInstruction(unsigned char command)
{
    LCD_RS = 0;        // RS low : COMMAND/INSTRUCTION; subsequent data being sent is an instruction for the LCD module.
    LCDPORT = command; // Here, the command value is written to the data bus to send the specific instruction to the LCD module.
    LCD_EN = 1;        // EN High : The LCD_EN pin controls the enabling or disabling of the LCD module. Setting it to 1 enables the module to process the instruction.
    lcd_delay(10);     // This delay function introduces a delay of 10 milliseconds, providing sufficient time for the LCD module to process the instruction.
    LCD_EN = 0;        // This disables the LCD module after processing the instruction. The comment clarifies that the command is sampled (read) by the LCD module at the falling edge of the Enable signal.
    lcd_delay(10);     // Another lcd_delay(10) is introduced to ensure a delay after disabling the module.
}

void SendData(unsigned char lcddata)
{
    LCD_RS = 1;        // RS HIGH : DATA; setting it to 1 indicates that the subsequent data being sent is actual display data rather than an instruction.
    LCDPORT = lcddata; // LCDPORT represents the data bus of the LCD module. Here, the lcddata value is written to the data bus to send it as display data to the LCD module.
    LCD_EN = 1;        // EN High; Setting it to 1 enables the module to process the data.
    lcd_delay(10);
    LCD_EN = 0;    // EN Low; data sampled(read) at EN falling edge
    lcd_delay(10); // Another lcd_delay(10) is introduced to ensure a delay after disabling the module.
}

void InitLCD(void)
{
    ADCON1 = 0x0F;         // The ADCON1 register is typically used to configure analog-to-digital converter (ADC) settings. In this case, setting it to 0x0F disables the ADC function on the corresponding pins, ensuring that they can be used for digital I/O.
    TRISB = 0x00;          // The TRISB register controls the direction of the data pins associated with the LCD module. By setting it to 0x00, all the pins in PORTB are configured as outputs, allowing data to be sent from the microcontroller to the LCD module.
    TRISAbits.RA0 = 0;     // RS pin ;These lines configure the direction of the RA0 and RA1 pins, which are associated with the Register Select (RS) and Enable (EN) pins of the LCD module, respectively. By setting them to 0, these pins are configured as outputs, allowing the microcontroller to control them.
    TRISAbits.RA1 = 0;     // EN pin
    SendInstruction(0x38); // Sets the LCD module to 8-bit mode, 2-line display, and 5x7 dot character font.
    SendInstruction(0x06); // Sets the entry mode, which determines how the cursor moves after writing to the display.
    SendInstruction(0x0C); // Turns on the display and turns off the cursor.
    SendInstruction(0x01); // Clears the display.
    SendInstruction(0x80); // Sets the cursor/address to the beginning of the first line.
}

unsigned char *String1 = " Microembedded"; // This line declares a variable named String1 as a pointer to an array of unsigned characters (unsigned char*). It assigns the memory address of the string literal " Microembedded" to String1. The string literal is a sequence of characters enclosed in double quotes. In this case, it represents the string " Microembedded".
unsigned char *String2 = " PIC-18F Board";

void main(void)
{
    InitLCD();
    while (*String1)
    {
        SendData(*String1);
        *String1++;
    }

    SendInstruction(0xC0); // set cursor/address to 2nd line
    while (*String2)
    {
        SendData(*String2);
        *String2++;
    }
    while (1);
}
