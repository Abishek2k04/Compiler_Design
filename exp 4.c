#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
const char *keywords[] = {"int", "float", "if", "else", "return", "while", "for", "char", "double", "void", "main"};
const char delimiters[] = "(){};";
const char operators[] = "+-*/<>=!&|";

int isKeyword(char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
        if (strcmp(word, keywords[i]) == 0) return 1;
    return 0;
}
int isOperator(char ch) { return (strchr(operators, ch) != NULL); }
int isDelimiter(char ch) { return (strchr(delimiters, ch) != NULL); }
int isNumber(char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]) && str[i] != '.') return 0;
    return 1;
}

int main() {
    char input[MAX_LEN], word[MAX_LEN];
    printf("Enter the string: ");
    fgets(input, MAX_LEN, stdin);

    int i = 0, j = 0;
    char delimitersFound[MAX_LEN] = "", operatorsFound[MAX_LEN] = "", identifiers[MAX_LEN][MAX_LEN], keywordsFound[MAX_LEN][MAX_LEN], literals[MAX_LEN][MAX_LEN], constants[MAX_LEN][MAX_LEN];
    int idCount = 0, kwCount = 0, litCount = 0, constCount = 0;

    while (input[i] != '\0') {
        char ch = input[i];
        if (ch == '\"') {
            j = 0;
            i++;
            while (input[i] != '\"' && input[i] != '\0') word[j++] = input[i++];
            word[j] = '\0';
            if (input[i] == '\"') i++;
            strcpy(literals[litCount++], word);
        } else if (isOperator(ch)) {
            strncat(operatorsFound, &ch, 1);
            strcat(operatorsFound, " ");
        } else if (isDelimiter(ch)) {
            strncat(delimitersFound, &ch, 1);
            strcat(delimitersFound, " ");
        } else if (isalnum(ch) || ch == '.') {
            j = 0;
            while (isalnum(input[i]) || input[i] == '.') word[j++] = input[i++];
            word[j] = '\0';
            i--;
            if (isKeyword(word)) strcpy(keywordsFound[kwCount++], word);
            else if (isNumber(word)) strcpy(constants[constCount++], word);
            else strcpy(identifiers[idCount++], word);
        }
        i++;
    }

    printf("\nDelimiters: %s\n", delimitersFound);
    printf("Operators: %s\n", operatorsFound);
    printf("Identifiers: ");
    for (int k = 0; k < idCount; k++) printf("%s ", identifiers[k]);
    printf("\nKeywords: ");
    for (int k = 0; k < kwCount; k++) printf("%s ", keywordsFound[k]);
    printf("\nConstants: ");
    for (int k = 0; k < constCount; k++) printf("%s ", constants[k]);
    printf("\nLiterals: ");
    for (int k = 0; k < litCount; k++) printf("\"%s\" ", literals[k]);

    return 0;
}
