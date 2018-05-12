#include "FiniteDifference.h"

#include <memory>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
FiniteDifference::FiniteDifference(
    const boost::numeric::ublas::vector<double>& stocks,
    const std::size_t numberOfTimeSteps)
    :
    _stocks(stocks),
    _numberOfTimeSteps(numberOfTimeSteps)
{
}

FiniteDifference::~FiniteDifference() 
{
}


boost::numeric::ublas::vector<double> FiniteDifference::doScheme(
    const std::shared_ptr<const FiniteDifferenceScheme> scheme,
    const std::shared_ptr<const StepCondition> stepCondition,
    boost::numeric::ublas::vector<double>& rightHandSide) const
{
    boost::numeric::ublas::vector<double> results(rightHandSide.size(), 0.0);

    for (std::size_t timeIndex = 0; timeIndex < _numberOfTimeSteps; ++timeIndex) {
        std::cout << "rhs:" << rightHandSide << std::endl;
        std::cout << "results:" << results << std::endl;
        scheme->doBackward(rightHandSide, results);

        stepCondition->applyAfterBackward(results);

        rightHandSide.swap(results);
    }

    return rightHandSide;
}

