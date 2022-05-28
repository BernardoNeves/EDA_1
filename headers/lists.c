
#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

int getInt(int min, int max) // TODO Optimize and move to another file
{
    int choiceInt = min - 1;
    char choiceChar;
    // printf("\n");
    while (choiceInt > max || choiceInt < min)
    {
        // printf("\t> ");
        scanf(" %d", &choiceInt);
        scanf("%c", &choiceChar);
    }
    // system("cls");
    return choiceInt;
}

job *read(FILE *jobFile, job *jobHead) // TODO OPTIMIZE AF WTF
{
    job *jobTmp;
    machine *machineHead = NULL;
    machine *machineTmp;
    operation *operationHead = NULL;
    operation *operationTmp;
    int jobNumber = 0, machineNumber, operationNumber = 0;
    char buffer = '>';

    jobFile = fopen("Jobs.txt", "r");
    if (jobFile == NULL)
    {
        printf("Failed to open Jobs.txt");
        return NULL;
    }
    fscanf(jobFile, "%*c");
    while (!feof(jobFile))
    {
        jobNumber++;
        if (buffer == '>')
        {
            while (buffer == '>')
            {
                operationNumber++;
                while (fscanf(jobFile, " %d", &machineNumber) == 1)
                {
                    machineTmp = createNewMachine(machineNumber);
                    machineHead = insertAtMachineEnd(&machineHead, machineTmp);
                }
                operationTmp = createNewOperation(operationNumber, jobNumber, &machineHead);
                operationHead = insertAtOperationEnd(&operationHead, operationTmp);
                fscanf(jobFile, "%*c %c", &buffer);
                machineTmp = machineHead;
                while (fscanf(jobFile, " %d", &machineNumber) == 1)
                {
                    machineTmp->machineTime = machineNumber;
                    machineTmp = machineTmp->next;
                }
                fscanf(jobFile, "%*c %c", &buffer);
                machineHead = NULL;
            }
        }
        fscanf(jobFile, "%*c %c", &buffer);
        operationNumber = 0;

        jobTmp = createNewJob(jobNumber, &operationHead);
        jobHead = insertAtJobEnd(&jobHead, jobTmp);
        operationHead = NULL;
    }
    fclose(jobFile);
    return jobHead;
}

void write(FILE *jobFile, job *jobHead) // TODO OPTIMIZE AF WTF
{
    job *jobTmp = jobHead;
    machine *machineTmp;
    jobFile = fopen("Jobs.txt", "w");
    while (jobTmp != NULL)
    {
        while (jobTmp->operationHeadPointer != NULL)
        {
            fprintf(jobFile, ">");
            while (jobTmp->operationHeadPointer->machineHeadPointer != NULL)
            {
                fprintf(jobFile, "%d", jobTmp->operationHeadPointer->machineHeadPointer->machineNumber);
                if (jobTmp->operationHeadPointer->machineHeadPointer->next != NULL)
                {
                    fprintf(jobFile, " ");
                }
                machineTmp = jobTmp->operationHeadPointer->machineHeadPointer;
                jobTmp->operationHeadPointer->machineHeadPointer = jobTmp->operationHeadPointer->machineHeadPointer->next;
            }
            fprintf(jobFile, ",\n");
            while (machineTmp->prev != NULL)
            {
                machineTmp = machineTmp->prev;
            }
            fprintf(jobFile, ">");
            while (machineTmp != NULL)
            {
                fprintf(jobFile, "%d", machineTmp->machineTime);
                if (machineTmp->next != NULL)
                {
                    fprintf(jobFile, " ");
                }
                machineTmp = machineTmp->next;
            }
            fprintf(jobFile, ",\n");
            jobTmp->operationHeadPointer = jobTmp->operationHeadPointer->next;
        }
        fprintf(jobFile, "-,");
        if (jobTmp->next != NULL)
            fprintf(jobFile, "\n");
        jobTmp = jobTmp->next;
    }
    fclose(jobFile);
}
// TODO OPTIMIZE FROM HERE TO THE TOP

