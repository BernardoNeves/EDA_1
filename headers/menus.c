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

void mainMenu()
{
    FILE *jobFile;
    job *jobHead = NULL;
    jobHead = read(jobFile, jobHead);
    int choice;

    while (choice != 0)
    {
        // printf("\t--- MAIN MENU ---\n"
        //        "\t Enter 1 - List \n"
        //        "\t Enter 2 - Add Operation\n"
        //        "\t Enter 3 - Remove Operation\n"
        //        "\t Enter 4 - Alter Operation\n"
        //        "\t Enter 5 - Minimum Time\n"
        //        "\t Enter 6 - Maximum Time\n"
        //        "\t Enter 7 - Average Time\n"
        //        "\n\t Enter 0 - Quit\n");

        choice = getInt(0, 10);
            timeAverage(findJob(jobHead, choice));

        // system("cls");
        // switch (choice)
        // {
        // case 1:
        //     printJobList(jobHead);
        //     break;
        // case 2:
        //     // userCreateOperation(jobHead);
        //     break;
        // case 3:
        //     // userRemoveOperation(jobHead);
        //     // removeMachine(&(jobHead->operationHeadPointer->machineHeadPointer), 1);
        //     removeOperation(&(jobHead->operationHeadPointer), 3);
        //     // removeJob(&jobHead, 2);
        //     break;
        // case 4:
        //     // userAlterOperation(jobHead);
        //     break;
        // case 5:
        //     timeMin(findJob(jobHead, 9));
        //     break;
        // case 6:
        //     timeMax(findJob(jobHead, 9));
        //     break;
        // case 7:
        //     timeAverage(findJob(jobHead, 6));
        //     break;
        // case 0:
        //     break;
        // default:
        //     printf("\n\t//Invalid Option//\n\n");
        //     mainMenu();
        //     break;
        // }
        // if (choice != 0 && choice != 4)
        // {
        //     printf("\n\tPress any key to go back");
        //     getch();
        //     system("cls");
        // }
    }
    write(jobFile, jobHead);
    _Exit(0);
}
