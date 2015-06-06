#pragma once

class CalculatorExplicit
{
    public:
        CalculatorExplicit();
        virtual ~CalculatorExplicit();

        virtual double calculateUpValue() = 0;
        virtual double calculateMiddleValue() = 0;
        virtual double calculateDownValue() = 0;
        
    private:
            
};

