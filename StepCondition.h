#pragma once

class StepCondition 
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    StepCondition();
    virtual ~StepCondition();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void applyAfterBackward(
        boost::numeric::ublas::vector<double>& previousStep) = 0;

private:
            
};

