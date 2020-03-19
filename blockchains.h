#include "openssl/sha.h"
#include "openssl/crypto.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 200 //Taille max de la blockchain

typedef struct{
    char *message;
    char *exp;
    char *dest;
    char *date;    
}Donnee;

struct bloc{
    unsigned char precHash[SHA256_DIGEST_LENGTH];
    unsigned char Hash[SHA256_DIGEST_LENGTH];
    Donnee* donnee;
    int index;
    struct bloc *lien;
}*Genesis;

void ajout_block(Donnee* message);
void verifyChain(void);
void alterNthBlock(int n, Donnee* newData);
void hackChain(void);
unsigned char *toString(struct bloc *blocks);
void hashPrinter(unsigned char hash[], int length);
int hashCompare(unsigned char *str1, unsigned char *str2);
void printBlock(struct bloc *blocs);
void printAllBlock(void);
