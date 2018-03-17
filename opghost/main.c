#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILENAME_TO_CREATE "soluzione.txt"
#define FILENAME_RIGHT_PASSWORD "rightPassword.txt"
#define FILENAME_TO_READ "passwords.txt"
#define FILENAME_SOLUTION "solution.txt"

typedef char *stringa;

int passwordLength = 0;
int passwordsNumber = 0;

void calculatePasswordsLength(char *fileName)
{
    FILE* file = fopen(fileName, "r"); /* should check the result */
    stringa line = (stringa)malloc(100*sizeof(char));
    fgets(line, 100*2, file);
    strtok(line,"\n");
    passwordLength = strlen(line);

    fclose(file);
}

void calculatePasswordsNumber(char *fileName)
{
    int result = 0;
    FILE* file = fopen(fileName, "r"); /* should check the result */
    stringa line = (stringa)malloc(100*sizeof(char));
    fgets(line, 100*2, file);
    while (fgets(line, 100*2, file))
        result++;
    passwordsNumber = result+1;

    fclose(file);
}

/** Reads all the lines of fileName text file.      *
*** Saves them all in an array, called passwords.   *
*** VALIDATED, IT WORKS FINE.                       */
stringa *readPasswordsFromFile(char *fileName)
{
    FILE* file = fopen(fileName, "r"); /* should check the result */

    calculatePasswordsLength(fileName);
    calculatePasswordsNumber(fileName);

    stringa *result = (stringa*)malloc(passwordsNumber*sizeof(stringa));
    stringa line = (stringa)malloc((passwordLength-1)*sizeof(char));

    int i = 0;

    while (fgets(line, (passwordLength-1)*2, file))
    {
        strtok(line, "\n");
        result[i] = (stringa)malloc((passwordLength-1)*sizeof(char));
        strcpy(result[i], line);
        i++;
    }

    fclose(file);

    return result;
}

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle(stringa *array, int n)
{
    stringa temp = (stringa)malloc(passwordLength*sizeof(char));
    strcpy(temp, array[passwordLength-1]);
    strcpy(array[passwordLength/2],array[passwordLength-1]);
    strcpy(array[passwordLength/2],temp);

    srand ( time(NULL) );
    if (n > 1)
    {
        int i;
        for (i = 0; i < n - 1; i++)
        {
            int j = rand()%(n+1);
            temp = (stringa)malloc(passwordLength*sizeof(char));
            strcpy(temp, array[j]);
            strcpy(array[j],array[i]);
            strcpy(array[i],temp);
        }
    }
}

void displayRandomNumbersAndSymbols(int length)
{
    int i = 0;
    int randomI = rand() % 256;
    char randomC = 'A' + (rand() % 26);

    while(i<length)
    {
        if(i%2==0)
        {
            randomI = rand()%64;
            randomC = 'a' + (rand() % 26);
        }
        if(i%4==0)
        {
            randomI = rand()%128;
            randomC = '0' + (rand() % 26);
        }
        if(i%8==0)
        {
            randomI = rand()%256;
            randomC = 'A' + (rand() % 26);
        }

        printf("%d", randomI);
        printf("%c", randomC);

        randomC = '@' + (rand() % 26);
        i++;
    }
}

/** This function shuffles the array containing all the passwords, then prints it shuffled         *
*** VALIDATED, IT WORKS FINE.                                                                       *
*** MISSING GUI                                                                                     */
void displayPasswords(stringa *passwords)
{
    int i = 0;
    int randomNumber;

    while(i<passwordsNumber)
    {
        randomNumber = rand()%256;
        displayRandomNumbersAndSymbols(randomNumber);
        printf("     %s     ", passwords[i]);
        displayRandomNumbersAndSymbols(randomNumber);
        i++;
    }
    printf("\n");
}

int occurrencesCounter(stringa inputPasswordFromKeyboard, stringa rightPassword)
{
    int result = 0;
    int i = 0;

    for(i=0; i<(passwordLength-1); i++)
    {
        if(inputPasswordFromKeyboard[i] == rightPassword[i])
            result++;
    }

    return result;
}

/** This function controls the password inserted by user.               *
*** Sets the unlocked global variable as 1 if the password is correct   */
void passwordCheck(stringa inputPasswordFromKeyboard, int *unlocked, stringa rightPassword)
{
    if(strcmp(inputPasswordFromKeyboard, rightPassword) == 0)
        *unlocked = 1;
}

/** Example
***                                                         *
*** rightPassword = qwertyuiop                              *
*** passwordInserted1 = poiuytrewq                          *
*** passwordInserted2 = qwertpoiuy                          *
***                                                         *
*** messageToShow(passwordInserted1) = 0/10                 *
*** messageToShow(passwordInserted2) = 5/10                 */
void messageToShow(stringa inputPasswordFromKeyboard, int *unlocked, stringa rightPassword)
{
    passwordCheck(inputPasswordFromKeyboard, unlocked, rightPassword);
    if(*unlocked == 1)
    {
        printf("%s", "Unlocked. File created.\n");
    }
    else
    {
        printf("Locked. %d/%d Correct\n", occurrencesCounter(inputPasswordFromKeyboard,rightPassword),(passwordLength));
    }
}

/**
*** returns the correct password read from the txt hidden file
*/
stringa correctPassword()
{
    FILE *fp = fopen(FILENAME_RIGHT_PASSWORD, "r");
    stringa result = (stringa)malloc(sizeof(stringa));

    fscanf(fp, "%s", result);

    fclose(fp);

    return result;
}

/**
*** creates a file named FILENAME_TO_CREATE, and writes in this file the content inside FILENAME_SOLUTION
***/
void createFile()
{
    FILE *fpToCreate = fopen(FILENAME_TO_CREATE, "w+");
    FILE *solution = fopen(FILENAME_SOLUTION, "r");

    stringa temp = (stringa)malloc(sizeof(stringa));
    fscanf(solution, "%s", temp);

    fprintf(fpToCreate, "%s", temp);

    fclose(fpToCreate);
    fclose(solution);
}

int main()
{
    displayRandomNumbersAndSymbols(20000);

    stringa *passwords = readPasswordsFromFile(FILENAME_TO_READ);
    stringa rightPassword = (stringa)malloc(passwordLength*sizeof(char));
    strcpy(rightPassword, correctPassword());
    shuffle(passwords, passwordsNumber-1);
    displayPasswords(passwords);

    int *unlocked = (int*)malloc(sizeof(int));
    *unlocked = 0;
    stringa inputPasswordFromKeyboard;

    while(*unlocked==0)
    {
        inputPasswordFromKeyboard = (stringa)malloc(10*passwordsNumber*sizeof(char));
        scanf("%s", inputPasswordFromKeyboard);
        messageToShow(inputPasswordFromKeyboard, unlocked, rightPassword);
    }

    if(*unlocked == 1)
    {
        createFile();
        return 0;
    }

    return 0;
}
