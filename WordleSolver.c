#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main() {
    FILE *in_file = fopen("memory.txt", "r");

    if (in_file == NULL) {
        printf("Error Occurred, could not find file memory.txt in current directory");
        return 1;
    }

    
    char buffer[6];
    printf("What word did you guess? ");
    scanf("%5s", buffer);

    printf("%s", buffer);
    //Some kind of logic
    char nextGuess[6];

    printf("You should guess %s next", nextGuess);




    return 0;
}