/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

/* You'll want to prototype any helper functions you need here */

// creates a new node to be entered in the the trie
trieNode* create_node();

// checks whether or not the branch of the integer passed in
// of the node passed in is null or not. Creates a node as the
// branch  if not null and returns the branch.
trieNode* update(trieNode* node, int i);

/* You'll need to implement the functions declare in trienode.h */
/* As well as the helpfer functions you prototype above. */

trieNode* build_tree(FILE *dict) {
  char currentWord[MAXLEN];
  trieNode* root = create_node();
  trieNode* currentNode = root;
  // gets word from dictionary
  while (fgets(currentWord, MAXLEN, dict) != NULL) {
    int length = strlen(currentWord);
    char * copy = (char*) malloc(length);
    if (copy != NULL) {
      strncpy(copy, currentWord, length - 1);
      copy[length - 1] = '\0';
    }
    int i = 0;
    // traverses the tree to find node to store word and creates
    // nodes when necessary
    while (currentWord[i] != '\0') {
      // finds next correct node in the path to store the word
      if (currentWord[i + 1] == '\0') {
        while (currentNode->word != NULL) {
          currentNode = update(currentNode, 0);
        }
      } else if (currentWord[i] == 'a' || currentWord[i] == 'b' ||
        currentWord[i] =='c') {
        currentNode = update(currentNode, 1);
      } else if (currentWord[i] == 'd' || currentWord[i] == 'e' ||
        currentWord[i] == 'f') {
        currentNode = update(currentNode, 2);
      } else if (currentWord[i] == 'g' || currentWord[i] == 'h' ||
        currentWord[i] == 'i') {
        currentNode = update(currentNode, 3);
      } else if (currentWord[i] == 'j' || currentWord[i] == 'k' ||
        currentWord[i] == 'l') {
        currentNode = update(currentNode, 4);
      } else if (currentWord[i] == 'm' || currentWord[i] == 'n' ||
        currentWord[i] == 'o') {
        currentNode = update(currentNode, 5);
      } else if (currentWord[i] == 'p' || currentWord[i] == 'q' ||
        currentWord[i] == 'r' || currentWord[i] == 's') {
        currentNode = update(currentNode, 6);
      } else if (currentWord[i] == 't' || currentWord[i] == 'u' ||
        currentWord[i] == 'v') {
        currentNode = update(currentNode, 7);
      } else if (currentWord[i] == 'w' || currentWord[i] == 'x' ||
        currentWord[i] == 'y' || currentWord[i] == 'z') {
        currentNode = update(currentNode, 8);
      }
      i++;
    }
    // stores word in current node
    currentNode->word = copy;
    currentNode = root;
  }
  return root;
}

char* get_word(trieNode *root, char *pattern) {
  trieNode* currentNode = root;
  int child;
  int i = 0;
  // traverses trie until the node has been found
  while (pattern[i] != '\0') {
    // handles cases for "#" characters
    if (pattern[i] == '#') {
      if (currentNode->branches[0] == NULL) {
        return "There are no more T9onyms";
      } else {
        currentNode = currentNode->branches[0];
      }
    } else {
      // handles cases for numbers
      child = (int) (pattern[i])-49;
      if (currentNode->branches[child] == NULL) {
        return "Not found in current dictionary";
      } else {
        currentNode = currentNode->branches[child];
      }
    }
  i++;
  }
  // returns results of traversal
  if (currentNode->word != NULL) {
    return currentNode->word;
  }
  return "Not found in current dictionary";
}

void free_tree(trieNode *root) {
  // frees memory in branches first
  for (int i = 0; i < 9; i++) {
    if (root->branches[i] != NULL) {
      free_tree(root->branches[i]);
    }
  }
  // frees the node passed in
  if (root->word != NULL) {
    free(root->word);
  }
  free(root);
}

trieNode* create_node() {
  trieNode* newNode = (trieNode*) malloc(sizeof(trieNode));
  for (int i = 0; i < 9; i++) {
    newNode->branches[i] = NULL;
  }
  newNode->word = NULL;
  return newNode;
}

trieNode* update(trieNode* node, int i) {
  if (node->branches[i] == NULL) {
    node->branches[i] = create_node();
  }
  return node->branches[i];
}