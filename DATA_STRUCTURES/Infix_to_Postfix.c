//To Convert Infix Expression to Postfix Expression

#include<stdio.h>
#include<string.h>

#define Max_Size 20

typedef struct{
    char arr[Max_Size];
    int top;
} stack;

void initialize(stack *st) {
    st->top = -1;
}

int precedence(char c){
    if(c == '^'){
        return 3;
    }
    else if(c == '*' || c == '/'){
        return 2;
    }
    else if(c == '+' || c == '-'){
        return 1;
    }
    else{
        return -1;
    }
}

int isfull(stack *st)
{
    return(st->top == Max_Size-1);
}

int isempty(stack *st)
{
    return (st->top == -1);
}

void push(stack *st, char value)
{
    if(isfull(st))
    {
        printf("Stack overflow! Cannot push %c\n", value);
        return;
    }
    st->top = st->top + 1;
    st->arr[st->top] = value;
}

char pop(stack *st)
{
    if(isempty(st))
    {
        printf("Stack underflow! Cannot pop.\n");
        return -1;
    }
    char topelement = st->arr[st->top];
    st->top = st->top - 1;
    return topelement;
}

char peek(stack *st) {
    if(isempty(st))
        return -1;
    return st->arr[st->top];
}

void Infix_to_Postfix(char infix[], int n, stack *st){
    char postfix[50];
    int k = 0;

    for(int i = 0; i < n; i++){
        char c = infix[i];
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
            postfix[k++] = c;
        }
        else if(c == '('){
            push(st, c);
        }
        else if(c == ')'){
            while(!isempty(st) && peek(st) != '('){
                postfix[k++] = pop(st);
            }
            if(!isempty(st)) pop(st); 
        }
        else{
            while(!isempty(st) && precedence(c) <= precedence(peek(st))){
                postfix[k++] = pop(st);
            }
            push(st, c);
        }
    }
    while(!isempty(st)){
        postfix[k++] = pop(st);
    }
    postfix[k] = '\0';
    printf("Postfix: %s\n", postfix);
}

int main()
{
    stack st;
    initialize(&st);

    char infix[50];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    int n = strlen(infix);
    Infix_to_Postfix(infix, n, &st);

    return 0;
}