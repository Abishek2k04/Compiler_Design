#include <stdio.h>
#include <ctype.h>
#include <string.h>

void checkKeyword(char str[]) {
    if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") || !strcmp(str, "for") || !strcmp(str, "int") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str, "char")) {
	printf("A keyword : %s\n", str);
    } else {
	printf("An identifier : %s\n", str);
    }
}

int main() {
    char ch, str[25], operators[] = "+-*/%=";
    FILE *fp;
    int i, j = 0;

    fp = fopen("source1.txt", "r");

    if (fp == NULL) {
	printf("Error while opening the file\n");
	return 0;
    }

    while ((ch = fgetc(fp)) != EOF) {
	for (i = 0; i < 6; ++i) {
	    if (ch == operators[i]) {
		printf("An operator : %c\n", ch);
            }
        }

        if (isalnum(ch)) {
            str[j++] = ch;
        } else if ((ch == ' ' || ch == '\n' || ch == ';' || ch == ',') && (j != 0)) {
            str[j] = '\0';
            j = 0;
            checkKeyword(str);
        }
    }

    fclose(fp);
    return 0;
}
