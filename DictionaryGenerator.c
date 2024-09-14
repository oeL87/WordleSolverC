#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH 1000
#define MAX_WORDS 200000
#define WORD_LENGTH 6
#define TABLE_SIZE 10000

typedef struct Node {
    char word[WORD_LENGTH];
    struct Node* next; 
} Node;

typedef struct HashTable {
    Node* table[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* word) {
    unsigned int hashValue = 0;
    for (int x = 0; word[x] != '\0'; x++) {
        hashValue = (hashValue * 31) + word[x];
    }

    return hashValue % TABLE_SIZE;
}

bool insertWord(HashTable* map, const char* word) {
    unsigned int index = hash(word);
    
    // Check if the word already exists in the chain
    Node* current = map->table[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return false;  // Word already exists
        }
        current = current->next;
    }
    
    // Insert new word at the beginning of the chain
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Error occurred, memory allocation failed");
        return false;
    }
    strcpy(new_node->word, word);
    new_node->next = map->table[index];
    map->table[index] = new_node;

    return true;
}

void initHashMap(HashTable* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;  // Initialize each bucket to NULL
    }
}

void freeHashMap(HashTable* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = map->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

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