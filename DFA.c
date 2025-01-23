#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    int Fa[10][10], states[3][10], row = 0, col = 0, sr = 0, sc = 0, flag = 0, i, j, in, curr;
    char k, str[100];

    // Open the file
    fp = fopen("Dfa_ip.txt", "r");
    if (fp == NULL) {
        printf("File could not be found\n");
        return 1;
    }

    // Initialize the states and transition table
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 10; j++) {
            states[i][j] = -1;
        }
    }
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            Fa[i][j] = -1;
        }
    }

    // Read the DFA transitions and states from the file
    while (fscanf(fp, "%d", &in) != EOF) {
        k = fgetc(fp); // Read the next character

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
    fclose(fp); // Close the file

    // Print the DFA transition table
    printf("THE AUTOMATA IS:\n\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%2d ", Fa[i][j]);
        }
        printf("\n");
    }

    // Print initial and final states
    printf("\nInitial State: %d\n", states[0][0]);
    printf("Final States: ");
    for (i = 0; i < sc; i++) {
        printf("%d ", states[1][i]);
    }
    printf("\n");

    // Input the string to test
    printf("\n\nEnter the string: ");
    scanf("%s", str);

    // Process the string through the DFA
    curr = states[0][0]; // Start from the initial state
    printf("\nProcessing string '%s':\n", str);
    i = 0;
    while (str[i] != '\0') {
        printf("At state %d, reading '%c'\n", curr, str[i]);
        if (curr < 0 || curr >= row) {
            curr = -1;
            break;
        }
        curr = Fa[curr][str[i] - 'a']; // Assuming input is lowercase letters
        if (curr == -1) {
            printf("Transition to invalid state\n");
            break; // Transition to an invalid state
        }
        i++;
    }

    // Check if the final state is an accepting state
    flag = 0;
    if (curr != -1) {
        for (i = 0; i < sc; i++) {
            if (curr == states[1][i]) {
                printf("\n\nSTRING ACCEPTED\n");
                flag = 1;
                break;
            }
        }
    }

    if (!flag) {
        printf("\n\nSTRING NOT ACCEPTED\n");
    }

    return 0;
}
