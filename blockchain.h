#include "openssl/sha.h"
#include "openssl/crypto.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 200           //Taille max de la blockchain
#define M 150           //taille max des messages
#define DIFFICULTY 4    //Difficulté de la proof of work

#define HASH_SIZE 32
#define HASH_HEX_SIZE 65
#define BINARY_SIZE (HASH_HEX_SIZE*4+1)
#define BLOCK_STR_SIZE 100

typedef struct{
    char message[M];
    char exp[20];
    char dest[20];
    char date[20];
}Donnee;

struct bloc{
    char precHash[HASH_HEX_SIZE];
    char Hash[HASH_HEX_SIZE];
    int index;
    Donnee* donnee;
    int nonce;
    struct bloc *lien;
}*Genesis;

void ajout_block(Donnee* message);


//void hackChain(void);
char *toString(struct bloc *blocks, char *str);
void hashPrinter(unsigned char hash[], int length);
int hashCompare(unsigned char *str1, unsigned char *str2);
void printBlock(struct bloc *blocs);
void printAllBlock(void);
void init_Data(Donnee* data);
bool HashMatchesDifficulty(char Hex[HASH_HEX_SIZE]);
void hexToBinary(char input[HASH_HEX_SIZE], char output[BINARY_SIZE]);
void hash256(unsigned char *output, const char *input);
bool IsValidBlock(struct bloc* newBlock, struct bloc* previousBlock);
void calculHash(struct bloc* Block);
char *Hex_Hash(struct bloc *Bloc, char *output);
//bool startsWith(const char *pre, const char *str);
