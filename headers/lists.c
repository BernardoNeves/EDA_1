#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "lists.h"

job *read(FILE *JobsFile, job *jobhead)
{
    machine *head = NULL;
    machine *tmp;
    operation *operationhead = NULL;
    operation *operationtmp;
    job *jobtmp;
    int i, j = 0, k = 0, l, m;
    char a = '>';

    JobsFile = fopen("Jobs.txt", "r");
    if (JobsFile == NULL)
    {
        printf("Failed to open Jobs.txt");
        return 0;
    }
    fscanf(JobsFile, "%*c");
    while (!feof(JobsFile))
    {
        k++;
        if (a == '>')
        {
            while (a == '>')
            {
                j++;
                while (fscanf(JobsFile, " %d", &i) == 1)
                {
                    tmp = create_new_machine(i);
                    head = insert_machine_at_end(&head, tmp);
                }
                operationtmp = create_new_operation(j, k, &head);
                operationhead = insert_operation_at_end(&operationhead, operationtmp);
                fscanf(JobsFile, "%*c %c", &a);
                tmp = head;
                while (fscanf(JobsFile, " %d", &i) == 1)
                {
                    tmp->MachineTime = i;
                    tmp = tmp->next;
                }
                fscanf(JobsFile, "%*c %c", &a);
                head = NULL;
            }
        }
        fscanf(JobsFile, "%*c %*c %c", &a);
        j = 0;

        jobtmp = create_new_job(k, &operationhead);
        jobhead = insert_job_at_end(&jobhead, jobtmp);
        operationhead = NULL;
    }
    fclose(JobsFile);
    return jobhead;
}

void write(FILE *JobsFile, job *jobhead)
{
    job *tmp = jobhead;
    machine *machinetmp;
    JobsFile = fopen("Jobs.txt", "w");
    while (tmp != NULL)
    {
        while (tmp->OperationHeadPointer != NULL)
        {
            fprintf(JobsFile, ">");
            while (tmp->OperationHeadPointer->MachineHeadPointer != NULL)
            {
                fprintf(JobsFile, "%d", tmp->OperationHeadPointer->MachineHeadPointer->MachineNumber);
                if (tmp->OperationHeadPointer->MachineHeadPointer->next != NULL)
                {
                    fprintf(JobsFile, " ");
                }
                machinetmp = tmp->OperationHeadPointer->MachineHeadPointer;
                tmp->OperationHeadPointer->MachineHeadPointer = tmp->OperationHeadPointer->MachineHeadPointer->next;
            }
            fprintf(JobsFile, ",\n");
            while (machinetmp->prev != NULL)
            {
                machinetmp = machinetmp->prev;
            }
            fprintf(JobsFile, ">");
            while (machinetmp != NULL)
            {
                fprintf(JobsFile, "%d", machinetmp->MachineTime);
                if (machinetmp->next != NULL)
                {
                    fprintf(JobsFile, " ");
                }
                machinetmp = machinetmp->next;
            }
            fprintf(JobsFile, ",\n");
            tmp->OperationHeadPointer = tmp->OperationHeadPointer->next;
        }
        fprintf(JobsFile, "-%d,", tmp->JobNumber);
        if (tmp->next != NULL)
        {
            fprintf(JobsFile, "\n");
        }
        tmp = tmp->next;
    }
    fclose(JobsFile);
}

//

void PrintJobList(job *jobhead)
{
    job *tmp = jobhead;
    job *jobtmp;
    printf("Jobs:\n");
    while (tmp != NULL)
    {
        printf(">%d ", tmp->JobNumber);
        jobtmp = tmp;
        tmp = tmp->next;
    }

    jobtmp = find_job(jobhead, 0);
    PrintOperationList(jobtmp->OperationHeadPointer, jobhead, jobtmp->JobNumber);
}

void PrintOperationList(operation *head, job *jobhead, int JobNumber)
{
    operation *tmp = head;
    operation *operationtmp;
    job *jobtmp;

    printf("\n\t\tJob: %d\n\n", JobNumber);
    while (tmp != NULL)
    {
        jobtmp = find_job(jobhead, JobNumber);
        operationtmp = find_operation(jobtmp->OperationHeadPointer, tmp->OperationNumber, JobNumber);
        printf("Operation: %d\n\n", tmp->OperationNumber);
        PrintMachineList(operationtmp->MachineHeadPointer);
        tmp = tmp->next;
    }
}

void PrintMachineList(machine *head)
{
    machine *tmp = head;
    machine *tmp2 = head;
    while (tmp != NULL)
    {
        printf("ID: %d TIME: %d\n", tmp->MachineNumber, tmp->MachineTime);
        tmp2 = tmp;
        tmp = tmp->next;
    }

    // printf("\nReversed\n");
    // while (tmp2 != NULL)
    // {
    //     printf("ID: %d TIME: %d\n", tmp2->MachineNumber, tmp2->MachineTime);
    //     tmp2 = tmp2->prev;
    // }
    printf("\n");
}

//

job *create_new_job(int JobNumber, operation **head)
{
    job *result = malloc(sizeof(job));
    result->JobNumber = JobNumber;
    result->OperationHeadPointer = *head;
    result->next = NULL;
    return result;
}

