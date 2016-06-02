#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string s = GetString();
    for (int i = 0; i < strlen(s); i++) {
        if (i == 0 || isspace(s[i - 1]))
            printf("%c", (char)(toupper(s[i])));
    }
    printf("\n");
}
