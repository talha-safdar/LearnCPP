#include "../include/calculator.h"
#include <iostream>

Calculator::Calculator() = default; // same as empty body {}

int Calculator::Add(int a, int b)
{
    return a + b;
}

int Calculator::Sub(int a , int b)
{
    return a - b;
}

int Calculator::Mul(int a , int b)
{
    return a * b;
}

double Calculator::Div(double a, double b)
{
    if (b == 0)
    {
        return 0;
    }
    return a / b;
}