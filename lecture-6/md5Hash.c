#include "md5.h"
#include <stdio.h>
#include <string.h>

void print_hash(char hash[])
{
    int idx;
    for (idx=0; idx < 16; idx++)
        printf("%02x",hash[idx]);
    printf("\n");
}

void main(void){

    char hash[16];

    char *szToHash = "Dette er en string som skal hashes.";
    MD5_CTX ctx;

    md5_init(&ctx);
    md5_update(&ctx,szToHash,strlen(szToHash));
    md5_final(&ctx,hash);
    print_hash(hash);

}