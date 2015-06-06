#include "TridiagonalOperator.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
TridiagonalOperator::TridiagonalOperator(
    boost::numeric::ublas::vector<double>& upperDiagonal,
    boost::numeric::ublas::vector<double>& middleDiagonal,
    boost numberic::ublas::vector<double>& lowerDiagonal)
    :
    _upperDiagonal(upperDiagonal),
    _middleDiagonal(middleDiagonal),
    _lowerDiagonal(lowerDiagonal)
{
    
}

TridiagonalOperator::TridiagonalOperator(
    const double upperValue,
    const double middleValue,
    const double lowerValue,
    const std::size_t rowLength
    const boost::shared_ptr<const BoundaryCondition>& boundaryCondiion);
    :
    _upperDiagonal(rowLength, upperValue),
    _middleDiagonal(rowLength, middleValue),
    _lowerDiagonal(rowLength, lowerValue)
{
    BoundaryCondition->operatorCondition(*this);
}

TridiagonalOperator::~TridiagonalOperator() 
{
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
void TridiagonalOperator::solve(
    boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& results)
{
    boost::numeric::ublas::vector<double> transformedVariable1(_upperDiagonal.size());
    boost::numeric::ublas::vector<double> transformedVariable2(_upperDiagonal.size());

    calculateTransformedVariables(rightHandSide, transformedVariable1, transformedVariable2);

    substituteTransFormedVariables(results, transformedVariable1, transformedVariable2);
}

void TridiagonalOperator::setFirstRow(const double middle, const double upper)
{
    const std::size_t lastIndex = _middleDiagonal.size() - 1;

    _middleDiagonal[lastIndex] = middle;
    _upperDiagonal[lastIndex] = upper;
}

void TridiagonalOperator::setEndRow(const double lower, const double middle)
{
    _middleDiagonal[0] = middle;
    _lowerDiagonal[0] = lower;
}

/******************************************************************************
 * private functions.
 ******************************************************************************/
void TridiagonalOperator::calculateTransformedVariables(
    const boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& transformedVariable1,
    boost::numeric::ublas::vector<double>& transformedVariable2)
{
    transformedVariable1[0] = _middleDiagonal[1] 
        - _lowerDiagonal[0] * _upperDiagonal[1] / _middleDiagonal[0];
    transformedVariable2[0] = rightHandSide[1]  
        - _upperDiagonal[1] * rightHandSide[0] / _middleDiagonal[0];

    for (std::size_t rowIndex = 2; rowIndex < _middleDiagonal.size(); ++rowIndex) {
        transformedVariable1[rowIndex - 1] = _middleDiagonal[rowIndex] 
            - _lowerDiagonal[rowIndex] * _upperDiagonal[rowIndex - 1] 
                / _transformedVariable1[rowIndex - 2];
        transformedVariable2[rowIndex - 1] = rightHandSide[rowIndex]  
            - _upperDiagonal[rowIndex] * transformedVariable2[rowIndex - 2] 
                / _transformedVariable1[rowIndex - 2];
    }
}

void TridiagonalOperator::substituteTransFormedVariables(
    boost::numeric::ublas::vector<double>& results,
    const boost::numeric::ublas::vector<double>& transformedVariable1,
    const boost::numeric::ublas::vector<double>& transformedVariable2)
{
    const std::size_t lastIndex = _middleDiagonal.size() - 1;
    results[lastIndex] = (transformedVariable2[lastIndex - 1]) / transformedVariable1[lastIndex - 1];
    for (std::size_t rowIndex = _middleDiagonal.size() - 2; rowIndex >= 0; --rowIndex) {
        results[rowIndex] = 
            (transformedVariable2[rowIndex - 1] - _lowerDiagonal[rowIndex] * results[rowIndex + 1]) 
            / transformedVariable1[lastIndex - 1];
    }
}
