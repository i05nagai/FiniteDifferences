#include "StepConditionAmerican.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
StepConditionAmerican::StepConditionAmerican() 
{
    
}
StepConditionAmerican::~StepConditionAmerican() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void StepConditionAmerican::applyAfterBackward(
    boost::numeric::ublas::vector<double>& previousStep)
{
    for (std::size_t dimensionIndex = 0; dimensionIndex < previousStep; 
        ++dimensionIndex) {
        
        previousStep[dimensionIndex] = 
            std::max(previousStep[dimensionIndex], 
                payOff->operator()(stocks[dimensionIndex]));
    }
}
