#pragma once

#include "FiniteDifferenceScheme.h"

class ImplicitFiniteDifference 
    : public FiniteDifferenceScheme
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    ImplicitFiniteDifference();
    virtual ~ImplicitFiniteDifference();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void doBackward(
        boost::numeric::ublas::vector<double>& rightHandSide,
        boost::numeric::ublas::vector<double>& result);

private:
            
};

