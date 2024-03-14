/*
 Implement a flag feature.
 */

#include <stdio.h>

#define FLAG_ONE 0b1
#define FLAG_TWO 0b10
#define FLAG_THREE 0b10000000


typedef unsigned char BYTE;

int main(int argc, char* argv[]){

    BYTE flags = FLAG_ONE | FLAG_TWO | FLAG_THREE; // 0000 0001

    // After or (|) operations on flag. Number will be:
    // 0000 0001
    // 0000 0010
    // 1000 0000

    // 1000 0011

    //Disable feature two
    flags = flags & ~ FLAG_TWO;
    //Enable again
    flags = flags | FLAG_TWO;

    printf("Value of flag: %d\n",flags);


    if((flags & FLAG_ONE) != 0){
        printf("Feature One Enabled.\n");
    }

    //Zero is not needed
    if((flags & FLAG_TWO)){
        printf("Feature Two Enabled.\n");
    }

    if((flags & FLAG_THREE)){
        printf("Feature Three Enabled.\n");
    }

}