#pragma once

#include "StepCondition.h"

class StepConditionAmerican 
    : public StepCondition
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    StepConditionAmerican(
        const boost::numeric::ublas::vector<double>& stocks,
        const boost::shared_ptr<const PayOff>& payOff);
    virtual ~StepConditionAmerican();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void applyAfterBackward(
        boost::numeric::ublas::vector<double>& previousStep);
private:
};

