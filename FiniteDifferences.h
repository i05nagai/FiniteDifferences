#pragma once

#include "FiniteDifferenceScheme.h"
#include "StepCondition.h"

class FiniteDifferences
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    FiniteDifference(
        const boost::numeric::ublas::vector<double>& stocks);
    virtual ~FiniteDifference();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    void doScheme(
        const boost::shared_ptr<const FiniteDifferenceScheme> scheme,
        const boost::shared_ptr<const StepCondition> stepCondition);

private:
    const boost::numeric::ublas::vector<double> _stocks;
            
};


