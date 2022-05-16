// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
  char word[LENGTH + 1];
  struct node * next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node * table[N];

// Returns true if word is in dictionary, else false
bool check(const char * word) {
  // TODO
  int n = strlen(word);
  char currentWord[n + 1];
  for (int i = 0; i < n + 1; i++) {
    if (i == n) {
      currentWord[n] = '\0';
    } else {
      currentWord[i] = tolower(word[i]);
    }
  }
  node * head = table[hash(currentWord)];

  while (head != NULL) {
    if (strcmp(head -> word, currentWord) == 0) {
      return true;
    }
    head = head -> next;
  }
  return false;
}

// Hashes word to a number
unsigned int hash(const char * word) {
  // TODO: Improve this hash function
  return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char * dictionary) {

  // TODO
  FILE * dict = fopen(dictionary, "r");
  if (dict == NULL) {
    return false;
  }
  char currentWord[LENGTH + 1] = "";
  char ch;
  while (fread( & ch, sizeof(char), 1, dict) && ch != EOF) {
    if (ch == '\n' && strcmp(currentWord, "") != 0) {
      node * n = malloc(sizeof(node));
      if (n == NULL) {
        return false;
      }
      strcpy(n -> word, currentWord);
      currentWord[0] = '\0';
      int wordIndex = hash(n -> word);

      n -> next = table[wordIndex];

      table[wordIndex] = n;
    } else if (isalpha(ch) || ch == '\'') {
      char lower = ch;
      if (isalpha(ch)) {
        lower = tolower(ch);
      }
      strncat(currentWord, & lower, 1);
    }
  }
  fclose(dict);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
  int size = 0;
  for (int i = 0; i < N; i++) {
    if (table[i]) {
      for (node * tmp = table[i]; tmp != NULL; tmp = tmp -> next) {
        size++;
      }
    }
  }
  return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
  for (int i = 0; i < N; i++)
    while (table[i] != NULL) {
      node * tmp = table[i] -> next;
      free(table[i]);
      table[i] = tmp;
    }
  return true;
}