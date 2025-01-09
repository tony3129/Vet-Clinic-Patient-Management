#ifndef CORE_H
#define CORE_H


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//Display entered phone #

void displayFormattedPhone(const char* number);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Check if input is an integer

int inputInt();

//Check if integer is positive

int inputIntPositive();

//Check if integer is within variable range

int inputIntRange(int lRange, int uRange);

//Check if input is a single char

char inputCharOption(const char validChar[]);

//Check if string fits in variable range

void inputCString(char* word, int min, int max);

#endif // !CORE_H
