#include "ImplicitFiniteDifference.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
ImplicitFiniteDifference::ImplicitFiniteDifference() 
{
    
}
ImplicitFiniteDifference::~ImplicitFiniteDifference() 
{
}


/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void ImplicitFiniteDifference::doBackward(
    boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& result)
{
    rightHandSide[] = boundaryCondtion->upperCondition();
    rightHandSide[] = boundaryCondtion->lowerCondition();

    tridiagonalOperator.solve(rightHandSide, results);

}

