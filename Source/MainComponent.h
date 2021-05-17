#pragma once

#include <JuceHeader.h>

/*
 a Car IS A Vehicle
 a Car IS A modern invention
 a Car IS A status symbol
 a Car IS A too
 */

// Our base classes
struct Tool
{
    // default argument added to constructor in case one isn't added
    Tool(const juce::String& purpose_ = "to perform work")
        : purpose(purpose_)
    {
        
    }
    juce::String purpose;
};

// if your base class constructor requires arguments, we need explicitly provide them in the preconstructor init list of the derived classes
struct Vehicle : public Tool
{
    Vehicle()
    // initialise the base class and provide the constructor argument to the base class constructor
        : Tool("To move object")
    {
        
    }
};
struct ModernInvention {};
struct StatusSymbol {};

struct Car : public Vehicle,
                    ModernInvention,
                    StatusSymbol,
{
    
};




//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
