#include <stdio.h>
#include <cs50.h>

int main(void) {
    printf("minutes: \n");
    int time = GetInt();
    int bottle = time * 12;
    printf("bottles: %d\n", bottle);
}
