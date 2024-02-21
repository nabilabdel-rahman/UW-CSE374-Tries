/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

// run_session run the on-going decoding interaction with the
// user.  It requires a previously build wordTrie to work.
void run_session(trieNode *wordTrie);

int main(int argc, char **argv) {
  FILE *dictionary = NULL;
  trieNode *wordTrie = NULL;

  // checks for valid arguments
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
    return EXIT_FAILURE;
  // reads dictionary
  } else {
    dictionary = fopen(argv[1], "r");
    if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  // build the trie
  wordTrie = build_tree(dictionary);
  fclose(dictionary);

  // run interactive session
  printf("Enter \"exit\" to quit.\n");
  char input[MAXLEN];
  char currentInput[MAXLEN];
  int boolean = 1;
  while (boolean) {
    printf("Enter Key Sequence (or \"#\" for next word):\n> ");
    scanf("%s", input);
    // exits interactive session
    if (strncmp(input, "exit", 5) == 0) {
      break;
    } else {
      // finds next T9onym
      if (strncmp(input, "#", 2) == 0 && currentInput != NULL) {
        int i = 0;
        while (boolean) {
          // adjusts input to find the next T9onym
          if (currentInput[i] == '\0') {
            currentInput[i] = '#';
            currentInput[i + 1] = '\0';
            break;
          }
          i++;
        }
      } else {
        // adjusts previous input to current input
        for (int j = 0; j < MAXLEN; j++) {
          currentInput[j] = input[j];
        }
      }
      // prints word with given input
      printf("\t%s\n", get_word(wordTrie, currentInput));
    }
  }

  // clean up
  free_tree(wordTrie);
  return(EXIT_SUCCESS);
}