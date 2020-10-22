/*
* FILE : cA2.cpp
* PROJECT : SENG1000 - Assignment #2
* PROGRAMMER : Silas Bartha
* FIRST VERSION : 2020-10-08
* DESCRIPTION :
*/

#include <stdlib.h>
#include<stdio.h>
#include <string.h>

#pragma warning(disable: 4996)

#define BASE_AND_EXPONENT_MIN 1
#define BASE_MAX 25
#define EXPONENT_MAX 5
#define GETNUM_ARRAY_SIZE 121

void showMenu(void);
int getNum(void);
int handleChange(const char* component, int currentValue);
int calculatePower(int base, int exponent);
int checkRange(int val, int min, int max);

int main(void)
{
    enum Options {CHANGE_B, CHANGE_E, DISPLAY, EXIT};
    int base = 1;
    int exponent = 1;
    while (true)
    {
        showMenu();
        enum Options o = (Options)(getNum()-1);
        switch (o)
        {
        case CHANGE_B:
            base = handleChange("base", base);
            break;
        case CHANGE_E:
            exponent = handleChange("exponent", exponent);
            break;
        case DISPLAY:
            printf("\nResult: %d ^ %d = %ld\n", base, exponent, calculatePower(base, exponent));
            break;
        case EXIT:
            exit(0);
            break;
        default:
            printf("Invalid selection, please try again.\n");
            break;
        }
    }
}

/*
* FUNCTION : showMenu
*
* DESCRIPTION : Prints out a properly-formatted menu
*
* PARAMETERS : void
*
* RETURNS : void
*/
void showMenu(void)
{
    printf("\n%s\n\n\t%s\n\t%s\n\t%s\n\t%s\n\n%s",
        "Power Menu:",
        "1. Change base",
        "2. Change exponent",
        "3. Display base raised to exponent",
        "4. Exit program",
        "Option? ");
}

/*
* FUNCTION : handleChange
*
* DESCRIPTION : Requests and validates a positive integer value from the user, to be used as a component in the power calculation.
*
* PARAMETERS : const char* component : The component of the power to be changed, either 'base' or 'exponent'
*
* RETURNS : int : The recieved integer value to be assigned.
*/
int handleChange(const char* component, int currentValue)
{
    printf("\nPlease enter a new positive integer to be used as the power's %s: ", component);
    int input = getNum();
    int max = (strcmp(component,"base")==0) ? BASE_MAX : EXPONENT_MAX;
    if (!checkRange(input, BASE_AND_EXPONENT_MIN, max)) 
    {
        printf("\nUnable to set %s value to %d: Please keep %s value between %d and %d.\n", component, input, component, BASE_AND_EXPONENT_MIN, max);
        input = currentValue;
    }

    return input;
}

/*
* FUNCTION : checkRange
*
* DESCRIPTION : Checks if a given value is in a given range
*
* PARAMETERS : int value : value to test
*              int min : minimum of test range
*              int max : maximum of test range
*
* RETURNS : int : 1 if value is within range, 0 otherwise
*/
int checkRange(int val, int min, int max) 
{
    return (int)((val >= min)&&(val <= max));
}

/*
* FUNCTION : calculatePower
*
* DESCRIPTION : Calculates the result of the specified base raised to the specified component
*               Remember: powers should not be thought of as the base multiplied by itself one less time than the exponent value,
*               but rather 1 multiplied by the base just as many times as the exponent value, e.g 0^0 =/= 0 x 0(-1 times), 0^0 == 1 x 0(0 times),
*               which is why 0^0 = 1 and not undefined.
*
* PARAMETERS : int base : base component of power
*              int exponent : exponent component of power 
*
* RETURNS : int : The result of the base raised to the power of the exponent. As I'm working with positive integer values only,
*                           unsigned long offers the broadest range of use.
*/
int calculatePower(int base, int exponent)
{
    int result = 1;
    for (int i = 0; i < exponent; i++) 
    {
        result *= base;
    }
    return result;
}

/*
* FUNCTION : getNum
*
* DESCRIPTION : Gets a user integer input
*
* PARAMETERS : void
*
* RETURNS : int : a valid user integer input, or -1 if input was invalid
*/
int getNum(void)
{
    /* the array is 121 bytes in size; we'll see in a later lecture how we can improve this code */
    char record[GETNUM_ARRAY_SIZE] = { 0 }; /* record stores the string */
    int number = 0;
    /* NOTE to student: indent and brace this function consistent with your others */
    /* use fgets() to get a string from the keyboard */
    fgets(record, 121, stdin);
    /* extract the number from the string; sscanf() returns a number
     * corresponding with the number of items it found in the string */
    if (sscanf(record, "%d", &number) != 1)
    {
        /* if the user did not enter a number recognizable by
         * the system, set number to -1 */
        number = -1;
    }
    return number;
}