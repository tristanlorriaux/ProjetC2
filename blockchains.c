#include "blockchain.h"


void ajout_bloc(Donnee* message){
    if(Genesis=NULL)//Initialisation de la blockhain
    {
        Genesis=malloc(sizeof(struct bloc));
        SHA256("", sizeof(""),Genesis->precHash);
    }
    struct bloc *currentbloc=Genesis;
    while(currentbloc->lien)//Idem aux listes chaînées
    {
        currentbloc=currentbloc->lien;
    }
    struct bloc *nouv_bloc=malloc(sizeof(struct bloc));
    currentbloc->lien=nouv_bloc;
    nouv_bloc->donnee=message;
    SHA256(toString(*currentbloc), sizeof(*currentbloc),nouv_bloc->precHash);

}

void verifyChain(void )
{
    if (Genesis == NULL)
    {
        printf("blocChain is emty! try again after adding some blocs");
        return;
    }
    struct bloc *curr = Genesis->lien;
    struct bloc *prev = Genesis;
    int count = 1;
    while(curr)
    {
        printf("%d\t[%d]\t",count++, curr->donnee);
        hashPrinter(SHA256(toString(*prev), sizeof(*prev), NULL),SHA256_DIGEST_LENGTH);
        printf(" - ");
        hashPrinter(curr->precHash,SHA256_DIGEST_LENGTH);
        if(hashCompare(SHA256(toString(*prev), sizeof(*prev), NULL), curr->precHash))
            printf(" Verified!\n");
        else
            printf("Verification Failed !\n");
        prev = curr;
        curr = curr->lien;
    }
}
void alterNthbloc(int n, Donnee* newData)
{
    struct bloc * curr = Genesis;
    if(curr == NULL)
    {
        printf("Nth bloc does ot exist! \n");
        return;
    }
    int count = 1;
    while(count != n)
    {
        if(curr->lien == NULL && count != n)
        {
            printf("Nth bloc does not exist!\n");
            return;
        }
        else if(count == n)
            break;
        curr = curr->lien;
        count++;
    }
    printf("before: ");
    printBloc(curr);
    curr->donnee = newData;
    printf("\n After");
    printBloc(curr);
    printf("\n");
}

void hackChain(void)
{
    struct bloc * curr = Genesis;
    struct bloc * prev;

    if(curr == NULL)
    {
        printf("blocChain is emty!\n");
        return;
    }

    while(1)
    {
        prev = curr;
        curr = curr->lien;
        if(curr == NULL)
            return;
        if(hashCompare(SHA256(toString(*prev), sizeof(*prev), NULL), curr->precHash))
        {
            hashPrinter(
                    SHA256(toString(*prev), sizeof(*prev), curr->precHash),
                    SHA256_DIGEST_LENGTH);
            printf("\n");
        }
    }
}

unsigned char *toString(struct bloc blocs)
{
    unsigned char *str = malloc(sizeof(unsigned char )*sizeof(blocs));
    memcpy(str, &blocs, sizeof(blocs));
    return str;
}

void hashPrinter(unsigned char hash[], int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%02x",hash[i]);
    }
}

int hashCompare(unsigned char *str1, unsigned char *str2)
{
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        if(str1[i] != str2[i])
            return 0;
    return 1;
}

void printbloc(struct bloc *blocs)
{
    printf("%p]\n", blocs);
    hashPrinter(blocs->precHash, sizeof(blocs->precHash));
    printf("\t[%d]\t", blocs->donnee);
    printf("%p\n",blocs->lien);
}

void printAllbloc(void)
{
    struct bloc * curr = Genesis;
    int count = 0;
    while(curr)
    {
        printbloc(curr);
        curr = curr->lien;
    }
}
