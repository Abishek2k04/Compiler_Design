#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
typedef struct {
    int top;
    char items[MAX];
} Stack;
void initStack(Stack *s) {
    s->top = -1;
}
int isEmpty(Stack *s) {
    return s->top == -1;
}
void push(Stack *s, char c) {
    s->items[++(s->top)] = c;
}
char pop(Stack *s) {
    return isEmpty(s) ? 0 : s->items[(s->top)--];
}
int precedence(char c) {
    return (c == '+' || c == '-') ? 1 : (c == '*' || c == '/') ? 2 : (c == '^') ? 3 : 0;
}
int isOperator(char c) {
    return strchr("+-*/^", c) != NULL;
}
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int i, j = 0;
    char token, temp;
    for (i = 0; infix[i] != '\0'; i++) {
        token = infix[i];
        if (isspace(token)) continue;
        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(&s, token);
        } else if (token == ')') {
            while (!isEmpty(&s) && (temp = pop(&s)) != '(') {
                postfix[j++] = temp;
            }
        } else if (isOperator(token)) {
            while (!isEmpty(&s) && precedence(s.items[s.top]) >= precedence(token)) {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}
int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter the expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = 0;
    infixToPostfix(infix, postfix);
    printf("\nPostfix Expression: %s\n", postfix);
    return 0;
}
