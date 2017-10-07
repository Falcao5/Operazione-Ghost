#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ATTEMPTS 5
#define PASSWORDS 5

int unlocked = 0;

typedef char *stringa;

char fileToReadName[100] = "passwords.txt";

/** Reads all the lines of fileName text file.      *
*** Saves them all in an array, called passwords.   *
*** VALIDATED, IT WORKS FINE.                       */
void readPasswordsFromFile(char *fileName)
{
    FILE* file = fopen(fileName, "r"); /* should check the result */
    stringa line;
    int i = 0;

    while (fgets(line, sizeof(line), file))
    {
        //strtok(line, "\n");
        //strcpy(passwords[i], line);
        //printf(sizeof(passwords));
        i++;
    }

    fclose(file);

}

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle(stringa *array, int n)
{
    srand ( time(NULL) );
    if (n > 1)
    {
        int i;
        for (i = 0; i < n - 1; i++)
        {
            int j = rand()%(sizeof(array)+2);
            stringa temp;
            strcpy(temp, array[j]);
            strcpy(array[j],array[i]);
            strcpy(array[i],temp);
        }
    }
}

/** This function shuffles the arrray containing all the passwords, then prints it shuffled     *
*** VALIDATED, IT WORKS FINE.                                                                   */
void displayPasswords()
{
    int i = 0;

    shuffle(passwords, sizeof(passwords));

    while(i<PASSWORDS)
    {
        printf("%s", passwords[i]);
        i++;
    }
}

int main()
{
    stringa inputPasswordFromKeyboard;

    readPasswordsFromFile(fileToReadName);
    //divideWrongPasswordsAndRightPassword();
    displayPasswords();

    //int attemptsRemaining = ATTEMPTS;

    //while(attemptsRemaining>0)
    //{
    //    if(unlocked == 1)
    //    {
    //        copyInUSB();
    //        return 0;
    //    }

    //    scanf("%s", inputPasswordFromKeyboard);
    //    printf("%s", messageToShow(inputPasswordFromKeyboard));

    //    attemptsRemaining--;

    //}

    return 0;

}
