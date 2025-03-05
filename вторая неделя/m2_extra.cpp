#include <stdio.h>
#include <cstring>
#include <iostream>
#include "stack.hpp"
using namespace std;

int is_operator(char ch);
int compare_operators(char op1, char op2);
int str_to_postfix(const char *infix, char **postfix);
double calculate_postfix(char **postfix);

#define CALCULATE(a, b, op) \
    ((op) == '+' ? (a) + (b) : ((op) == '-' ? (a) - (b) : ((op) == '*' ? (a) * (b) : ((op) == '/' ? ((b) != 0 ? (a) / (b) : 0) : ((op) == '%' ? ((b) != 0 ? (int)(a) % (int)(b) : 0) : 0)))))

int main()
{
    char infix[100] = {};
    fgets(infix, 100, stdin);
    char **postfix = new char *[60];
    for (int index = 0; index < 60; index++)
        postfix[index] = new char[15];
    str_to_postfix(infix, postfix);
    cout << postfix;
    cout << calculate_postfix(postfix) << endl;
}

double calculate_postfix(char **postfix)
{
    mStack<double> operation_stack;
    int postfix_eval_index = 0;
    while (postfix[postfix_eval_index][0] != '\0')
    {
        if (is_operator(postfix[postfix_eval_index][0]) && strlen(postfix[postfix_eval_index]) == 1)
        {
            double x = operation_stack.top();
            operation_stack.pop();
            double y = operation_stack.top();
            operation_stack.pop();
            y = CALCULATE(y, x, postfix[postfix_eval_index][0]);
            operation_stack.push(y);
            postfix_eval_index++;
        }
        else
        {
            char *lol = NULL;
            double num = strtod(postfix[postfix_eval_index], &lol);
            operation_stack.push(num);
            postfix_eval_index++;
        }
    }
    return operation_stack.top();
}

int str_to_postfix(const char *infix, char **postfix)
{
    mStack<char> s_postfix;
    int postfix_index = 0;

    char *operation_infix = (char *)calloc(strlen(infix) + 100, sizeof(char));
    strcat(operation_infix, infix);

    s_postfix.push('(');
    operation_infix[strlen(operation_infix)] = ')';

    int infix_index = 0;
    while (!s_postfix.isEmpty())
    {
        if (operation_infix[infix_index] == '(')
        {
            s_postfix.push('(');
            infix_index++;
            continue;
        }
        if (isdigit(operation_infix[infix_index]) || operation_infix[infix_index] == '-')
        {
            if (operation_infix[infix_index] == '-' && infix_index != 0 && isdigit(operation_infix[infix_index - 1]))
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
            while (is_operator(s_postfix.top()))
            {
                int comparison_result = compare_operators(operation_infix[infix_index], s_postfix.top());
                if (comparison_result == 0 || comparison_result == -1)
                {
                    postfix[postfix_index][0] = s_postfix.top();
                    postfix_index++;
                    s_postfix.pop();
                }
                else
                    break;
            }
            s_postfix.push(operation_infix[infix_index]);
            infix_index++;
            continue;
        }
        if (operation_infix[infix_index] == ')')
        {
            while (is_operator(s_postfix.top()))
            {
                postfix[postfix_index][0] = s_postfix.top();
                postfix_index++;
                s_postfix.pop();
            }
            s_postfix.pop();
            infix_index++;
        }
        infix_index++;
    }
    return 1;
}

int is_operator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%';
}

int compare_operators(char op1, char op2)
{
    int op1_int = 0;
    int op2_int = 0;
    if (op1 == '+' || op1 == '-')
        op1_int = 1;
    if (op1 == '*' || op1 == '/' || op1 == '%')
        op1_int = 2;
    if (op1 == '^')
        op1_int = 3;
    if (op2 == '+' || op2 == '-')
        op2_int = 1;
    if (op2 == '*' || op2 == '/' || op2 == '%')
        op2_int = 2;
    if (op2 == '^')
        op2_int = 3;
    return op1_int > op2_int ? 1 : (op1_int == op2_int ? 0 : -1);
}