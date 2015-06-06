#include "FiniteDifferences.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
FiniteDifference::FiniteDifference(
    const boost::numeric::ublas::vector<double>& stocks)
    :
    _stocks(stocks)
{
}

FiniteDifference::~FiniteDifference() 
{
}


void FiniteDifference::doScheme(
    const boost::shared_ptr<const FiniteDifferenceScheme> scheme,
    const boost::shared_ptr<const StepCondition> stepCondition,
    const boost::numeric::ublas::vector<double> rightHandSide) const
{
    for (std::size_t timeIndex = 0; timeIndex < endIndex; ++timeIndex) {
        scheme->doBackward(rightHandSide, );

        stepCondition->applyAfterBackward(rightHandSide);
    }
}

