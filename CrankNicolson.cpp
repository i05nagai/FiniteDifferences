#include "CrankNicolson.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CrankNicolson::CrankNicolson(
    const double upperValue,
    const double middleValue,
    const double lowerValue,
    const std::size_t dimension,
    const boost::shared_ptr<const BoundaryCondition>& boundaryCondition)
    :
    _upperValue(upperValue),
    _middleValue(middleValue),
    _lowerValue(lowerValue),
    _boundaryCondtion(boundaryCondition),
    _tridiagonalOperator(lowerValue, middleValue, upperValue, 
        dimension, boundaryCondition)
{
}

CrankNicolson::~CrankNicolson() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void CrankNicolson::doBackward(
    boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& results)
{
    //berfore solve
    const std::size_t lastIndex = rightHandSide.size() - 1;
    rightHandSide[lastIndex] = _boundaryCondtion->upperCondition(rightHandSide);
    rightHandSide[0] = _boundaryCondtion->lowerCondition(rightHandSide);
    
    for (std::size_t rowIndex = 1; rowIndex < rightHandSide.size() - 1; ++rowIndex) {
        results[rowIndex] = 
            - rightHandSide[rowIndex + 1] * _lowerValue 
            - rightHandSide[rowIndex] * (_middleValue - 2.0)
            - rightHandSide[rowIndex - 1] * _upperValue;
    }

    //solve
    _tridiagonalOperator.solve(rightHandSide, results);

    //after solve
}

