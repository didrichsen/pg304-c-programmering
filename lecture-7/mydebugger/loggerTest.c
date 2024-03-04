#include "../include/sdlogger.h"

int main(void){
/*
    sdlogger(1, __LINE__,__FILE__,"Linje 1");
    sdlogger(2,__LINE__,__FILE__,"Linje 2");
    sdlogger(3, __LINE__,__FILE__,"Linje 3");
*/

    sddebug("Test");
    sderror("3rror");

    return 0;
}