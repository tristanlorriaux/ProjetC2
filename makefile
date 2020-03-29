all: blockchain

blockchain: blockchain.o main.o compte.o
	gcc -o blockchain blockchain.o main.o compte.o -lssl -lcrypto

blockchain.o: blockchain.c
	gcc -o blockchain.o -c blockchain.c -W -Wall -std=c99 -lssl -lcrypto

compte.o: compte.c blockchain.h
	gcc -o compte.o -c compte.c -W -Wall -std=c99 

main.o: main.c blockchain.h compte.h
	gcc -o main.o -c main.c -W -Wall -std=c99


clean:
	rm -rf *.o

mrproper: clean
	rm -rf blockchain
