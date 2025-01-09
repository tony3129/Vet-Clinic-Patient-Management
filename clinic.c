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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)

void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, eligibleRecords;
    i = 0;
    eligibleRecords = 0;

    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        //check if there are any records to display
        if (patient[i].patientNumber > 0)
        {
            eligibleRecords++;
        }
    }

    for (i = 0; i < max; i++)
    {
        if (eligibleRecords == 0)
        {
            printf("*** No records found ***\n");
        }
        else if (patient[i].patientNumber > 0)
        {
            displayPatientData(&patient[i], fmt);
        }
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)

void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    printf("Search Options\n"
        "==========================\n"
        "1) By patient number\n"
        "2) By phone number\n");

    printf("..........................\n"
        "0) Previous menu\n"
        "..........................\n"
        "Selection: ");

    selection = inputIntRange(0, 2);

    switch (selection)
    {
    case 0:
        putchar('\n');
        ;
        break;
    case 1:
        searchPatientByPatientNumber(patient, max);
        break;
    case 2:
        searchPatientByPhoneNumber(patient, max);
        break;
    }

}

// Add a new patient record to the patient array
// (Copy your code from MS#2)

void addPatient(struct Patient patient[], int max)
{
    int i, availSpace;
    availSpace = 0;

    for (i = 0; i < max && availSpace == 0; i++)
    {
        //check if there is any space for a new patient
        if (patient[i].patientNumber == 0)
        {
            availSpace++;
            i--;
        }
    }

    if (availSpace > 0)
    {
        patient[i].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[i]);
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)

void editPatient(struct Patient patient[], int max)
{
    int patientNumber, searchResult;
    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();
    putchar('\n');

    searchResult = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (searchResult == -1)
    {
        printf("ERROR: Patient record not found!");
    }
    else
    {
        menuPatientEdit(&patient[searchResult]);
    }

}

// Remove a patient record from the patient array
// (Copy your code from MS#2)

