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
        printf("yo\n");
        currentbloc->lien = nouv_bloc;
    }
    else
    {
        printf("Bloc invalide, espece de hacker va!\n");
    }
    printf("grosse pute\n");
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

char *toString(struct bloc *bloc)
{
    if(bloc == NULL)
        return NULL;

    char *str = (unsigned char *)malloc(sizeof(unsigned char )*sizeof(bloc));
    
    char b[3];
    char c[32];
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




bool HashMatchesDifficulty(char Hex[HASH_HEX_SIZE])
{
    char binaryHash[BINARY_SIZE] = "";
    hexToBinary(Hex, binaryHash);
    printf("bin : %s\n", binaryHash);

    // Creation de la chaine de caractère "0"*difficulty
    char *prefix = malloc(DIFFICULTY + 1);
    memset(prefix, '0', DIFFICULTY);
    prefix[DIFFICULTY] = '\0';
    
    char *checker = NULL;
    checker = strstr(binaryHash, prefix);

    return checker == binaryHash;
}


void hexToBinary(char input[HASH_HEX_SIZE], char output[BINARY_SIZE])
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

void hash256(unsigned char *output, const char *input)
{

    size_t length = strlen(input);
    unsigned char md[HASH_SIZE];
    SHA256((const unsigned char*)input, length, md);
    memcpy(output,md, HASH_SIZE);

    return;
}

bool IsValidBlock(struct bloc* newBlock, struct bloc* previousBlock)
{
    printf("%d %d\n", previousBlock->index,newBlock->index);
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
    char hash_test[HASH_SIZE];
    char hash_hex_test[HASH_HEX_SIZE];
    
    hash256(hash_test, toString(newBlock));
    Hex_Hash(hash_test,hash_hex_test);
    printf("len du test : %d: %s\n", strlen(hash_hex_test),hash_hex_test);
    
    printf("len de new_hash : %d: %s\n", strlen(newBlock->Hash), newBlock->Hash);
    printf("\n");
    int res = strcmp(hash_hex_test, newBlock->Hash);
    printf("res : %d\n",res);
    if(res != 0)
    {
        printf("%d\n", 3);
        return false;
    }
    printf("pute\n");
    return true;
}

void calculHash(struct bloc* Bloc)
{
    
    Bloc->nonce = 0;
    char hash_hex[HASH_HEX_SIZE];
    char hash[HASH_SIZE];
    //hashPrinter(hash_test,HASH_SIZE);
    hash256(hash, toString(Bloc)); // mise à jour du hash
    printf("Hash normal : ");
    hashPrinter(hash,HASH_SIZE);
    
    Hex_Hash(hash, hash_hex);
    strcpy(Bloc->Hash, hash_hex);
    printf("Hex : %s\n",hash_hex);
    //hashPrinter(hash_test,HASH_SIZE);
    while(!HashMatchesDifficulty(hash_hex))
    {
        printf("yo\n");
        Bloc->nonce++;
        
        hash256(hash, toString(Bloc));  // mise à jour du hash
        Hex_Hash(hash, hash_hex);       //Conversion du hash en hex
        strcpy(Bloc->Hash, hash_hex);
        printf("enorme putin : %s\n",Bloc->Hash);
        printf("nouveau Hex : %s\n",hash_hex);
        
    }
}

char *Hex_Hash(char *input, char *output)
{

    char bloc_string[100];
    strcpy(bloc_string, input);

    unsigned char hash_value[HASH_SIZE];
    hash256(hash_value, bloc_string);
    
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
