#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    FILE *in_file = fopen("memory.txt", "r");

    if (in_file == NULL) {
        printf("Error Occurred, could not find file memory.txt in current directory");
        exit(-1);
    }


    return 0;
}