void removePatient(struct Patient patient[], int max)
{
    int patientNumber, searchResult;
    char patientRemoval;
    char removalOptions[] = "yn";
    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();


    searchResult = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (searchResult == -1)
    {
        printf("\nERROR: Patient record not found!\n");
    }
    else
    {
        //confirm removal choice, accepts both lowercase and uppercase inputs
        putchar('\n');
        displayPatientData(&patient[searchResult], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        patientRemoval = inputCharOption(removalOptions);
        if (patientRemoval == 'y' || patientRemoval == 'Y')
        {
            patient[searchResult].patientNumber = 0;
            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }

    }
    putchar('\n');
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:

void viewAllAppointments(struct ClinicData* data)
{
    int i, j, eligibleRecords;
    i = 0;
    eligibleRecords = 0;

    displayScheduleTableHeader(&data->appointments->date, ALL_RECORDS);
  
    //check if there are any appointments to display
    for (i = 0; i < (*data).maxAppointments; i++)
    {
        
        if ((*data).appointments[i].patientNumber > 0)
        {
            eligibleRecords++;
        }
    }

    //sort appointment dates in ascending order
    sortDates(*data, (*data).maxAppointments);

    //print schedule data if appointments found
    if (eligibleRecords == 0)
    {
        printf("*** No Appointments Found ***\n");
    }
    //compare both appointment patient ID and patient patient ID, display matching information
    else
    {
        for (i = 0; i < (*data).maxAppointments; i++)
        {
            if ((*data).appointments[i].patientNumber > 0)
            {
                j = matchPatientIndextoAppoinment(*data, i);
                displayScheduleData(&data->patients[j], &data->appointments[i], INCLUDE_DATE); 
            }

        }
    }
    putchar('\n');
}

// View appointment schedule for the user input date
// Todo:

void viewAppointmentSchedule(struct ClinicData data[])
{
    int year, month, day,i,j,flag, noMatch;
    i = 0;
    j = 0;
    flag = 1;
    noMatch = 0;

    //input dates
    inputAppointmentDate(&month, &year, &day);

    //sort dates in ascending order
    sortDates(*data, (*data).maxAppointments);

    putchar('\n');

    //display header with year, month, day match
    for (i = 0; i < (*data).maxAppointments && flag ==1; i++)
    {
        if (year == (*data).appointments[i].date.year && month == (*data).appointments[i].date.month && day == (*data).appointments[i].date.day)
        {
            flag = 0;
            displayScheduleTableHeader(&data->appointments[i].date, SINGLE_RECORDS);
        }
        else
        {
            noMatch++;
            if (noMatch==(*data).maxAppointments)
            {
                printf("*** No appointments found ***\n");
            }
        }
    }
    //display patient info and time of appointment
    for (i = 0; i < (*data).maxAppointments; i++)
    {
        if (year == (*data).appointments[i].date.year && month == (*data).appointments[i].date.month && day == (*data).appointments[i].date.day)
        {
            j = matchPatientIndextoAppoinment(*data, i);
            displayScheduleData(&data->patients[j], &data->appointments[i], NO_DATE);
        }
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
// Todo:

void addAppointment(struct Appointment appointments[], int appointMax, struct Patient patients[], int patientsMax)
{
    int i, availSpace, availAppoint, flag;
    int patientNumber, year, month, day, hour, min, searchResult;
    i = 0;
    availSpace = -1;
    availAppoint = 1;
    flag = 0;

    //check if there is any open appointment slot
    for (i = 0; i < appointMax && flag == 0; i++)
    {
        if (appointments[i].patientNumber == 0)
        {
            availSpace=i;
            flag = 1;
            
        }
    }
    
    //allow addition of appointment if open slot, otherwise print error
    if (availSpace < 0)
    {
        printf("ERROR: Appointment System Full\n");

    }
    else
    {
        searchResult = inputPatientNumberValidation(patients, &patientNumber, patientsMax);
        //if patient number has a match, allow user to input appointment
        if (searchResult > -1)
        {
            do
            {
                availAppoint = 1;

                inputAppointmentDate(&month, &year, &day);

                inputAppointTime(&hour, &min);


                //compare desired appointment date/time to existing appointments - add if not existing, otherwise give error
                for (i = 0; i < appointMax; i++)
                {
                    if (year == appointments[i].date.year && month == appointments[i].date.month && day == appointments[i].date.day && hour == appointments[i].time.hour && min == appointments[i].time.min)
                    {
                        availAppoint = 0;
                        printf("\nERROR: Appointment timeslot is not available!\n\n");
                        
                    }
                }
            } while (availAppoint == 0);


            if (availAppoint == 1 && availSpace > -1)
            {
                appointments[availSpace].patientNumber = patientNumber;
                appointments[availSpace].date.year = year;
                appointments[availSpace].date.month = month;
                appointments[availSpace].date.day = day;
                appointments[availSpace].time.hour = hour;
                appointments[availSpace].time.min = min;

                printf("\n*** Appointment scheduled! ***\n\n");
            }
        }
    }
}

// Remove an appointment record from the appointment array
// Todo:

void removeAppointment(struct Appointment appointments[], int appointMax, struct Patient patients[], int patientsMax)
{
    int i, patientNumber, year, month, day, appointMatch, searchResult;
    char removalOption[] = "yn";
    char removalSelection;

    appointMatch = 0;

    searchResult = inputPatientNumberValidation(patients, &patientNumber, patientsMax);
    //if patient number is valid, allow user to input appointment date/time for removal
    if (searchResult >-1)
    {
        
        inputAppointmentDate(&month, &year, &day);
        putchar('\n');
        //match given patient number and date to existing appointments
        for (i = 0; i < appointMax && appointMatch == 0; i++)
        {
            //if match is found, give option to remove appointment, else print error
            if (patientNumber == appointments[i].patientNumber && year == appointments[i].date.year && month == appointments[i].date.month && day == appointments[i].date.day)
            {
                appointMatch = 1;
                displayPatientData(&patients[searchResult], FMT_FORM);

                printf("Are you sure you want to remove this appointment (y,n): ");
                removalSelection = inputCharOption(removalOption);
                if (removalSelection == 'y')
                {
                    appointments[i].patientNumber = 0;
                    printf("\nAppointment record has been removed!\n\n");
                }
                else
                {
                    printf("Operation aborted\n\n");
                }
            }
        }

        if (appointMatch == 0)
        {
            printf("ERROR: Appointment not found\n");
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)

void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNum, patientIndex;

    printf("\nSearch by patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    patientIndex = findPatientIndexByPatientNum(patientNum, patient, max);

    if (patientIndex > -1)
    {
        displayPatientData(&patient[patientIndex], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
    suspend();
    searchPatientData(patient, max);

}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)

void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, recordMatch;
    char patientPhone[PHONE_LEN + 1];
    recordMatch = 0;

    printf("\nSearch by phone number: ");
    inputCString(patientPhone, 10, 10);
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(patientPhone, patient[i].phone.number) == 0)
        {
            recordMatch++;
            displayPatientData(&patient[i], FMT_TABLE);
        }
    }
    if (recordMatch == 0)
    {
        printf("\n*** No records found ***\n");

    }
    putchar('\n');
    suspend();
    searchPatientData(patient, max);

}

// Get the next highest patient number
// (Copy your code from MS#2)

int nextPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber;
    int i;

    patientNumber = 0;

    //find largest patient number
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > patientNumber)
        {
            patientNumber = patient[i].patientNumber;
        }
    }
    //add +1 to largest patient number for new nuumber
    patientNumber += 1;

    return patientNumber;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)

int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i, flag, searchResult;
    flag = 0;
    searchResult = -1;

    for (i = 0; i < max && flag == 0; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            //return the index number when there is a match
            searchResult = i;
            flag = 1;

        }
    }
    return searchResult;

}

