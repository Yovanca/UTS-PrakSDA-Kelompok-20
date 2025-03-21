#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// fungsi untuk membersihkan terminal
void clear() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void end() {
    printf("Press Enter to return...");
    getchar();
    clear();
}

// Stack 
typedef struct {
    char arr[MAX][MAX]; // Array untuk menyimpan ekspresi
    int top;
} Stack;

// Initialize stack
void initStack(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, const char* item) { if (s->top < MAX - 1) strcpy(s->arr[++(s->top)], item); }
char* pop(Stack* s) { return isEmpty(s) ? "" : s->arr[(s->top)--]; }

// Operator precedence
int precedence(char op) {
    return (op == '^') ? 3 : (op == '*' || op == '/') ? 2 : (op == '+' || op == '-') ? 1 : -1;
}

// Reverse string
void reverseStr(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Remove spaces from a string
void removeSpaces(char* str) {
    int i, j = 0;
    for (i = 0; str[i]; i++) {
        if (str[i] != ' ') str[j++] = str[i];
    }
    str[j] = '\0';
}

// Infix to Postfix
void infixToPostfix() {
    char exp[MAX], result[MAX] = "";
    Stack stack; initStack(&stack);
    printf("Masukkan ekspresi infix : ");
    fgets(exp, MAX, stdin);
    exp[strcspn(exp, "\n")] = 0;
    removeSpaces(exp);

    for (int i = 0, j = 0; exp[i]; i++) {
        if (isalnum(exp[i])) result[j++] = exp[i];
        else if (exp[i] == '(') push(&stack, "(");
        else if (exp[i] == ')') {
            while (!isEmpty(&stack) && stack.arr[stack.top][0] != '(') result[j++] = pop(&stack)[0];
            pop(&stack);
        } else {
            while (!isEmpty(&stack) && precedence(exp[i]) <= precedence(stack.arr[stack.top][0])) result[j++] = pop(&stack)[0];
            char op[2] = {exp[i], '\0'}; push(&stack, op);
        }
    }
    while (!isEmpty(&stack)) result[strlen(result)] = pop(&stack)[0];
    printf("Ekspresi Postfix : %s\n", result);
    end();
}

// Postfix to Infix
void postfixToInfix() {
    char exp[MAX];
    Stack stack; initStack(&stack);
    printf("Masukkan ekspresi postfix : ");
    fgets(exp, MAX, stdin);
    exp[strcspn(exp, "\n")] = 0;
    removeSpaces(exp);

    for (int i = 0; exp[i]; i++) {
        if (isalnum(exp[i])) { char str[2] = {exp[i], '\0'}; push(&stack, str); }
        else {
            char op1[MAX], op2[MAX], res[MAX];
            strcpy(op1, pop(&stack)); strcpy(op2, pop(&stack));
            snprintf(res, MAX, "(%s%c%s)", op2, exp[i], op1);
            push(&stack, res);
        }
    }
    printf("Ekspresi Infix : %s\n", pop(&stack));
    end();
}

// Infix to Prefix
void infixToPrefix() {
    char exp[MAX], result[MAX] = "";
    Stack stack; 
    initStack(&stack);

    printf("Masukkan ekspresi infix : ");
    fgets(exp, MAX, stdin);
    exp[strcspn(exp, "\n")] = 0;
    removeSpaces(exp);

    reverseStr(exp);

    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }

    char postfix[MAX] = "";
    int j = 0;
    for (int i = 0; exp[i]; i++) {
        if (isalnum(exp[i])) {
            postfix[j++] = exp[i];  
        } 
        else if (exp[i] == '(') {
            push(&stack, "(");
        } 
        else if (exp[i] == ')') {
            while (!isEmpty(&stack) && stack.arr[stack.top][0] != '(') {
                postfix[j++] = pop(&stack)[0];
            }
            pop(&stack); 
        } 
        else {
            while (!isEmpty(&stack) && precedence(exp[i]) <= precedence(stack.arr[stack.top][0])) {
                postfix[j++] = pop(&stack)[0];
            }
            char op[2] = {exp[i], '\0'};
            push(&stack, op);
        }
    }
    
    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack)[0];
    }
    postfix[j] = '\0';

    reverseStr(postfix);
    
    printf("Ekspresi Prefix : %s\n", postfix);
    end();
}


// Prefix to Infix
void prefixToInfix() {
    char exp[MAX];
    Stack stack; initStack(&stack);
    printf("Masukkan ekspresi prefix : ");
    fgets(exp, MAX, stdin);
    exp[strcspn(exp, "\n")] = 0;
    removeSpaces(exp);
    int len = strlen(exp);

    for (int i = len - 1; i >= 0; i--) {
        if (isalnum(exp[i])) { char str[2] = {exp[i], '\0'}; push(&stack, str); }
        else {
            char op1[MAX], op2[MAX], res[MAX];
            strcpy(op1, pop(&stack)); strcpy(op2, pop(&stack));
            snprintf(res, MAX, "(%s%c%s)", op1, exp[i], op2);
            push(&stack, res);
        }
    }
    printf("Ekspresi Infix : %s\n", pop(&stack));
    end();
}
