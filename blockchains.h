#include "openssl/sha.h"
#include "openssl/crypto.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char message;
    char exp;
    char dest;
}Donnee;

struct bloc{
    char precHash[SHA256_DIGEST_LENGTH];
    Donnee* donnee;
    struct bloc *lien;
}*Genesis;

void ajout_bloc(Donnee* message);
void verifyChain(void);
void alterNthbloc(int n, Donnee* newData);
void hackChain(void);
unsigned char *toString(struct bloc blocks);
void hashPrinter(unsigned char hash[], int length);
int hashCompare(unsigned char *str1, unsigned char *str2);
void printbloc(struct bloc *blocs);
void printAllblocs(void);
