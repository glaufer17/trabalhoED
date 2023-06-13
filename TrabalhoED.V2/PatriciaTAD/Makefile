makefile
Copy code
all: app_main

app_main: app_main.o trie.o
	gcc obj/app_main.o obj/trie.o -o bin/app_main.out

trie.o: src/trie.c include/trie.h
	gcc -I include -Wall -Werror -c src/trie.c -o obj/trie.o

app_main.o: apps/app_main.c include/trie.h
	gcc -I include -Wall -Werror -c apps/app_main.c -o obj/app_main.o

run:
	./bin/app_main.out

valgrind:
	valgrind --leak-check=yes ./bin/app_main.out

clean:
	rm -f bin/app_main.out obj/*.o