operation *create_new_operation(int OperationNumber, int JobNumber, machine **head)
{
    operation *result = malloc(sizeof(operation));
    result->OperationNumber = OperationNumber;
    result->JobNumber = JobNumber;
    result->MachineHeadPointer = *head;
    result->next = NULL;
    return result;
}

machine *create_new_machine(int MachineNumber)
{
    machine *result = malloc(sizeof(machine));
    result->MachineNumber = MachineNumber;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

//

job *insert_at_jobhead(job **jobhead, job *job_to_insert)
{
    job_to_insert->next = *jobhead;
    *jobhead = job_to_insert;
    return job_to_insert;
}

operation *insert_at_operationhead(operation **operationhead, operation *operation_to_insert)
{
    operation_to_insert->next = *operationhead;
    *operationhead = operation_to_insert;
    return operation_to_insert;
}

machine *insert_at_machinehead(machine **machinehead, machine *machine_to_insert)
{
    machine_to_insert->next = *machinehead;
    *machinehead = machine_to_insert;
    return machine_to_insert;
}

//

void insert_after_job(job *job_to_insert_after, job *newjob)
{
    newjob->next = job_to_insert_after->next;
    job_to_insert_after->next = newjob;
}

void insert_after_operation(operation *operation_to_insert_after, operation *newoperation)
{
    newoperation->next = operation_to_insert_after->next;
    operation_to_insert_after->next = newoperation;
}

void insert_after_machine(machine *machine_to_insert_after, machine *newmachine)
{
    newmachine->next = machine_to_insert_after->next;
    machine_to_insert_after->next = newmachine;
}

//

job *insert_job_at_end(job **jobhead, job *job_to_insert)
{
    job_to_insert->next = NULL;

    if (*jobhead == NULL)
        *jobhead = job_to_insert;
    else
    {
        job *last = *jobhead;

        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = job_to_insert;
    }
    return *jobhead;
}

operation *insert_operation_at_end(operation **operationhead, operation *operation_to_insert)
{
    operation_to_insert->next = NULL;

    if (*operationhead == NULL)
        *operationhead = operation_to_insert;
    else
    {
        operation *last = *operationhead;

        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = operation_to_insert;
    }
    return *operationhead;
}

machine *insert_machine_at_end(machine **machinehead, machine *machine_to_insert)
{
    machine_to_insert->next = NULL;

    if (*machinehead == NULL)
        *machinehead = machine_to_insert;
    else
    {
        machine *last = *machinehead;

        while (last->next != NULL)
        {
            last->next->prev = last;
            last = last->next;
        }
        last->next = machine_to_insert;
        machine_to_insert->prev = last;
    }
    return *machinehead;
}

//

job *find_job(job *head, int JobNumber)
{
    job *tmp = head;
    job *jobtmp;

    while (tmp != NULL)
    {
        jobtmp = tmp;
        tmp = tmp->next;
    }
    if (JobNumber == 0)
    {
        printf("\nSelect Job: ");
        JobNumber = GetInt(1, jobtmp->JobNumber);
    }

    tmp = head;
    while (tmp != NULL)
    {
        if (tmp->JobNumber == JobNumber)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

operation *find_operation(operation *head, int OperationNumber, int JobNumber)
{
    operation *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->OperationNumber == OperationNumber && tmp->JobNumber == JobNumber)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

machine *find_machine(machine *head, int MachineNumber)
{
    machine *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->MachineNumber == MachineNumber)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

//

operation *alter_operation(operation *operation_to_alter)
{
    printf("Old Job Number: %d\tNew Job Number: ", operation_to_alter->OperationNumber);
    scanf(" %d", &operation_to_alter->OperationNumber);
}

void *remove_job(job **head, job *job_to_remove)
{
    job *tmp;

    if ((*head)->JobNumber == job_to_remove->JobNumber)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
    else
    {
        job *current = *head;
        while (current->next != NULL)
        {
            if (current->next->JobNumber == job_to_remove->JobNumber)
            {
                tmp = current->next;
                current->next = current->next->next;
                free(tmp);
                break;
            }
            else
            {
                current = current->next;
            }
        }
    }
}

void *remove_operation(operation **head, int OperationNumber)
{
    operation *tmp;

    if ((*head)->OperationNumber == OperationNumber)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
    else
    {
        operation *current = *head;
        while (current->next != NULL)
        {
            if (current->next->OperationNumber == OperationNumber)
            {
                tmp = current->next;
                current->next = current->next->next;
                free(tmp);
                break;
            }
            else
            {
                current = current->next;
            }
        }
    }
}

void *remove_machine(machine **head, int MachineNumber)
{
    machine *tmp;

    if ((*head)->MachineNumber == MachineNumber)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
    else
    {
        machine *current = *head;
        while (current->next != NULL)
        {
            if (current->next->MachineNumber == MachineNumber)
            {
                tmp = current->next;
                current->next = current->next->next;
                free(tmp);
                break;
            }
            else
            {
                current = current->next;
            }
        }
    }
}
