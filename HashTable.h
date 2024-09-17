#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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