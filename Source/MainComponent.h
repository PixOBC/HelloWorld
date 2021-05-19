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

struct MyButton
{
	// virtual means its member functions can be overriden 
	struct Listener
	{
		virtual ~Listener() { }
		// no impletation  provided for buttonClicked() by the Button::Listener class (functions address is actually'0' as opposed a real address that can be called by the CPU)
		virtual void buttonClicked(MyButton*) = 0;
	};

	juce::Array<Listener*> listeners; // don't need to write <Button::Listener> because we are in the class
	void addListener(Listener* listener)
	{
		listeners.addIfNotAlreadyThere(listener);
	}
	void removeListener(Listener* listener) { listeners.removeFirstMatchingValue(listener); }

	void click()
	{
		// size - 1 >= 0
		for (int i = listeners.size(); --i >= 0; )
		{
			listeners[i]->buttonClicked(this); // buttonClicked called for every button listener stored in the array
		}
	}
};


// Any object that inherits from Button::Listener  must provide the implementation
// Done using the ovveride keyword
// override keyword is not just for providing the implementation of pure vitual functions
// it's for when you want to change the base class's ipmlementation of any function that it has marked as vitual

// use override to implement function from your derived class otherwise the implementation will take place in base class @21:45 Ch4.2

// Paused at 22:49
// We can add the instance of the widget being created as a listener to when the button is clicked. We do this by calling the button's member function button.addListener(&widget) because Widget IS A listener; it extends Button::Listener so can be passed as the argument.

// MEMBER INITIALISATION: When derived classes are instantiated their base classes are instantiated first
struct WidgetB : public MyButton::Listener
{
	MyButton button;
	void buttonClicked(MyButton* b) override {}

	WidgetB()
	{
		button.addListener(this); // this is the name that &widget goes by in the constructor 
	}

	~WidgetB()
	{
		button.removeListener(this);
	}
};




struct Widget { Widget(void*) {  } };

struct Bar { virtual ~Bar() { } };

struct Foo : public Bar // If there are multiple bass classes then the calling order is left->right
{
	Widget widgetA;
	Foo()
		: widgetA(nullptr) {}
};

// Calling order
// 1. Foo calls Bar constructor (inherits from Bar) - BASE CLASS FIRST
// 2. Foo calls Widget's constructor (instance of Widget + argument in Foo) - MEMBER VARIABLES TOP->BOTTOM
// 3. Foo then calls Foo's constructor - IT'S ACTUAL CONSTRUCTOR
inline void test2()
{
	Foo foo;
}


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
