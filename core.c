#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"
#include "clinic.h"


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}
//6. Display number in phone format
void displayFormattedPhone(const char* number)
{
    int i, lengthCheck, numCheck;
    char acceptInput[] = { '1', '2', '3', '4', '5','6','7','8','9','0' };
    i = 0;
    lengthCheck = 0;
    numCheck = 0;


    if (number == NULL)
    {
        printf("(___)___-____");
    }
    else
    {
        lengthCheck = strlen(number);

        for (i = 0; number[i] != '\0'; i++)
        {
            if (strchr(acceptInput, number[i]) != 0)
            {
                numCheck++;
            }
        }

        if (lengthCheck != 10 || numCheck != 10)
        {
            printf("(___)___-____");
        }
        else
        {
            //print out in phone number format
            printf("(");
            for (i = 0; i < lengthCheck; i++)
            {
                printf("%c", number[i]);
                if (i == 2)
                {
                    printf(")");
                }
                else if (i == 5)
                {
                    printf("-");
                }
            }
        }
    }
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//check if input is an single integer
int inputInt()
{
    int scanResult;
    int intCheck;
    char newLine;


    do
    {
        scanResult = scanf("%d%c", &intCheck, &newLine);

        if (newLine != '\n' || scanResult != 2)
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
    } while (newLine != '\n' || scanResult != 2);

    return intCheck;

}

//check if integer is positive
int inputIntPositive()
{
    int positiveCheck;

    do
    {
        positiveCheck = inputInt();
        if (positiveCheck < 1)
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (positiveCheck < 1);


    return positiveCheck;
}

//make sure integer is between given range

int inputIntRange(int lRange, int uRange)
{
    int rangeCheck;

    do
    {
        rangeCheck = inputInt();
        if (rangeCheck<lRange || rangeCheck>uRange)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lRange, uRange);
        }
    } while (rangeCheck<lRange || rangeCheck>uRange);

    return rangeCheck;
}

//check if input is a single char
char inputCharOption(const char validChar[])

{
    int scanResult;
    char newLine;
    char charCheck;
    do
    {
        scanResult = scanf("%c%c", &charCheck, &newLine);

        if (newLine !='\n')
        {
            clearInputBuffer();
        }

        if (strchr(validChar, charCheck) == 0 || scanResult != 2 || newLine != '\n')
        {
            printf("ERROR: Character must be one of [%s]: ", validChar);
        }

    } while (strchr(validChar, charCheck) == 0 || scanResult != 2 || newLine != '\n');

    return charCheck;
}

//check if string input matches a given range
void inputCString(char* word, int min, int max)
{
    int lengthCheck;
    //string array in main function is too small to handle given tests, local string to hold chars in function
    char localWord[50];


    do
    {

        scanf("%[^\n]%*c", localWord);

        lengthCheck = strlen(localWord);


        if (min == max && (lengthCheck > max || lengthCheck < min))
        {
            printf("Invalid %d-digit number! Number: ", max);


        }
        else if (lengthCheck > max)
        {
            printf("ERROR: String length must be no more than %d chars: ", max);

        }
        else if (lengthCheck > max || lengthCheck < min)
        {
            printf("ERROR: String length must be between %d and %d chars: ", min, max);

        }
        else
        {
            strcpy(word, localWord);
        }
    } while (lengthCheck > max || lengthCheck < min);

}



