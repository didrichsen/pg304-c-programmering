#include <stdio.h>

// Define an enum named Color
enum Color {
    RED,
    BLUE,
    YELLOW,
    INDIGO = 10
};

int main(void) {
    enum Color myColor = RED;
    enum Color myColorTwo = BLUE;
    enum Color myColorThree = YELLOW;
    enum Color myColorFour = INDIGO;

    // Printing the values of myColor and myColorTwo
    printf("|Red: %d| |Blue: %d| Yellow: %d| Indigo: %d|\n", myColor, myColorTwo, myColorThree, myColorFour);

    return 0;
}