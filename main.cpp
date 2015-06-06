

void initializeRightHandSide(
    boost::numeric::ublas::vector<double> rightHandSide,
    const boost::shared_ptr<const PayOff>& payOff) const
{
    for (std::size_t rowIndex = 0; rowIndex < rightHandSide.size(); ++rowIndex) {
        rightHandSide[rowIndex] = payOff->operator()(rightHandSide[rowIndex]);
    }
}

inline double squared(const double x)
{
    return x * x;
}

inline double calculateUpValue()
{
    return 0.5 * timeStepSize 
        * (squared(volatility / spaceStepSize) + drifit / spaceStepSize);
}

inline double calculateMiddleValue()
{
    return 1.0 - timeStepSize * squared(volatility / spaceStepSize)
        - interestRate * timeStepSize;
}

inline double calculateDownValue()
{
    return 0.5 * timeStepSize 
        * (squared(volatility / spaceStepSize) - drifit / spaceStepSize);
}

int main(int argc, char const* argv[])
{
    /**************************************************************************
     * Programs on Chapter 3 in Clewlow.
     **************************************************************************/
    {
        /**********************************************************************
         * European Call Option by Explicit Finite Difference. Figure3.7.
         **********************************************************************/
        //parameters
        const double strike = 100.0;
        const double maturity = 1.0;
        const double spot = 100.0;
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const std::size_t numberOfTimeSteps = 3;;
        const double spaceStepSize = 0.2;

        //precomputing variables
        const std::size_t gridSize = 2 * numberOfTimeSteps + 1;
        const double drift = interestRate - dividend - 0.5 * squared(volatilit);
        const double upValue = 
            calculateUpValue(drift, volatility, timeStepSize, spaceStepSize);
        const double middleValue = calculateMiddleValue(
            interestRate, drift, volatility, timeStepSize, spaceStepSize);
        const double downValue = 
            calculateDownValue(drift, volatility, timeStepSize, spaceStepSize);

        //payoff
        const boost::shared_ptr<const PayOff> payOff(new PayOffCall(strike));

        //initial value
        const boost:::numeric::ublas::vector<double> rightHandSide(gridSize);
        initializeRightHandSide(rightHandSide, payOff);

        //boundary condition
       const boost::shared_ptr<const BoundaryCondition> boundaryConditionCall(
           new BoundaryConditionCall());

       //Finite difference scheme
       const boost::shared_ptr<const FiniteDifferenceScheme> scheme(
           new ExplicitFiniteDifference(upValue, middleValue, downValue,
                boundaryConditionPut));

       //step condition
       const boost::shared_ptr<const StepCondition> stepCondition(
           new StepConditionNull());

       //calculate price
       FiniteDifferences finiteDifferences(scheme, stepCondition)
    }
    
    return 0;
}
