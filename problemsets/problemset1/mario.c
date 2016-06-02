#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do {
        printf("Height of pyramid: ");
        h = GetInt();
       }
       while (h > 23 || h < 0);
       
    for (int i = 0; i < h; i++) {
        for (int j = h - i - 1; j > 0; j--)
            printf(" ");
        for (int k = 0; k < i + 2; k++)
            printf("#");
        printf("\n");
    }
}
