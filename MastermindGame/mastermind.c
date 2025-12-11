
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char secret[101], guess[101];
    int len;

    printf("Enter secret (max 100 chars): ");
    if (scanf("%100s", secret) != 1) return 0;
    len = (int)strlen(secret);

    
    for (int i = 0; i < len; ++i) {
        if (!isdigit((unsigned char)secret[i])) {
            fprintf(stderr, "Secret should contain digits only.\n");
            return 1;
        }
    }

    while (1) {
        printf("\nEnter guess (must be %d chars): ", len);
        if (scanf("%100s", guess) != 1) break;

        if ((int)strlen(guess) != len) {
            printf("Guess length mismatch. Try again.\n");
            continue;
        }

        if (strcmp(secret, guess) == 0) {
            printf("Correct guess! Game over.\n");
            break;
        }

        // use VLA sized by len
        int usedSecret[len];
        int usedGuess[len];
        for (int i = 0; i < len; ++i) { usedSecret[i] = usedGuess[i] = 0; }

        // exact matches
        for (int i = 0; i < len; ++i) {
            if (secret[i] == guess[i]) {
                printf("Number %c is matched in correct position (%d)\n", secret[i], i + 1);
                usedSecret[i] = usedGuess[i] = 1;
            }
        }

        // correct digit but wrong position
        for (int i = 0; i < len; ++i) {
            if (usedGuess[i]) continue;
            for (int j = 0; j < len; ++j) {
                if (!usedSecret[j] && guess[i] == secret[j]) {
                    printf("Number %c is matched but the position should be altered\n", guess[i]);
                    usedSecret[j] = usedGuess[i] = 1;
                    break;
                }
            }
        }
    }

    return 0;
}
