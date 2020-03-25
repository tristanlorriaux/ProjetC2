#include "blockchain.h"


void ajout_block(Donnee* message){
    
    if(Genesis==NULL)//Initialisation de la blockhain
    {
        Genesis = (struct bloc *)malloc(sizeof(struct bloc));
        Genesis->donnee = (Donnee*)malloc(sizeof(Donnee));
        Genesis->lien = NULL;
        Genesis->index = 0;
        Genesis->nonce = 0;
        strcpy(Genesis->precHash, "");
        init_Data(Genesis->donnee);
    }
    struct bloc *currentbloc = Genesis;
    while(currentbloc->lien != NULL)//Idem aux listes chaînées
    {
        currentbloc=currentbloc->lien;
    }
    
    struct bloc *nouv_bloc = (struct bloc *)malloc(sizeof(struct bloc));  
    nouv_bloc->donnee = (Donnee*)malloc(sizeof(Donnee));  
    
    nouv_bloc->lien = NULL;    
    nouv_bloc->donnee = message;
    nouv_bloc->index = currentbloc->index + 1;    
    strcpy(nouv_bloc->precHash, currentbloc->Hash);
    //hash256(nouv_bloc->Hash, toString(nouv_bloc));
    printBlock(nouv_bloc);
    calculHash(nouv_bloc);

    if(IsValidBlock(nouv_bloc,currentbloc))
    {
        currentbloc->lien = nouv_bloc;
    }
    else
    {
        printf("Bloc invalide, espece de hacker va!\n");
    }
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
        if(hashCompare(SHA256(toString(prev), sizeof(*prev), NULL), curr->precHash))
        {
            hashPrinter(
                    SHA256(toString(prev), sizeof(*prev), curr->precHash),
                    HASH_SIZE);
            printf("\n");
        }
    }
}

unsigned char *toString(struct bloc *bloc)
{
    unsigned char *str = (unsigned char *)malloc(sizeof(unsigned char )*sizeof(bloc));
    
    unsigned char b[3];
    unsigned char c[32];
    sprintf(b, "%d", bloc->index);    
    strcpy(str, b);
    strcat(str, bloc->precHash);
    strcat(str, bloc->donnee->date);
    strcat(str, bloc->donnee->dest);
    strcat(str, bloc->donnee->exp);
    strcat(str, bloc->donnee->message);
    sprintf(c, "%ld", bloc->nonce);    
    strcat(str, c);
    return str;
}

void hashPrinter(unsigned char hash[], int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%02x",hash[i]);
    }
    printf("\n");
}

int hashCompare(unsigned char *str1, unsigned char *str2)
{
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        if(str1[i] != str2[i])
            return 0;
    return 1;
}

void printBlock(struct bloc *blocs)
{
    printf("bloc %d : ", blocs->index);
    printf("precHash : ");
    hashPrinter(blocs->precHash, sizeof(blocs->precHash));
    printf(" [%s]->", blocs->donnee->exp);
    printf("[%s] ", blocs->donnee->dest);
    printf("%s : ", blocs->donnee->date);
    printf("%s //", blocs->donnee->message);
    printf("Hash : ");
    hashPrinter(blocs->Hash, sizeof(blocs->Hash));
    printf("  %p\n\n",blocs->lien);
}

void printAllBlock(void)
{
    struct bloc * curr = Genesis;
    while(curr)
    {
        printBlock(curr);
        curr = curr->lien;
    }
}

void init_Data(Donnee* data)
{
    strcpy(data->date, "");
    strcpy(data->dest, "");
    strcpy(data->exp, "");
    strcpy(data->message, "");
}




int HashMatchesDifficulty(const char Hex[HASH_HEX_SIZE])
{
    
    char binaryHash[BINARY_SIZE];
    hexToBinary(Hex, binaryHash);

    // Creation de la chaine de caractère "0"*difficulty
    char *prefix = malloc(DIFFICULTY + 1);
    memset(prefix, '0', DIFFICULTY);
    prefix[DIFFICULTY] = '\0';
    
    char *checker = NULL;
    checker = strstr(binaryHash, prefix);
    printf("cond : %d\n", strcmp(checker, binaryHash));
    return strcmp(checker, binaryHash);
}