//sort appointment dates in ascending order

void sortDates(struct ClinicData data, int size)
{
    int i, j;
    double dateTotal[50], tempTotal;
    struct Appointment tempAppoint;
    i = 0;
    j = 0;

    //add up year+month+day, the higher the number the later the appointment
    for (i = 0; i < size; i++)
    {
        ///divide by 10/100/10000 depending on importance: day -> hour -> min
        dateTotal[i] = data.appointments[i].date.year + (double)data.appointments[i].date.month / 12 + (double)data.appointments[i].date.day / 30 / 10 + (double)data.appointments[i].time.hour / 24 / 100 + (double)data.appointments[i].time.min / 60 / 10000;
    }

    //bubble sort dates in ascending order
    for (i = size - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (dateTotal[j] > dateTotal[j + 1])
            {
                tempAppoint = data.appointments[j];
                data.appointments[j] = data.appointments[j + 1];
                data.appointments[j + 1] = tempAppoint;

                tempTotal = dateTotal[j];
                dateTotal[j] = dateTotal[j + 1];
                dateTotal[j + 1] = tempTotal;
            }
        }
    }
}

//match patient number in patient and appointment arrays to display information properly
int matchPatientIndextoAppoinment(struct ClinicData data, int appointArray)
{
    int j,flag, result;
    flag = 0;
    j = 0;
    result = 0;


    for (j = 0; j < (data).maxPatient && flag ==0 ; j++)
    {
        if ((data).appointments[appointArray].patientNumber == (data).patients[j].patientNumber)
        {
            flag = 1;
            result = j;
        }
    }

    return result;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)

void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", (*patient).patientNumber);

    printf("Name  : ");
    inputCString((*patient).name, 1, NAME_LEN);

    putchar('\n');

    inputPhoneData(&patient->phone);

    printf("*** New patient record added ***\n\n");

}

// Get user input for phone contact information
// (Copy your code from MS#2)

