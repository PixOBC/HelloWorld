#pragma once

#include <JuceHeader.h>

/*
* Inheritance IS A, Composition HAS A
 a Car IS A Vehicle
 a Car IS A modern invention
 a Car IS A status symbol
 a Car IS A too

 a Car HAS A heater
 a Car HAS A engine
 a Care HAS A air conditioner
 a Car HAS A battery
 */

 // Our base classes. Base class initialisation
struct Tool
{
	// default argument added to constructor in case one isn't added
	Tool(const juce::String& purpose_ = "to perform work")
		: purpose(purpose_)
	{

	}
	juce::String purpose;
};
struct TemperatureController { int currentTemp = 0; };
struct PowerSupply
{
	PowerSupply(int po)
		: powerOutput(po)
	{

	}
	int powerOutput = 0;
};

struct Heater : public TemperatureController {};
struct AirConditioner : public TemperatureController {};

struct Engine : public PowerSupply
{
	Engine(int power = 5)
		: PowerSupply(power)
	{
	}
};

struct Battery : public PowerSupply
{
	Battery(int power = 3)
		: PowerSupply(power)

	{
	}
};

// if your base class constructor requires arguments, we need explicitly provide them in the preconstructor init list of the derived classes
struct Vehicle : public Tool
{
	Vehicle(const juce::String& purpose_, int enginePower, int batteryPower)
		// initialise the base class and provide the constructor argument to the base class constructor
		: Tool(purpose_),
		  engine(enginePower),
		  battery(batteryPower)
	{
	}
	Heater heater;
	AirConditioner airConditioner;
	Engine engine;
	Battery battery;
};
struct ModernInvention
{
	int yearInvented = 1901;
};
struct StatusSymbol {};

struct SemiTruck : public Vehicle
{
	SemiTruck()
		: Vehicle("to move cargo", 20, 10)
	{

	}
};


struct Car : public Vehicle,
			 public ModernInvention,
			 public StatusSymbol
{
	Car()
		: Vehicle("to move people", 5, 2)
	{
		yearInvented = 1808;
		this->ModernInvention::yearInvented = 1808;
	}

};

//==============================================================================
/*
	This component lives inside our window, and this is where you should put all
	your controls and content.
*/
class MainComponent : public juce::Component
{
public:
	//==============================================================================
	MainComponent();
	~MainComponent() override;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;

private:
	//==============================================================================
	// Your private member variables go here...


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
