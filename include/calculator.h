#pragma once
#include <string>

class Calculator
{
    public:
        Calculator();  
        
        int Add(int a, int b);
        int Sub(int a, int b);
        int Mul(int a, int b);
        double Div(double a, double b);        
};