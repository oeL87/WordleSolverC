#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "HashTable.h"

#define MAX_WORD_LENGTH 1000
#define MAX_WORDS 200000

bool isValidWord(const char *word) {
    for (int x = 0; word[x] != '\0'; x++) {
        if (!isalpha(word[x])) {
            return false;
        }
    }

    return true;
}

void toLower(char *word) {
    for (int x = 0; word[x] != '\0'; x++) {
        word[x] = tolower(word[x]);
    }
}

int main() {
    FILE* in_file = fopen("Oxford English Dictionary.txt", "r");
    FILE* memory = fopen("memory.txt", "r");
    
// || out_file == NULL
    if (in_file == NULL || memory == NULL) {
        printf("Error occurred, could not find file in current directory");
        return 1;
    }

    char word[MAX_WORD_LENGTH];
    HashTable fiveLetterWords;
    initHashMap(&fiveLetterWords);
    // if (fiveLetterWords == NULL) {
    //     printf("Error occurred, memory allocation failed");
    //     return 1;
    // }

    int numberOf5LetterWords = 0;
    while (fscanf(memory, "%s", word) == 1) {
        //assumed that the words in memory are already valid, just making it faster to read and write and future files.
        if (insertWord(&fiveLetterWords, word)) {
            printf("Successfully inserted %s\n", word);
        }
    }

    while (fscanf(in_file, "%s", word) == 1) {
        if (strlen(word) == 5 && isValidWord(word)) {            
            if (numberOf5LetterWords >= MAX_WORDS) {
                printf("Reached maximum word storage capacity.\n");
                break;
            }

            toLower(word);

            if (insertWord(&fiveLetterWords, word)) {
                printf("Successfully inserted %s\n", word);
            }
        }
    }

    // fputs(sub, out_file);
    fclose(in_file);
    // fclose(out_file);
    FILE* out_file = fopen("memory.txt", "w");

    if (out_file == NULL) {
        printf("Error occurred, could not find file in current directory");
        return 1;
    }

    printf("5-letter words found\n======================\n");
    for (int x = 0; x < TABLE_SIZE; x++) {
        Node* current = fiveLetterWords.table[x];
        
        // If the bucket is not empty, iterate through the linked list
        if (current != NULL) {
            printf("Bucket %d:", x);
            fprintf(out_file, "%s\n", current);
        }
        while (current != NULL) {
            printf("  %s\n", current->word);
            current = current->next;  // Move to the next node in the list
        }
    }

    // printf("5-letter words found\n======================\n");
    // for (int x = 0; x < numberOf5LetterWords; x++) {
    //     if (fiveLetterWords[x] != NULL) {
    //         printf("%s\n", fiveLetterWords[x]);
    //         fprintf(out_file, "%s\n", fiveLetterWords[x]);
    //         free(fiveLetterWords[x]);
    //         fiveLetterWords[x] = NULL;
    //     }
    // }

    freeHashMap(&fiveLetterWords);
    fclose(out_file);

    // free(buffer);

    return 0;
}