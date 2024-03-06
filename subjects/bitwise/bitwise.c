//
// Created by simen on 3/6/2024.
//

#include <stdio.h>

int main() {
    unsigned char a = 12; // binary: 00001100
    unsigned char b = 25; // binary: 00011001

    unsigned char result;

    // Bitwise AND
    result = a & b; // binary: 00001000, decimal: 8
    printf("a & b = %u\n", result);

    // Bitwise OR
    result = a | b; // binary: 00011101, decimal: 29
    printf("a | b = %u\n", result);

    // Bitwise XOR
    result = a ^ b; // binary: 00010101, decimal: 21
    printf("a ^ b = %u\n", result);

    // Bitwise NOT
    result = ~a; // binary: 11110011, decimal: 243 (for an unsigned char)
    printf("~a = %u\n", result);

    // Left Shift
    result = a << 2; // binary: 00110000, decimal: 48
    printf("a << 2 = %u\n", result);

    // Right Shift
    result = a >> 2; // binary: 00000011, decimal: 3
    printf("a >> 2 = %u\n", result);

    return 0;
}