void inputPhoneData(struct Phone* phone)
{
    int selection;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");

    selection = inputIntRange(0, 4);

    switch (selection)
    {
    case 1:
        strcpy((*phone).description, "CELL");
        printf("\nContact: %s\n", (*phone).description);
        printf("Number : ");
        inputCString((*phone).number, 10, 10);
        break;
    case 2:
        strcpy((*phone).description, "HOME");
        printf("\nContact: %s\n", (*phone).description);
        printf("Number : ");
        inputCString((*phone).number, 10, 10);
        break;
    case 3:
        strcpy((*phone).description, "WORK");
        printf("\nContact: %s\n", (*phone).description);
        printf("Number : ");
        inputCString((*phone).number, 10, 10);
        break;
    case 4:
        strcpy((*phone).description, "TBD");
        strcpy((*phone).number, "\0");
        break;
    }

    putchar('\n');
}

//determine day range, accounting for leap years

void inputAppointmentDate(int* month, int* year, int* day)
{
    int lastDay = 0;

    printf("Year        : ");
    *year = inputIntPositive();
    printf("Month (1-12): ");
    *month = inputIntRange(1, 12);
    //Determining how long the month will be
    switch (*month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        lastDay = 31;
        break;
    case 2:
        //check if leap year
        if (*year % 4 == 0)
        {
            lastDay = 29;
        }
        else
        {
            lastDay = 28;
        }
        break;
    default:
        lastDay = 30;
    }

    printf("Day (1-%d)  : ", lastDay);
    *day = inputIntRange(1, lastDay);
}

//determine hour and minutes for appointment, within opening to closing hours and in 30 minute intervals
void inputAppointTime(int *hour, int *mins)
{

    do
    {
        printf("Hour (0-23)  : ");
        *hour = inputInt();
        printf("Minute (0-59): ");
        *mins = inputInt();
        if (*hour<OPENING_HOUR || *hour>CLOSING_HOUR || *mins % MIN_INTERVALS != 0 || *hour+*mins > CLOSING_HOUR)
        {
            printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", OPENING_HOUR, CLOSING_HOUR, MIN_INTERVALS);
        }
    } while (*hour<OPENING_HOUR || *hour>CLOSING_HOUR || *mins % MIN_INTERVALS != 0 || *hour + *mins > CLOSING_HOUR);
}

//check to see if enetered patient number is valid if it is, send back the index number where match occured
int inputPatientNumberValidation(struct Patient patients[], int* patientNumber, int maxPatients)
{
    int searchResult;

    printf("Patient Number: ");
    *patientNumber = inputIntPositive();

    searchResult = findPatientIndexByPatientNum(*patientNumber, patients, maxPatients);

    if (searchResult == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }

    return searchResult;
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:

int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i, patientCount;
    i = 0;
    patientCount = 0;
    
    //local struct to store all patients in patientData.txt file as there are more patients than the number of arrays allocated
    struct Patient localPatients[30] = { {0} };

    FILE* patientData = NULL;
    patientData = fopen(datafile, "a+");

    //store data from patientData.txt to local struct
    if (patientData != NULL)
    {
        while (fscanf(patientData, "%d|%[^|]|%[^|]|%[^\n]\n", &localPatients[i].patientNumber, localPatients[i].name, localPatients[i].phone.description, localPatients[i].phone.number) != EOF)
        {
            i++;
        }
        fclose(patientData);
    }
    else
    {
        printf("FILE OPEN ERROR\n");
    }

    //Transfer local struct data to main struct up to 20 (MAX_PETS)

    for (i = 0; i < max; i++)
    {
        patients[i] = localPatients[i];
        if (patients[i].patientNumber>0)
        {
            patientCount++;
        }
    }

    return patientCount;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:

int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i, appointCount;
    i = 0;
    appointCount = 0;

    FILE* appointmentData = NULL;
    appointmentData = fopen(datafile, "a+");

    if (appointmentData != NULL)
    {

        while (fscanf(appointmentData, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min)!=EOF)
        {
            i++;
            appointCount++;
        }
     
    }
    return appointCount;
}