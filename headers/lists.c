#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

int GetInt(int min, int max)
{
    int choiceInt = -1;
    char choiceChar;
    printf("\n\t> ");
    scanf(" %d", &choiceInt);
    scanf("%c", &choiceChar);
    while (choiceInt > max || choiceInt < min)
    {
        printf("\n\t//Invalid Option//\n\n");
        printf("\n> ");
        scanf(" %d", &choiceInt);
        scanf("%c", &choiceChar);
    }
    system("cls");
    return choiceInt;
}

job *read(FILE *jobFile, job *jobHead)
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
        return 0;
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
                    machineTmp = create_new_machine(machineNumber);
                    machineHead = insert_machine_at_end(&machineHead, machineTmp);
                }
                operationTmp = create_new_operation(operationNumber, jobNumber, &machineHead);
                operationHead = insert_operation_at_end(&operationHead, operationTmp);
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

        jobTmp = create_new_job(jobNumber, &operationHead);
        jobHead = insert_job_at_end(&jobHead, jobTmp);
        operationHead = NULL;
    }
    fclose(jobFile);
    return jobHead;
}

void write(FILE *jobFile, job *jobHead)
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
        {
            fprintf(jobFile, "\n");
        }
        jobTmp = jobTmp->next;
    }
    fclose(jobFile);
}

void PrintJobList(job *jobHead)
{
    job *jobTmp = jobHead;
    printf("Jobs:\n");
    while (jobTmp != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobTmp = jobTmp->next;
    }
    PrintOperationList(select_job(jobHead)->operationHeadPointer);
}

void PrintOperationList(operation *operationHead)
{
    operation *operationTmp = operationHead;

    while (operationTmp != NULL)
    {
        printf("\nOperation: %d\n\n", operationTmp->operationNumber);
        PrintMachineList(operationTmp->machineHeadPointer);
        operationTmp = operationTmp->next;
    }
}

void PrintMachineList(machine *machineHead)
{
    machine *machineTmp = machineHead;

    while (machineTmp != NULL)
    {
        printf("Machine: %d Time: %d\n", machineTmp->machineNumber, machineTmp->machineTime);
        machineTmp = machineTmp->next;
    }
}

void UserCreateOperation(job *jobHead)
{
    job *jobTmp = jobHead;
    operation *operationTmp;
    operation *operationHead;
    machine *machineTmp;
    machine *machineHeadTmp;
    machine *machineHead = NULL;
    int machineNumber = 1;
    int operationNumber;
    printf("Jobs:\n");
    while (jobTmp != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobTmp = jobTmp->next;
    }
    jobTmp = select_job(jobHead);

    printf("\nOperation Order Number: ");
    scanf(" %d", &operationNumber);

    while (machineNumber != 0)
    {
        printf("\nMachine Number: ");
        scanf(" %d", &machineNumber);
        machineTmp = create_new_machine(machineNumber);
        machineHead = insert_machine_at_end(&machineHead, machineTmp);

        printf("\nMachine %d Time: ", machineTmp->machineNumber);
        scanf(" %d", &machineNumber);
        machineTmp->machineTime = machineNumber;
        machineTmp = machineHead;

        printf("Enter 0 to stop adding machines: ");
        scanf(" %d", &machineNumber);
    }
    while (jobTmp->operationHeadPointer->next != NULL)
    {
        jobTmp->operationHeadPointer = jobTmp->operationHeadPointer->next;
    }
    operationTmp = create_new_operation(jobTmp->operationHeadPointer->operationNumber + 1, jobTmp->jobNumber, &machineHead);
    while (jobTmp->operationHeadPointer->prev != NULL)
    {
        jobTmp->operationHeadPointer = jobTmp->operationHeadPointer->prev;
    }
    operationHead = insert_operation_at_end(&jobTmp->operationHeadPointer, operationTmp);
    operationTmp = find_operation(jobTmp->operationHeadPointer, operationNumber, jobTmp->jobNumber);
    while (operationTmp != NULL)
    {
        machineHeadTmp = operationTmp->machineHeadPointer;
        operationTmp->machineHeadPointer = machineTmp;
        machineTmp = machineHeadTmp;
        operationTmp = operationTmp->next;
    }
}

