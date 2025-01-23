#include <stdio.h>

int main() {
    FILE *fp;
    int Fa[10][10], states[3][10], row = 0, col = 0, sr = 0, sc = 0, flag = 0, i, j, in, curr;
    char str[100], k;

    fp = fopen("Dfa_ip.txt", "r");
    if (fp == NULL) {
        printf("File could not be found\n");
        return 1;
    }

    // Initialize states array
    for (i = 0; i < 3; i++)
        for (j = 0; j < 10; j++)
            states[i][j] = -1;

    while (fscanf(fp, "%d", &in) != EOF) {
        k = fgetc(fp);  // Read next character

        if (flag) {
            states[sr][sc++] = in;
            if (k == '\n') {
                sr++;
                sc = 0;
            }
        } else if (k == '#') {
            flag = 1;
            Fa[row][col++] = in;
        } else if (!flag) {
            Fa[row][col++] = in;
            if (k == '\n') {
                row++;
                col = 0;
            }
        }
    }
    fclose(fp);

    printf("THE AUTOMATA IS :\n\n");
    for (i = 0; i <= row; i++) {
        for (j = 0; j < col; j++) {
            printf("%2d ", Fa[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter the string: ");
    scanf("%s", str);

    curr = states[0][0];
    i = 0;
    while (str[i] != '\0') {
        curr = Fa[curr][str[i] - 'a']; // Assuming input is lowercase letters
        if (curr == -1)
            break;
        i++;
    }

    flag = 0;
    if (curr != -1) {
        for (i = 0; i <= sc && !flag; i++) {
            if (curr == states[1][i]) {
                printf("\nSTRING ACCEPTED\n");
                flag = 1;
            }
        }
    }

    if (!flag)
        printf("\nSTRING NOT ACCEPTED\n");

    return 0;
}
