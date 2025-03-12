#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
int is_operator(char ch);
int compare_operators(char op1, char op2);
int str_to_postfix(const char *infix, char **postfix);
double calculate_postfix( char **postfix);
#define CALCULATE(a, b, op) \
    ((op) == '+' ? (a) + (b) : ((op) == '-' ? (a) - (b) : ((op) == '*' ? (a) * (b) : ((op) == '/' ? ((b) != 0 ? (a) / (b) : 0) : ((op) == '%' ? ((b) != 0 ? (int)(a) % (int)(b) : 0) : 0)))))

int main()
{
    char infix[100] = {};
    fgets(infix, 100, stdin);
    char **postfix = new char *[60];
    for (int index = 0; index < 60;index++)
        postfix[index] = new char[15];
    str_to_postfix(infix, postfix);
    cout<< calculate_postfix(postfix)<<endl;

}
double calculate_postfix( char ** postfix){
double operation_stack[100] = {};
    int operation_stack_index = 5;
    int postfix_eval_index = 0;
    while(postfix[postfix_eval_index][0]!='\0'){
        if(is_operator(postfix[postfix_eval_index][0])&&strlen(postfix[postfix_eval_index]) == 1){
             double x = operation_stack[operation_stack_index - 1];
                operation_stack[operation_stack_index - 1] = 0;
                double y = operation_stack[operation_stack_index - 2];
                operation_stack[operation_stack_index - 2] = 0;
                operation_stack_index -= 2;
                y = CALCULATE(y, x, postfix[postfix_eval_index][0]);
                operation_stack[operation_stack_index] = y;
                operation_stack_index++;
                postfix_eval_index++;

        }else{
            char *lol = NULL;
            operation_stack[operation_stack_index] = strtod(postfix[postfix_eval_index], &lol);
            operation_stack_index++;
            postfix_eval_index++;
        }
    }
    return operation_stack[operation_stack_index - 1];
}
int str_to_postfix(const char * infix, char** postfix){
    char stack[1000] = {};
    int postfix_index = 0;
  
    char *operation_infix = (char *)calloc(strlen(infix) + 100, sizeof(char));
    strcat(operation_infix, infix);

    stack[0] = '(';
    int stack_index = 0;
    operation_infix[strlen(operation_infix)] = ')';

    int infix_index = 0;
    while (stack_index!=-1)
    {
        if(operation_infix[infix_index] == '('){
            stack[stack_index + 1] = '(';
            stack_index++;
            infix_index++;
            continue;
        }
        if(isdigit(operation_infix[infix_index])|| operation_infix[infix_index] == '-'){
            if (operation_infix[infix_index] == '-' && infix_index != 0&& isdigit(operation_infix[infix_index-1]))
                ;
            else
            {
                char *ptr = NULL;
                double current_num = strtod(operation_infix + infix_index, &ptr);
                snprintf(postfix[postfix_index], 15, "%f", current_num);
                postfix_index++;
                infix_index = ptr - operation_infix;
                continue;
              }
        }

        if (is_operator(operation_infix[infix_index]))

        {
            while (is_operator(stack[stack_index]))
            {
                int comparison_result = compare_operators(operation_infix[infix_index], stack[stack_index]);
                if (comparison_result == 0 || comparison_result == -1)
                {
                    postfix[postfix_index][0] = stack[stack_index];
                    postfix_index++;
                    stack[stack_index] = 0;
                    stack_index--;
                }
                else
                    break;
            }
            stack[stack_index + 1] = operation_infix[infix_index];
            stack_index++;
            infix_index++;
            continue;
        }
        if(operation_infix[infix_index] == ')'){
            while (stack_index >= 0 && is_operator(stack[stack_index]))
            {
                postfix[postfix_index][0] = stack[stack_index];
                postfix_index++;
                stack[stack_index] = 0;
                stack_index--;
            }

                stack[stack_index] = 0;
                        stack_index--; 

            infix_index++;

        }
        infix_index++;
    }
    return 1;
}

int is_operator(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/'||ch =='^' || ch == '%';
}

int compare_operators(char op1, char op2){
    int op1_int = 0;
     int op2_int = 0;
    if(op1=='+'|| op1=='-')
        op1_int = 1;
    if(op1=='*'|| op1=='/'|| op1 == '%')
        op1_int = 2;
    if(op1 == '^')
        op1_int = 3;
    if (op2 == '+' || op2 == '-')
        op1_int = 1;
    if(op2=='*'|| op2=='/'|| op2 == '%')
        op2_int = 2;
    if(op2 == '^')
        op2_int = 3;
    return op1_int > op2_int ? 1 : (op1_int == op2_int ? 0
                                                      : -1);
}