//This is a preprocessor directive that includes the necessary header file for the specific microcontroller being used. This file contains definitions and configurations for the microcontroller's registers and peripherals.
#include <xc.h> 

// The void main(void) function is the entry point of the program. It is the starting point of execution.
void main(void)
{
    TRISD = 0;  //TRISD sets the direction of the port D pins as output
    LATD = 0;  //LATD sets the initial output values of those pins to logic low (0).
    unsigned int number[5] = {1, 1, 1, 1, 1}; //This line declares an unsigned integer array named number with a size of 5. It initializes each element of the array with the value 1.
    unsigned int sum = 0; //Here, an unsigned integer variable named sum is declared and initialized to 0. This variable will be used to store the sum of the elements in the number array.

    // This is a for loop that iterates over the elements of the number array. 
    // It starts with i equal to 0 and continues as long as i is less than 5. 
    // In each iteration, the value of number[i] is added to the sum variable.
    for (unsigned int i = 0; i < 5; i++)
    {
        sum = sum + number[i];
    }

    PORTD = sum; //Finally, the value of the sum variable is assigned to the PORTD register. This will set the output values of the port D pins to the calculated sum.
    return;
}
