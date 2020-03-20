#include "openssl/sha.h"
#include "openssl/crypto.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 200 //Taille max de la blockchain
#define M 150 //taille max des string
typedef struct{
    char message[M];
    char exp[20];
    char dest[20];
    char date[20];
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
void init_Data(Donnee* data);
