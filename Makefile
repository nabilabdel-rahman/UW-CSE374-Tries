t9: tnine.o trie.o
	gcc -Wall -g -std=c17 -o t9 tnine.o trie.o

trie.o: trie.c trienode.h
	gcc -Wall -g -std=c17 -c trie.c

tnine.o: tnine.c trienode.h
	gcc -Wall -g -std=c17 -c tnine.c

clean:
	rm -f *.o t9 *~