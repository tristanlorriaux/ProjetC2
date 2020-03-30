all: blockchain

blockchain: blockchain.o main.o compte.o saisi.o sdl.o
	gcc -o blockchain blockchain.o main.o compte.o saisi.o sdl.o -lssl -lcrypto -lSDL2main -lSDL2 -lSDL_ttf

blockchain.o: blockchain.c
	gcc -o blockchain.o -c blockchain.c -W -Wall -std=c99 -lssl -lcrypto -lSDL2main -lSDL2

compte.o: compte.c blockchain.h saisi.h
	gcc -o compte.o -c compte.c -W -Wall -std=c99 

saisi.o: saisi.c
	gcc -o saisi.o -c saisi.c -W -Wall -std=c99 

sdl.o: sdl.c compte.h
	gcc -o sdl.o -c sdl.c -W -Wall -std=c99 -lSDL2main -lSDL2 -lSDL_ttf -lSDL_image

main.o: main.c blockchain.h compte.h saisi.h sdl.h
	gcc -o main.o -c main.c -W -Wall -std=c99


clean:
	rm -rf *.o

mrproper: clean
	rm -rf blockchain