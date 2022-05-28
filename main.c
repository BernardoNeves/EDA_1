/**
 * Author: Bernardo Neves
 * Email: a23494@alunos.ipca.pt
 * Date: 01/04/2022
 * Description: Main
 */
#include <stdio.h>
#include <stdlib.h>
#include "headers/menus.h"

void main()
{
   system("cls");
   mainMenu();
}

/* //TODO:
   * Get rid of printf's in lists.c //TODO DOING
   * Make lists.c's functions just return stuff
   * Implement Job list in the time calculations
   * Save process plan in a different file 
   * Maybe care about the process plan visualization idk
   * Try implementing either a binary search or a hash table for the job linked list
     Implement a binary search or a hash table for the operation linked list (copilot suggestion)
     Implement a binary search or a hash table for the machine linked list (copilot suggestion)
*/

/* //Ideas for the future: 

    why tho ?
    machines in a binary search tree sorted by time
    less time goes to left and more time goes to right reducing search times

    operations in a linked list?
    operations are the index of the machine binary trees

    jobs in linked list?
    in the job the on/off switch doesn't affect the time because the operation (n) only starts after operation (n-1) is done
    so the machines used in operation (n-1) are no longer being used

    process plan is all the jobs in the job linked list, so the whole file read represents the process plan,
    different files = different process plans
    search goes to the smaller end and checks for a on/off switch condition
    if on, it goes to the next bigger machine and repeats
    if off, turns it on and adds the time to the totalTime
    does this for all machines in the operation for all the opreations in the job and for all jobs,
    saving the total time and then printing the smallest of them all

*/