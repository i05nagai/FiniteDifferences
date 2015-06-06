#pragma once

class FiniteDifferenceScheme 
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    FiniteDifferenceScheme();
    virtual ~FiniteDifferenceScheme();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void doBackward() const = 0;        
private:
            
};

