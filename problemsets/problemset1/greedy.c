#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{   
    float h;
    do {
        printf("O hai! How much change is owed?\n");
        h = GetFloat();
       }
       while (h < 0);
    int cents = (int)(round(h * 100));
    int coins = 0;
    coins += cents / 25;
    cents %= 25;
    coins += cents / 10;
    cents %= 10;
    coins += cents / 5;
    cents %= 5;
    coins += cents;
    printf("%d\n", coins);
}
