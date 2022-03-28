#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

int GetInt(int min, int max) // gets the user choice as an integer between or equal to min and max
{
    int ChoiceInt = -1; // -1 so it automatically gives error if user's input is not an integer
    char ChoiceChar;    // char buffer to read a letter so when the user inputs a letter it resets the ChoiceInt Buffer
    printf("\n\t> ");
    scanf(" %d", &ChoiceInt);
    scanf("%c", &ChoiceChar);
    while (ChoiceInt > max || ChoiceInt < min) // check if user input is in the range of the menu options and repeats the code if not
    {
        printf("\n\t//Invalid Option//\n\n");
        printf("\n> ");
        scanf(" %d", &ChoiceInt);
        scanf("%c", &ChoiceChar);
    }
    system("cls");    // clears the console
    return ChoiceInt; // returns user choice
}

// char GetsUppercase(char Buffer[200])
// {
//     gets(Buffer); // reads line from user input to Buffer

//     for (int i = 0; i < strlen(Buffer); i++) // loops for the length of Buffer
//     {
//         Buffer[i] = toupper(Buffer[i]); // swaps each letter for it's upper case version
//     }
// }



// char GetChar()
// {
//     int ChoiceInt = -1;
//     char ChoiceChar;
//     printf("\n> ");
//     scanf(" %c", &ChoiceChar);
//     while (!((ChoiceChar >= 'a' && ChoiceChar <= 'z') || (ChoiceChar >= 'A' && ChoiceChar <= 'Z')))
//     {
//         printf("\n\t//Invalid Option//\n\n");
//         printf("\n> ");
//         scanf(" %c", &ChoiceChar);
//     }
//     system("cls");
//     return ChoiceChar;
// }
