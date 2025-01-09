/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Tony Liu
Student ID#: 024672131
Email      : tliu55@myseneca.ca
Section    : E

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//6. Display entered phone #

void displayFormattedPhone(const char* number);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//1. Check if input is an integer

int inputInt();

//2. Check if integer is positive

int inputIntPositive();

//3. Check if integer is within variable range

int inputIntRange(int lRange, int uRange);

//4. Check if input is a single char

char inputCharOption(const char validChar[]);

//5. Check if string fits in variable range

void inputCString(char* word, int min, int max);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
