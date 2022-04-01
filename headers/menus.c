/**
 * Author: Bernardo Neves
 * Email: a23494@alunos.ipca.pt
 * Date: 01/04/2022
 * Description: Menus
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "menus.h"
#include "lists.h"

void MainMenu()
{
    FILE *jobFile;
    job *jobHead = NULL;
    jobHead = read(jobFile, jobHead);
    int choice;

    do
    {
        printf("\t--- MAIN MENU ---\n"
               "\t Enter 1 - List \n"
               "\t Enter 2 - Add Operation\n"
               "\t Enter 3 - Remove Operation\n"
               "\t Enter 4 - Alter Operation\n"
               "\t Enter 5 - Minimum Time\n"
               "\t Enter 6 - Maximum Time\n"
               "\t Enter 7 - Average Time\n"
               "\n\t Enter 0 - Quit\n");

        choice = GetInt(0, 7);
        switch (choice)
        {
        case 1:
            PrintJobList(jobHead);
            break;
        case 2:
            UserCreateOperation(jobHead);
            break;
        case 3:
            UserRemoveOperation(jobHead);
            break;
        case 4:
            UserAlterOperation(jobHead);
            break;
        case 5:
            timeMin(select_job(jobHead));
            break;
        case 6:
            timeMax(select_job(jobHead));
            break;
        case 7:
            timeAverage(select_job(jobHead));
            break;
        case 0:
            break;
        default:
            printf("\n\t//Invalid Option//\n\n");
            MainMenu();
            break;
        }
        if (choice != 0 && choice != 4)
        {
            printf("\n\tPress any key to go back");
            getch();
            system("cls");
        }

    } while (choice != 0);
    write(jobFile, jobHead);
    _Exit(0);
}
