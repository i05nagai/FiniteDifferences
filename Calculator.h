#pragma once

class Calculator 
{
    public:
        Calculator();
        virtual ~Calculator();

        virtual double calculateUpValue() = 0;
        virtual double calculateMiddleValue() = 0;
        virtual double calculateDownValue() = 0;
        
    private:
            
};

Calculator::Calculator() 
{
    
}
Calculator::~Calculator() 
{
}
