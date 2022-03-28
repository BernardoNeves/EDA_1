#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "menus.h"
#include "functions.h"
#include "lists.h"

void MainMenu()
{

    FILE *JobsFile;
    job *jobhead = NULL;
    jobhead = read(JobsFile, jobhead);
    int ChoiceInt;

    do
    {
        printf("\t--- MAIN MENU ---\n"
               "\t Enter 1 - List \n"
               "\t Enter 2 - Add \n"
               "\t Enter 3 - Remove \n"
               "\t Enter 4 - Change \n"
               "\n\t Enter 0 - Quit\n");

        ChoiceInt = GetInt(0, 5);
        switch (ChoiceInt)
        {
        case 1:
            PrintJobList(jobhead);
            break;
        case 2:

            break;
        case 3:
            PrintJobList(jobhead);
            remove_job(&jobhead, find_job(jobhead, 0));
            break;
        case 4:

            break;
        case 5:

            break;
        case 0:
            break;
        default:
            printf("\n\t//Invalid Option//\n\n");
            MainMenu();
            break;
        }
        if (ChoiceInt != 0)
        {
            printf("\n\tPress any key to go back");
            getch();
            system("cls");
        }

    } while (ChoiceInt != 0);
    write(JobsFile, jobhead);
}