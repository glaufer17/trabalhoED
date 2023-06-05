all: main

main: main.o Patricia TAD.o  
	gcc obj/main.o obj/Patricia TAD.o -o bin/main.exe	


Patricia TAD.o: src/Patricia TAD.c include/Patricia TAD.h
	gcc -I include -Wall -Werror -c src/Patricia TAD.c -o obj/Patricia TAD.o

main.o: Apps/main.c include/deque_como_vetor.h
	gcc -I include -Wall -Werror -c Apps/main.c -o obj/main.o

run:
	./bin/main.exe	

clean:
	del bin\main.exe obj\*.o 	