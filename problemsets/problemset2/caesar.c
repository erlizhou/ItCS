#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Please input a single command line argument.\n");
        return 1;
    }
    else {
        int k = atoi(argv[1]);
        if (k < 0) {
            printf("Integer must not be non-negative.\n");
            return 1;
        }
        string s = GetString();
        for (int i = 0; i < strlen(s); i++) {
            if islower((s[i])) {
                int value = (int)(s[i]) - 97;
                int c = (value + k) % 26;
                char output = (char)(97 + c);
                printf("%c", output);
            }
            else if isupper((s[i])) {
                int value = (int)(s[i]) - 65;
                int c = (value + k) % 26;
                char output = (char)(65 + c);
                printf("%c", output);
            }
            else
                printf("%c", s[i]);
        }
        printf("\n");
    }
}