void UserRemoveOperation(job *jobHead)
{
    job *jobTmp = jobHead;
    operation *operationTmp;
    machine *machineTmp;
    machine *machineHeadTmp;
    machine *machineHead = NULL;
    int machineNumber = 1;
    int operationNumber;
    printf("Jobs:\n");
    while (jobTmp != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobTmp = jobTmp->next;
    }
    jobTmp = select_job(jobHead);
    operationTmp = jobTmp->operationHeadPointer;

    printf("\nOperation Number: ");
    scanf(" %d", &operationNumber);

    // while (jobTmp->operationHeadPointer->prev != NULL)
    // {
    //     jobTmp->operationHeadPointer = jobTmp->operationHeadPointer->prev;
    // }
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

void UserAlterOperation(job *jobHead)
{
    job *jobTmp = jobHead;
    operation *operationTmp;
    operation *operationTmp2;
    operation *operationTmp3;
    machine *machineTmp;
    machine *machineHeadTmp;
    machine *machineHead = NULL;
    int machineNumber = 1;
    int operationNumber;

    printf("Jobs:\n");
    while (jobTmp != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobTmp = jobTmp->next;
    }
    jobTmp = select_job(jobHead);

    operationTmp = select_operation(jobTmp->operationHeadPointer);
    int choice;

    do
    {
        printf("\t--- Alter Operation ---\n"
               "\t Enter 1 - Add Machine \n"
               "\t Enter 2 - Remove Machine \n"
               "\t Enter 3 - Swap Operation Order \n"
               "\n\t Enter 0 - Quit\n");

        choice = GetInt(0, 5);
        switch (choice)
        {
        case 1:
            while (machineNumber != 0)
            {
                machineHead = operationTmp->machineHeadPointer;
                printf("\nMachine Number: ");
                scanf(" %d", &machineNumber);
                machineTmp = create_new_machine(machineNumber);
                machineHead = insert_machine_at_end(&machineHead, machineTmp);

                printf("\nMachine %d Time: ", machineTmp->machineNumber);
                scanf(" %d", &machineNumber);
                machineTmp->machineTime = machineNumber;
                machineTmp = machineHead;

                printf("Enter 0 to stop adding machines: ");
                scanf(" %d", &machineNumber);
            }
            break;
        case 2:
            machineTmp = select_machine(jobTmp->operationHeadPointer->machineHeadPointer);
            remove_machine(jobTmp->operationHeadPointer->machineHeadPointer, machineTmp->machineNumber);
            break;
        case 3:
            printf("\n Swap operation %d with: ", operationTmp->operationNumber);
            scanf("%d", &operationNumber);
            operationTmp2 = find_operation(jobTmp->operationHeadPointer, operationNumber, jobTmp->jobNumber);
            operationTmp3->next = operationTmp->next;
            operationTmp3->prev = operationTmp->prev;
            operationTmp->next = operationTmp2->next;
            operationTmp->prev = operationTmp2->prev;
            operationTmp2->next = operationTmp3->next;
            operationTmp2->prev = operationTmp3->prev;
            break;
        case 0:
            break;
        default:
            printf("\n\t//Invalid Option//\n\n");
            break;
        }
    } while (choice != 0);
}

job *create_new_job(int jobNumber, operation **operationHead)
{
    job *result = malloc(sizeof(job));
    result->jobNumber = jobNumber;
    result->operationHeadPointer = *operationHead;
    result->next = NULL;
    return result;
}

operation *create_new_operation(int operationNumber, int jobNumber, machine **machineHead)
{
    operation *result = malloc(sizeof(operation));
    result->operationNumber = operationNumber;
    result->jobNumber = jobNumber;
    result->machineHeadPointer = *machineHead;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

machine *create_new_machine(int machineNumber)
{
    machine *result = malloc(sizeof(machine));
    result->machineNumber = machineNumber;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

job *insert_at_jobhead(job **jobHead, job *jobToInsert)
{
    jobToInsert->next = *jobHead;
    *jobHead = jobToInsert;
    return jobToInsert;
}

operation *insert_at_operationhead(operation **operationHead, operation *operationToInsert)
{
    operationToInsert->next = *operationHead;
    *operationHead = operationToInsert;
    return operationToInsert;
}

machine *insert_at_machineHead(machine **machineHead, machine *machineToInsert)
{
    machineToInsert->next = *machineHead;
    *machineHead = machineToInsert;
    return machineToInsert;
}

void insert_after_job(job *jobToInsertAfter, job *jobToInsert)
{
    jobToInsert->next = jobToInsertAfter->next;
    jobToInsertAfter->next = jobToInsert;
}

void insert_after_operation(operation *operationToInsertAfter, operation *operationToInsert)
{
    operationToInsert->next = operationToInsertAfter->next;
    operationToInsertAfter->next = operationToInsert;
}

void insert_after_machine(machine *machineToInsertAfter, machine *machineToInsert)
{
    machineToInsert->next = machineToInsertAfter->next;
    machineToInsertAfter->next = machineToInsert;
}

job *insert_job_at_end(job **jobHead, job *jobToInsert)
{
    jobToInsert->next = NULL;

    if (*jobHead == NULL)
        *jobHead = jobToInsert;
    else
    {
        job *last = *jobHead;

        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = jobToInsert;
    }
    return *jobHead;
}

operation *insert_operation_at_end(operation **operationHead, operation *operationToInsert)
{
    operationToInsert->next = NULL;

    if (*operationHead == NULL)
        *operationHead = operationToInsert;
    else
    {
        operation *last = *operationHead;

        while (last->next != NULL)
        {
            last->next->prev = last;
            last = last->next;
        }

        last->next = operationToInsert;
        operationToInsert->prev = last;
    }
    return *operationHead;
}

machine *insert_machine_at_end(machine **machineHead, machine *machineToInsert)
{
    machineToInsert->next = NULL;

    if (*machineHead == NULL)
        *machineHead = machineToInsert;
    else
    {
        machine *last = *machineHead;

        while (last->next != NULL)
        {
            last->next->prev = last;
            last = last->next;
        }
        last->next = machineToInsert;
        machineToInsert->prev = last;
    }
    return *machineHead;
}

job *select_job(job *jobHead)
{
    job *jobHead2 = jobHead;
    int jobNumber;

    printf("\nSelect Job: ");
    while (jobHead->next != NULL)
    {
        jobHead = jobHead->next;
    }
    jobNumber = GetInt(1, jobHead->jobNumber);
    jobHead = jobHead2;
    while (jobHead != NULL)
    {
        if (jobHead->jobNumber == jobNumber)
            return jobHead;
        jobHead = jobHead->next;
    }
    return NULL;
}

operation *find_operation(operation *operationHead, int operationNumber, int jobNumber)
{
    operation *operationTmp = operationHead;
    while (operationTmp != NULL)
    {
        if (operationTmp->operationNumber == operationNumber && operationTmp->jobNumber == jobNumber)
        {
            return operationTmp;
        }
        operationTmp = operationTmp->next;
    }
    return NULL;
}

operation *select_operation(operation *operationHead)
{
    operation *operationHead2 = operationHead;
    int operationNumber;

    printf("\nSelect operation: ");
    while (operationHead->next != NULL)
    {
        operationHead = operationHead->next;
    }
    operationNumber = GetInt(1, operationHead->operationNumber);
    operationHead = operationHead2;
    while (operationHead != NULL)
    {
        if (operationHead->operationNumber == operationNumber)
            return operationHead;
        operationHead = operationHead->next;
    }
    return NULL;
}

machine *select_machine(machine *machineHead)
{
    machine *machineHead2 = machineHead;
    int machineNumber;

    printf("\nSelect machine: ");
    while (machineHead->next != NULL)
    {
        machineHead = machineHead->next;
    }
    machineNumber = GetInt(1, 999);
    machineHead = machineHead2;
    while (machineHead != NULL)
    {
        if (machineHead->machineNumber == machineNumber)
            return machineHead;
        machineHead = machineHead->next;
    }
    return NULL;
}

operation *alter_operation(operation *operationToAlter)
{
    printf("Old Job Number: %d\tNew Job Number: ", operationToAlter->operationNumber);
    scanf(" %d", &operationToAlter->operationNumber);
}

void *remove_job(job **jobHead, job *jobToRemove)
{
    job *jobTmp;

    if ((*jobHead)->jobNumber == jobToRemove->jobNumber)
    {
        jobTmp = *jobHead;
        *jobHead = (*jobHead)->next;
        free(jobTmp);
    }
    else
    {
        job *current = *jobHead;
        while (current->next != NULL)
        {
            if (current->next->jobNumber == jobToRemove->jobNumber)
            {
                jobTmp = current->next;
                current->next = current->next->next;
                free(jobTmp);
                break;
            }
            else
            {
                current = current->next;
            }
        }
    }
}

void *remove_operation(operation **operationHead, int operationNumber)
{
    operation *operationTmp;

    if ((*operationHead)->operationNumber == operationNumber)
    {
        operationTmp = *operationHead;
        *operationHead = (*operationHead)->next;
        free(operationTmp);
    }
    else
    {
        operation *current = *operationHead;
        while (current->next != NULL)
        {
            if (current->next->operationNumber == operationNumber)
            {
                operationTmp = current->next;
                current->next = current->next->next;
                free(operationTmp);
                break;
            }
            else
            {
                current = current->next;
            }
        }
    }
}

void *remove_machine(machine **machineHead, int machineNumber)
{
    machine *machineTmp;

    if ((*machineHead)->machineNumber == machineNumber)
    {
        machineTmp = *machineHead;
        *machineHead = (*machineHead)->next;
        free(machineTmp);
    }
    else
    {
        machine *current = *machineHead;
        while (current->next != NULL)
        {
            if (current->next->machineNumber == machineNumber)
            {
                machineTmp = current->next;
                current->next = current->next->next;
                free(machineTmp);
                break;
            }
            else
            {
                current = current->next;
            }
        }
    }
}
