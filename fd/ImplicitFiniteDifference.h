#pragma once

#include "BoundaryCondition.h"
#include "FiniteDifferenceScheme.h"
#include <memory>

class ImplicitFiniteDifference 
    : public FiniteDifferenceScheme
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    ImplicitFiniteDifference(
        const double upperValue,
        const double middleValue,
        const double lowerValue,
        const std::size_t dimension,
        const std::shared_ptr<const BoundaryCondition>& boundaryCondition);
    virtual ~ImplicitFiniteDifference();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void doBackward(
        boost::numeric::ublas::vector<double>& rightHandSide,
        boost::numeric::ublas::vector<double>& results) const;

private:
    const std::shared_ptr<const BoundaryCondition> _boundaryCondition;
    const TridiagonalOperator _tridiagonalOperator;
            
};

