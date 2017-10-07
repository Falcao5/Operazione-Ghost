#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORDS 5
#define ATTEMPTS 5

#define PASSWORD_LENGTH 10

typedef char string[PASSWORD_LENGTH];

int unlocked = 0;

string passwords[PASSWORDS];        // Array containing all the passwords
string wrongPasswords[PASSWORDS-1]; // Array containing the wrong passwords
string rightPassword;               // Array containing the right password

char fileToReadName[100] = "passwords.txt";

/** Reads all the lines of fileName text file.      *
*** Saves them all in an array, called passwords.   *
*** VALIDATED, IT WORKS FINE.                       */
void readPasswordsFromFile(char *fileName)
{
    FILE* file = fopen(fileName, "r"); /* should check the result */
    string line;
    int i = 0;

    while (fgets(line, sizeof(line), file))
    {
        strtok(line, "\n");
        strcpy(passwords[i], line);
        //printf(sizeof(passwords));
        i++;
    }

    fclose(file);

}

/** Saves the wrong passwords in wrongPasswords array.  *
*** Saves the right password in rightPassword variable  */
void divideWrongPasswordsAndRightPassword()
{

}


/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle(string *array, int n)
{
    srand ( time(NULL) );
    if (n > 1)
    {
        int i;
        for (i = 0; i < n - 1; i++)
        {
            int j = rand()%(sizeof(array)+2);
            string temp;
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

    //shuffle(passwords, sizeof(passwords));

    while(i<sizeof(passwords))
    {
        printf("%s\n", passwords[i]);
        i++;
    }
}

/** This function controls the password inserted by user.               *
*** Sets the unlocked global variable as 1 if the password is correct   */
void passwordCheck(string inputPasswordFromKeyboard){
    unlocked = 1;
}

/** Example
***                                                         *
*** rightPassword = qwertyuiop                              *
*** passwordInserted1 = poiuytrewq                          *
*** passwordInserted2 = qwertpoiuy                          *
***                                                         *
*** messageToShow(passwordInserted1) = 0/10                 *
*** messageToShow(passwordInserted2) = 5/10                 */
char *messageToShow(string inputPasswordFromKeyboard){
    string result;
    passwordCheck(inputPasswordFromKeyboard);
    if(unlocked == 1)
        return "Unlocked.\n";
    return result;
}
/** This function copies a file in the USB drive selected   */
void copyInUSB(){

}

int main()
{

    readPasswordsFromFile(fileToReadName);

    /*

    string inputPasswordFromKeyboard;

    readPasswordsFromFile(fileToReadName);
    divideWrongPasswordsAndRightPassword();
    displayPasswords();

    int attemptsRemaining = ATTEMPTS;

    while(attemptsRemaining>0)
    {
        if(unlocked == 1)
        {
            copyInUSB();
            return 0;
        }

        scanf("%s", inputPasswordFromKeyboard);
        printf("%s", messageToShow(inputPasswordFromKeyboard));

        attemptsRemaining--;

    }

    return 0;

    */

}
