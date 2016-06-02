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
        string key = argv[1];
        for (int i = 0; i < strlen(key); i++) {
            if (!isalpha(key[i])) {
                printf("Key must not contain any non-alphabetical character.\n");
                return 1;
            }
        }
        string s = GetString();
        int j = 0;
        int length = strlen(key); 
        int keyvalue;
        for (int i = 0; i < strlen(s); i++) {
            if islower((key[j]))
                keyvalue = (int)(key[j]) - 97;
            else
                keyvalue = (int)(key[j]) - 65;
            if islower((s[i])) {
                int value = (int)(s[i]) - 97;
                int c = (value + keyvalue) % 26;
                char output = (char)(97 + c);
                printf("%c", output);
                j++;
                if (j == length)
                    j = 0;
            }
            else if isupper((s[i])) {
                int value = (int)(s[i]) - 65;
                int c = (value + keyvalue) % 26;
                char output = (char)(65 + c);
                printf("%c", output);
                j++;
                if (j == length)
                    j = 0;
            }
            else
                printf("%c", s[i]);
        }
        printf("\n");
    }
}
