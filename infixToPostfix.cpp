#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Stack
{
	int top;
	unsigned capacity;
	int* array;
};
struct Stack* createStack( unsigned capacity )
{
	struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));

	if (!stack) 
		return NULL;
	stack->top = -1;
	stack->capacity = capacity;

	stack->array = (int*) malloc(stack->capacity * sizeof(int));

	if (!stack->array)
		return NULL;
	return stack;
}
int isEmpty(struct Stack* stack)
{
	return stack->top == -1 ;
}
char peek(struct Stack* stack)
{
	return stack->array[stack->top];
}
char pop(struct Stack* stack)
{
	if (!isEmpty(stack))
		return stack->array[stack->top--] ;
	return '$';
}
void push(struct Stack* stack, char op)
{
	stack->array[++stack->top] = op;
}

int isOperand(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'||ch>='0'&&ch<='9'||ch=='.');
}
int Prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}


int infixToPostfix(char* exp)
{
	int i, k;
	struct Stack* stack = createStack(strlen(exp));
	if(!stack) 
		return -1 ;

	for (i = 0, k = -1; exp[i]; ++i)
	{
		
		if (isOperand(exp[i]))
			exp[++k] = exp[i];
		
		
		else if (exp[i] == '(')
			push(stack, exp[i]);
		
		
		else if (exp[i] == ')')
		{
			while (!isEmpty(stack) && peek(stack) != '(')
				exp[++k] = pop(stack);
			if (!isEmpty(stack) && peek(stack) != '(')
				return -1; 		 
			else
				pop(stack);
		}
		else
		{
			while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
				exp[++k] = pop(stack);
			push(stack, exp[i]);
		}

	}

	
	while (!isEmpty(stack))
		exp[++k] = pop(stack );

	exp[++k] = '\0';
	printf( "%s", exp );
}

int main()
{
	// char infix[] = "3+b*(5^d-e)^(10+g*h)-1.4";
    char infix[100];
    printf("Enter the infix to convert to postfix: ");
    fgets(infix, 100, stdin);
    printf("intfix : %s ",infix);
    printf("Postfix : ");
	infixToPostfix(infix);
    getchar();
    // printf("\n");
	return 0;
}
