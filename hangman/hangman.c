
//C project to make a simple hangman game


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void displayHangman(int triesleft) {
    printf(" -----|\n");
    printf(" |    %s\n", triesleft < 6 ? "O" : " ");
    printf(" |   %s%s%s\n", triesleft < 4 ? "/" : " ", triesleft < 5 ? "|" : " ", triesleft < 3 ? "\\" : " ");
    printf(" |   %s %s\n", triesleft < 2 ? "/" : " ", triesleft < 1 ? "\\" : " ");
    printf("_|_\n\n");
}

void displayDeadHangman() {
    printf(" -----|\n");
    printf(" |    X\n");
    printf(" |   /|\\\n");
    printf(" |   / \\\n");
    printf("_|_\n\n");
}

void reset(char* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = 0;
    }
}

int main() {
    char word[10];
    char guessed[10];
    int length, n, i;
    char guess, confirm;
    char letters[26];

    printf("Welcome to Hangman!\n");
    
    do {
        printf("Enter a word: ");
        scanf("%s", word);
        system("cls");
        
        length = strlen(word);
        for (i = 0; i < length; i++) {
            guessed[i] = '_';
        }

        guessed[length] = '\0';
        n = 6;

        reset(letters, sizeof(letters));

        printf("\nLet's play Hangman!\n");

        while (n > 0 && strcmp(word, guessed) != 0) {
            printf("\nWord: %s\n", guessed);
            printf("Tries left: %d\n", n);
            printf("Guessed letters: ");
            for (i = 0; i < 26; i++) {
                if (letters[i] != 0) {
                    printf("%c ", letters[i]);
                }
            }
            printf("\n");

            printf("Enter a lowercase letter: ");
            scanf(" %c", &guess);

            if (guess < 'a' || guess > 'z') {
                printf("Invalid input! Please enter a lowercase letter.\n");
                continue;
            }

            if (letters[guess - 'a'] != 0) {
                printf("You have already guessed the letter %c. Please try a different letter.\n", guess);
                continue;
            }

            letters[guess - 'a'] = guess;

            int found = 0;
            for (i = 0; i < length; i++) {
                if (word[i] == guess) {
                    guessed[i] = guess;
                    found = 1;
                }
            }

            if (!found) {
                n--;
                printf("Incorrect guess!\n");
                displayHangman(n);
            }
        }

        printf("\n");

        if (strcmp(word, guessed) == 0) {
            printf("Congratulations! You guessed the word: %s\n", word);
        } else {
            printf("Sorry, you ran out of tries. The word was: %s\n", word);
            displayDeadHangman();
        }

        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &confirm);

        while (confirm != 'y' && confirm != 'n') {
            printf("Invalid input. Please enter 'y' to play again or 'n' to exit: ");
            scanf(" %c", &confirm);
        }

        printf("\n");

    } while (confirm == 'y');

    printf("Thank you for playing Hangman!\n");

    return 0;
}
