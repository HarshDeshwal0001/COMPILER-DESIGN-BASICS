#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of keywords
char keywords[][10] = {
    "int", "float", "if", "else", "while", "for", "return", "void"
};

// Function to check if a word is a keyword
int isKeyword(char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
            ch == '<' || ch == '>' || ch == '%');
}

int main() {
    FILE *file;
    char ch, word[50];
    int i;

    file = fopen("input.c", "r"); // Input file to scan
    if (file == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    printf("Lexical Analysis Output:\n");

    while ((ch = fgetc(file)) != EOF) {
        // Detect words (keywords or identifiers)
        if (isalpha(ch)) {
            i = 0;
            while (isalnum(ch)) {
                word[i++] = ch;
                ch = fgetc(file);
            }
            word[i] = '\0';
            fseek(file, -1, SEEK_CUR); // Step back one character

            if (isKeyword(word))
                printf("[Keyword]    %s\n", word);
            else
                printf("[Identifier] %s\n", word);
        }

        // Detect operators
        else if (isOperator(ch)) {
            printf("[Operator]   %c\n", ch);
        }
    }

    fclose(file);
    return 0;
}
