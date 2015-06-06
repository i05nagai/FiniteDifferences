#include "ExplicitFiniteDifference.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
ExplicitFiniteDifference::ExplicitFiniteDifference(
    const double upperValue,
    const double middleValue,
    const double lowerValue,
    const std::size_t dimension,
    const boost::shared_ptr<const BoundaryCondition>& boundaryCondition)
    :
    _upperValue(upperValue),
    _middleValue(middleValue),
    _lowerValue(lowerValue),
    _boundaryCondition(boundaryCondition),
    _tridiagonalOperator(0.0, 1.0, 0.0, dimension, boundaryCondition)
{
}

ExplicitFiniteDifference::~ExplicitFiniteDifference() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
ExplicitFiniteDifference::doBackward(
    boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& results)
{
    //before solve
    for (std::size_t rowIndex = 1; rowIndex < rightHandSide.size() - 1; ++rowIndex) {
        result[rowIndex] = rightHandSide[rowIndex + 1] * lowerValue 
            + rightHandSide[rowIndex] * middleValue 
            + rightHandSide[rowIndex - 1] * upperValue;
    }

    //solve
    _tridiagonalOperator.solve(rightHandSide, results);

    //after solve
    const double lastIndex = rightHandSide.size() - 1;
    rightHandSide[lastIndex] = boundaryCondtiion->upperCondition();
    rightHandSide[0] = boundaryCondition->lowerCondition();
}

