//
// Created by simen on 3/4/2024.
//

#include "include/exercise-3-extend-buffer.h"

int countDigits(long number){

    int count = 0;
    int n = number;

    while (n != 0){
        n = n / 10;
        count++;
    }

    return count;

}