void hexToBinary(const char *input, char *output)
{

    long int i = 0;
    while (input[i])
    {

        switch (input[i])
        {
        case '0':
            strcat(output, "0000");
            break;
        case '1':
            strcat(output, "0001");
            break;
        case '2':
            strcat(output, "0010");
            break;
        case '3':
            strcat(output, "0011");
            break;
        case '4':
            strcat(output, "0100");
            break;
        case '5':
            strcat(output, "0101");
            break;
        case '6':
            strcat(output, "0110");
            break;
        case '7':
            strcat(output, "0111");
            break;
        case '8':
            strcat(output, "1000");
            break;
        case '9':
            strcat(output, "1001");
            break;
        case 'A':
        case 'a':
            strcat(output, "1010");
            break;
        case 'B':
        case 'b':
            strcat(output, "1011");
            break;
        case 'C':
        case 'c':
            strcat(output, "1100");
            break;
        case 'D':
        case 'd':
            strcat(output, "1101");
            break;
        case 'E':
        case 'e':
            strcat(output, "1110");
            break;
        case 'F':
        case 'f':
            strcat(output, "1111");
            break;
        default:
            printf("Invalid hexadecimal digit %c\n",
                   input[i]);
        }
        i++;
    }
}

void hash256(struct bloc* Bloc, const char *input)
{

    size_t length = strlen(input);
    unsigned char md[HASH_SIZE];
    SHA256((const unsigned char*)input, length, md);
    memcpy(Bloc->Hash,md, HASH_SIZE);

    return;
}

bool IsValidBlock(struct bloc* newBlock, struct bloc* previousBlock)
{
    if(previousBlock->index + 1 != newBlock->index)
    {
        printf("%d\n", 1);
        return false;
    }
    int ret = strcmp(previousBlock->Hash, newBlock->precHash);
    if(ret != 0)
    {
        printf("%d\n", 2);
        return false;
    }
    struct bloc *bloc_test = (struct bloc *)malloc(sizeof(struct bloc));  
    bloc_test->donnee = (Donnee*)malloc(sizeof(Donnee));
    hash256(bloc_test->Hash, toString(newBlock));
    
    int res = strcmp(bloc_test->Hash, newBlock->Hash);
    if(res != 0)
    {
        printf("%d\n", 3);
        return false;
    }
    return true;
}

void calculHash(struct bloc* Bloc)
{
    
    Bloc->nonce = 0;
    char hash_hex[HASH_HEX_SIZE] = "";
    //hashPrinter(hash_test,HASH_SIZE);
    hash256(Bloc, toString(Bloc)); // mise à jour du hash
    printf("Hash normal : ");
    hashPrinter(Bloc->Hash,HASH_SIZE);
    
    Hex_Hash(Bloc, hash_hex);
    printf("Hex : %s\n",hash_hex);
    //hashPrinter(hash_test,HASH_SIZE);
    int b = HashMatchesDifficulty(hash_hex);
    printf("bool = %d\n", b);
    while(b != 0)
    {
        printf("yo\n");
        Bloc->nonce++;
        
        hash256(Bloc, toString(Bloc)); // mise à jour du hash
        printf("nouveau Hash : ");
        hashPrinter(Bloc->Hash,HASH_SIZE);
        strcpy(hash_hex, "");
        Hex_Hash(Bloc, hash_hex);       //Conversion du hash en hex
        printf("nouveau Hex : %s\n",hash_hex);
        b = HashMatchesDifficulty(hash_hex);
        
    }
}

char *Hex_Hash(struct bloc *Bloc, char *output)
{

    /*char bloc_string[100];
    strcpy(bloc_string, toString(bloc));*/

    unsigned char hash_value[HASH_SIZE] = "";
    strcpy(hash_value, Bloc->Hash);
    
    char buffer[3];
    char hex_hash[HASH_HEX_SIZE] = {0};
    for(int i = 0; i < HASH_SIZE; i++) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer,"%02x", hash_value[i]);
        strcat(hex_hash, buffer);
    }

    strcpy(output,hex_hash);

    output[HASH_HEX_SIZE] = 0;

    return output;
}
