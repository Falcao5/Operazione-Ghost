#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORDS 5

#define PASSWORD_LENGTH 10

typedef char password[PASSWORD_LENGTH];

char fileToReadName[100] = "passwords.txt";

void readPasswordsFromFile(char *fileName){
    FILE* file = fopen(fileName, "r"); /* should check the result */
    password line;
    int i=0;

    while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        printf("%s",line);
        i++;
    }

    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

}

int main()
{

    readPasswordsFromFile(fileToReadName);



    return 0;
}