int timeMin(job *jobHead) //? remove prints
{
    int totalTime = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
    {
        machine *minTimeMachine = operationTmp->machineHeadPointer;
        for (machine *machineTmp = operationTmp->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
            if (minTimeMachine->machineTime > machineTmp->machineTime)
                minTimeMachine = machineTmp;
        totalTime += minTimeMachine->machineTime;
        printf("Minimum Time for Operation %d: Machine: %d Time: %d\n", operationTmp->operationNumber, minTimeMachine->machineNumber, minTimeMachine->machineTime);
    }
    printf("\nMinimum Time for Job %d: %d\n", jobHead->jobNumber, totalTime);
    return totalTime;
}

int timeMax(job *jobHead) //? remove prints
{
    int totalTime = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
    {
        machine *maxTimeMachine = operationTmp->machineHeadPointer;
        for (machine *machineTmp = operationTmp->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
            if (maxTimeMachine->machineTime < machineTmp->machineTime)
                maxTimeMachine = machineTmp;
        totalTime += maxTimeMachine->machineTime;
        printf("Maximum Time for Operation %d: Machine: %d Time: %d\n", operationTmp->operationNumber, maxTimeMachine->machineNumber, maxTimeMachine->machineTime);
    }
    printf("\nMaximum Time for Job %d: %d\n", jobHead->jobNumber, totalTime);
    return totalTime;
}

float timeAverage(job *jobHead) // TODO OPTIMIZE ??? MORE ???
{
    int machineCounter, operationCounter = 0;
    float totalTime = 0, operationTime;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
    {
        machineCounter = 0, operationTime = 0, operationCounter++;
        for (machine *machineTmp = operationTmp->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        {
            operationTime += machineTmp->machineTime;
            machineCounter++;
        }
        printf("Average Time for Operation %d: %.2f\n", operationTmp->operationNumber, operationTime / machineCounter);
        totalTime += operationTime / machineCounter;
    }
    printf("\nAverage Time for Job %d: %.2f\n", jobHead->jobNumber, totalTime / operationCounter);
    return totalTime / operationCounter;
}

void printJobList(job *jobHead)
{
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
    {
        printf("\n\nJob: %d\n\n", jobTmp->jobNumber);
        printOperationList(jobTmp->operationHeadPointer);
    }
}

void printOperationList(operation *operationHead)
{
    for (operation *operationTmp = operationHead; operationTmp != NULL; operationTmp = operationTmp->next)
    {
        printf("\nOperation: %d\n\n", operationTmp->operationNumber);
        printMachineList(operationTmp->machineHeadPointer);
    }
}

void printMachineList(machine *machineHead)
{
    for (machine *machineTmp = machineHead; machineTmp != NULL; machineTmp = machineTmp->next)
        printf("Machine: %d Time: %d\n", machineTmp->machineNumber, machineTmp->machineTime);
}

/*//TODO MOVE THIS TO A NEW FILE AND SEPARATE PRINTS FROM CALCULATIONS AND FUNCTIONS
void userCreateOperation(job *jobHead) // TODO Optimize
{
    job *jobTmp = jobHead;
    operation *operationTmp;
    operation *operationHead;
    machine *machineTmp;
    machine *machineHeadTmp;
    machine *machineHead = NULL;
    int machineNumber = 1;
    int operationNumber;
    int jobNumber;

    // select job and operation order
    printf("Jobs:\n");
    while (jobTmp->next != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobNumber = jobTmp->jobNumber;
        jobTmp = jobTmp->next;
    }
    printf("\nSelect Job: ");
    jobTmp = findJob(jobHead, getInt(1, jobNumber));

    printf("\nOperation Order Number: ");
    scanf(" %d", &operationNumber);

    //  create machines
    while (machineNumber != 0)
    {
        printf("\nMachine Number: ");
        scanf(" %d", &machineNumber);
        machineTmp = createNewMachine(machineNumber);
        machineHead = insertAtMachineEnd(&machineHead, machineTmp);

        printf("\nMachine %d Time: ", machineTmp->machineNumber);
        scanf(" %d", &machineNumber);
        machineTmp->machineTime = machineNumber;
        machineTmp = machineHead;

        printf("Enter 0 to stop adding machines: ");
        scanf(" %d", &machineNumber);
    }

    // Create Operation
    operationTmp = createNewOperation(operationNumber, jobTmp->jobNumber, &machineHead);
    while (jobTmp->operationHeadPointer->prev != NULL)
    {
        jobTmp->operationHeadPointer = jobTmp->operationHeadPointer->prev;
    }
    insertAfterOperation(findOperation(jobTmp->operationHeadPointer, operationNumber - 1), operationTmp);
    orderJob(jobHead);
}

void userRemoveOperation(job *jobHead) // TODO Optimize
{
    job *jobTmp = jobHead;
    operation *operationTmp;
    machine *machineTmp;
    machine *machineHeadTmp;
    machine *machineHead = NULL;
    int machineNumber = 1;
    int operationNumber;
    int jobNumber;

    printf("Jobs:\n");
    while (jobTmp->next != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobNumber = jobTmp->jobNumber;
        jobTmp = jobTmp->next;
    }
    printf("\nSelect Job: ");
    jobTmp = findJob(jobHead, getInt(1, jobNumber));
    operationTmp = jobTmp->operationHeadPointer;

    printf("\nOperation Number: ");
    scanf(" %d", &operationNumber);

    while (operationTmp->next != NULL)
    {
        operationTmp = operationTmp->next;
    }
    while (operationTmp->prev != NULL)
    {
        machineHeadTmp = operationTmp->machineHeadPointer;
        operationTmp->machineHeadPointer = machineTmp;
        machineTmp = machineHeadTmp;
        operationTmp = operationTmp->prev;
        if (operationTmp->next->operationNumber == operationNumber)
            break;
    }

    while (operationTmp->next != NULL)
    {
        operationTmp = operationTmp->next;
    }
    operationTmp->prev->next = NULL;
    free(operationTmp);
}

void userAlterOperation(job *jobHead) // TODO Optimize
{
    job *jobTmp = jobHead;
    operation *operationTmp, *operationTmp2;
    machine *machineTmp, *machineHeadTmp, *machineHead = NULL;
    int machineNumber = 1, operationNumber, jobNumber, choice;

    printf("Jobs:\n");
    while (jobTmp->next != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobNumber = jobTmp->jobNumber;
        jobTmp = jobTmp->next;
    }
    printf("\nSelect Job: ");
    jobTmp = findJob(jobHead, getInt(1, jobNumber));

    printf("\nOperation Number: ");
    scanf(" %d", &operationNumber);

    operationTmp = findOperation(jobTmp->operationHeadPointer, operationNumber);

    printf("\t--- Alter Operation ---\n"
           "\t Enter 1 - Add Machine \n"
           "\t Enter 2 - Remove Machine \n"
           "\t Enter 3 - Swap Operation Order \n"
           "\n\t Enter 0 - back\n");

    choice = getInt(0, 5);
    switch (choice)
    {
    case 1:
        while (machineNumber != 0)
        {
            machineHead = operationTmp->machineHeadPointer;
            printf("\nMachine Number: ");
            scanf(" %d", &machineNumber);
            machineTmp = createNewMachine(machineNumber);
            machineHead = insertAtMachineEnd(&machineHead, machineTmp);

            printf("\nMachine %d Time: ", machineTmp->machineNumber);
            scanf(" %d", &machineNumber);
            machineTmp->machineTime = machineNumber;
            machineTmp = machineHead;

            printf("Enter 0 to stop adding machines: ");
            scanf(" %d", &machineNumber);
        }
        break;
    case 2:
        printf("\nMachine Number: ");
        scanf(" %d", &machineNumber);
        machineTmp = findMachine(jobTmp->operationHeadPointer->machineHeadPointer, machineNumber);
        removeMachine(&operationTmp->machineHeadPointer, machineTmp->machineNumber);
        break;
    case 3:
        printf("\n Swap operation %d with: ", operationTmp->operationNumber);
        scanf("%d", &operationNumber);
        operationTmp2 = findOperation(jobTmp->operationHeadPointer, operationNumber);
        machineTmp = operationTmp->machineHeadPointer;
        operationTmp->machineHeadPointer = operationTmp2->machineHeadPointer;
        operationTmp2->machineHeadPointer = machineTmp;
        break;
    case 0:
        break;
    default:
        printf("\n\t//Invalid Option//\n\n");
        break;
    }
}
*/

job *createNewJob(int jobNumber, operation **operationHead)
{
    job *result = malloc(sizeof(job));
    result->jobNumber = jobNumber;
    result->operationHeadPointer = *operationHead;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

operation *createNewOperation(int operationNumber, int jobNumber, machine **machineHead)
{
    operation *result = malloc(sizeof(operation));
    result->operationNumber = operationNumber;
    result->jobNumber = jobNumber;
    result->machineHeadPointer = *machineHead;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

machine *createNewMachine(int machineNumber)
{
    machine *result = malloc(sizeof(machine));
    result->machineNumber = machineNumber;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

job insertAfterJob(struct job *jobToInsertAfter, struct job *jobToInsert)
{
    jobToInsert->next = jobToInsertAfter->next;
    jobToInsert->next->prev = jobToInsert;
    jobToInsertAfter->next = jobToInsert;
    jobToInsert->prev = jobToInsertAfter;
    return *jobToInsert;
}

operation insertAfterOperation(struct operation *operationToInsertAfter, struct operation *operationToInsert)
{
    operationToInsert->next = operationToInsertAfter->next;
    operationToInsert->next->prev = operationToInsert;
    operationToInsertAfter->next = operationToInsert;
    operationToInsert->prev = operationToInsertAfter;
    return *operationToInsert;
}

machine insertAfterMachine(struct machine *machineToInsertAfter, struct machine *machineToInsert)
{
    machineToInsert->next = machineToInsertAfter->next;
    machineToInsert->next->prev = machineToInsert;
    machineToInsertAfter->next = machineToInsert;
    machineToInsert->prev = machineToInsertAfter;
    return *machineToInsert;
}

job *insertAtJobHead(job **jobHead, job *jobToInsert)
{
    jobToInsert->next = *jobHead;
    *jobHead = jobToInsert;
    return jobToInsert;
}

operation *insertAtOperationHead(operation **operationHead, operation *operationToInsert)
{

    operationToInsert->next = *operationHead;
    *operationHead = operationToInsert;
    return operationToInsert;
}

machine *insertAtMachineHead(machine **machineHead, machine *machineToInsert)
{
    machineToInsert->next = *machineHead;
    *machineHead = machineToInsert;
    return machineToInsert;
}

job *insertAtJobEnd(job **jobHead, job *jobToInsert) //? CAN I OPTIMIZE THIS
{
    jobToInsert->next = NULL;

    if (*jobHead == NULL)
        *jobHead = jobToInsert;
    else
    {
        job *last = *jobHead;
        while (last->next != NULL)
            last = last->next;
        last->next = jobToInsert;
        jobToInsert->prev = last;
    }
    return *jobHead;
}

operation *insertAtOperationEnd(operation **operationHead, operation *operationToInsert) //? CAN I OPTIMIZE THIS
{
    operationToInsert->next = NULL;

    if (*operationHead == NULL)
        *operationHead = operationToInsert;
    else
    {
        operation *last = *operationHead;
        while (last->next != NULL)
            last = last->next;
        last->next = operationToInsert;
        operationToInsert->prev = last;
    }
    return *operationHead;
}

machine *insertAtMachineEnd(machine **machineHead, machine *machineToInsert) //? CAN I OPTIMIZE THIS
{
    machineToInsert->next = NULL;

    if (*machineHead == NULL)
        *machineHead = machineToInsert;
    else
    {
        machine *last = *machineHead;
        while (last->next != NULL)
            last = last->next;
        last->next = machineToInsert;
        machineToInsert->prev = last;
    }
    return *machineHead;
}

void orderJob(job *jobHead)
{
    int jobNumber = 1;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
    {
        orderOperation(jobTmp->operationHeadPointer);
        jobTmp->jobNumber = jobNumber++;
    }
}

void orderOperation(operation *operationHead)
{
    int operationNumber = 1;
    for (operation *operationTmp = operationHead; operationTmp != NULL; operationTmp = operationTmp->next)
        operationTmp->operationNumber = operationNumber++;
}

job *findJob(job *jobHead, int jobNumber)
{
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        if (jobTmp->jobNumber == jobNumber)
            return jobTmp;
    return NULL;
}

operation *findOperation(operation *operationHead, int operationNumber)
{
    for (operation *operationTmp = operationHead; operationTmp != NULL; operationTmp = operationTmp->next)
        if (operationTmp->operationNumber == operationNumber)
            return operationTmp;
    return NULL;
}

machine *findMachine(machine *machineHead, int machineNumber)
{
    for (machine *machineTmp = machineHead; machineTmp != NULL; machineTmp = machineTmp->next)
        if (machineTmp->machineNumber == machineNumber)
            return machineTmp;
    return NULL;
}

void *removeJob(job **jobHead, int jobNumber)
{
    for (job *jobTmp = *jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        if (jobTmp->jobNumber == jobNumber)
        {
            while (jobTmp->operationHeadPointer != NULL)
                removeOperation(&(jobTmp->operationHeadPointer), jobTmp->operationHeadPointer->operationNumber);
            if (jobTmp == *jobHead)
                *jobHead = (*jobHead)->next;
            else
                jobTmp->prev->next = jobTmp->next;
            free(jobTmp);
            break;
        }
    orderJob(*jobHead);
}

void *removeOperation(operation **operationHead, int operationNumber)
{
    for (operation *operationTmp = *operationHead; operationTmp != NULL; operationTmp = operationTmp->next)
        if (operationTmp->operationNumber == operationNumber)
        {
            while (operationTmp->machineHeadPointer != NULL)
                removeMachine(&(operationTmp->machineHeadPointer), operationTmp->machineHeadPointer->machineNumber);
            if (operationTmp == *operationHead)
                *operationHead = (*operationHead)->next;
            else
                operationTmp->prev->next = operationTmp->next;
            free(operationTmp);
            break;
        }
    orderOperation(*operationHead);
}

void *removeMachine(machine **machineHead, int machineNumber)
{
    for (machine *machineTmp = *machineHead; machineTmp != NULL; machineTmp = machineTmp->next)
        if (machineTmp->machineNumber == machineNumber)
        {
            if (machineTmp == *machineHead)
                *machineHead = (*machineHead)->next;
            else
                machineTmp->prev->next = machineTmp->next;
            free(machineTmp);
            break;
        }
}
