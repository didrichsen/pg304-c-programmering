#include <stdio.h>

int main(int argc,char* argv[]){

    int a,b;

    int *p,*q;

    p = &a;

    q = &b;

    printf("Type two integers seperated with space\n");

    scanf("%d %d", p, q);

    if(a > b){
        printf("%d\n", a);
    } else if (a < b){
        printf("%d\n", b);
    }

    return 0;

}