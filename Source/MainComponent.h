#pragma once

#include <JuceHeader.h>

/*
* Inheritance IS A, Composition HAS A
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
    Vehicle(const juce::String& purpose_ = "to move objects")
    // initialise the base class and provide the constructor argument to the base class constructor
        : Tool(purpose_)
    {
    }
};
struct ModernInvention {};
struct StatusSymbol {};

struct SemiTruck : public Vehicle
{
  SemiTruck()
        : Vehicle("to move cargo")
    {
        
    }
};

struct Car : public Vehicle,
             public ModernInvention,
             public StatusSymbol
{
    Car()
        : Vehicle("to move people")
    {
        
    }
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
