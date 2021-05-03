/*
  ==============================================================================

	This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

struct Person
{
	// if the member variables CANNOT be default-constructed (e.g. if it only has one constructor declared and that constructor takes arguments) then that member variable must be initialised in the Constructor's member intialisation list
	int age = 0;
	int heightInInches = 0;
	float hairLength{ 0.0f };
	float GPA = 0.0f;
	unsigned int SATScore{ 0 };
	int distanceTraveled = 0;

	int run(int howFast, bool startWithLeftFoot);

	juce::String name;

	Person() {}

	// Conststructor is called AFTER all member variables that can be default-constructed ARE constructed
	Person(juce::String personsName)
		: name(personsName)
	{
		DBG("Person constructor: " + name); // could use <<
	}

	// When program execution is inside a constructoror any member function the scope INCLUDES all class member variables.
	Person(int age)
	{
		this->age = age;
	}
	// NB Destructor is called first and then member variables are destroyed after the destructor has finished executing
	~Person()
	{
		DBG("Person destructor: " + name);
	}

	void moveAndSetAge(int speed, int newAge);

	struct Foot
	{
		int stepForward() { return 0; }
	};
	Foot leftFoot;
	Foot rightFoot;
};

int Person::run(int howFast, bool startWithLeftFoot)
{
	if (startWithLeftFoot)
	{
		return leftFoot.stepForward() + rightFoot.stepForward();
	}

	return rightFoot.stepForward() + leftFoot.stepForward();
}

// in what scope or context is that run() function being called? Who owns it? Who owns that age variable?
// p owns them - While we are in the scope of move and set age the calling object is the owner.
// 1. When we are using members of our Person from an outside perspective, we used the instance name, dot, then the name of the member we wanted to access.
// 2. However, when we are inside a member function called from an outside scope, the calling object is the owner. We use the 'this' keyword and arrow operator to express the name of the calling object.

void Person::moveAndSetAge(int speed, int newAge)
{
	run(speed, true);
	age = newAge;
}

// free function
void doStuff()
{
	//Person p{"person"};
	Person p(6);
	p.moveAndSetAge(5, 42);
}

struct IntValue
{
	IntValue()
	{
		DBG("IntValue constructor");
	}

	~IntValue()
	{
		DBG("IntValue destructor");
	}

	int value;
};

int functionA(int val)
{
	IntValue a;
	a.value = 5;
	return val * 2 + a.value;
}
void functionB()
{
	IntValue val;
	val.value = functionA(3);
	val.value *= 4;
}

void functionC()
{
	int i = 0;
	// conditional check (0 < 3)happens OUTSIDE of the nested scope
	while (i < 3)
	{
		IntValue a;
		a.value += i;
		i += 1;
	}

	for (int i = 0; i < 3; i += 1)
	{
		IntValue a;
		a.value += i;
	}


}

void whileTest()
{
	bool b = true;
	while (b)
	{
		b = false;
		DBG("b is " << (b ? "true" : "false"));
	}
}

//=================================================================

struct Family
{
	// order initialised is the order in which they were declared
	// order of destruction is reverse of construction

	Family() { DBG("family constructor"); }
	~Family() { DBG("family deconstructor"); }

	Person mum{ "mum" };
	Person dad{ "dad" };
	Person child1{ "child1" };
	Person child2{ "child2" };
};

void familyFunction()
{
	// a member variables lifetime is that of its owning object
	Family family;
}

void functionForLearningCPP()
{
	Person a, b, c;

	a.age = 24;
	b.age = 24;
	c.age = 24;

	// all the information in a has been COPIED into a new instance inside the vector
	// so, when you modify the i'th instance in the vector it's a completely different variable to the one declared above. That instance is owned by the vector
	// Using pointers, We're storing the memory address of where our object currently lives
	// '=' operator now just copies the memory address of a, b and c rather than all of their member variables 
	std::vector<Person*> persons = { &a, &b, &c };

	for (size_t i = 0; i > persons.size(); ++i)
	{
		// changing all objects in vector to the same value
		Person* p = persons[i];
		// '.' is for accessing an the member functions/variables DIRECTLY. '->' is for accessing the member functions/variables of some object that you're POINTING to.
		p->age = 24;
	}

	// THIS IS THE NAME OF THE POINTER VARIABLE THAT IS POINTING TO AT WHATEVER CLASS INSTANCE IS BEING USED WHEN YOU'RE INSIDE OF A MEMBER FUNCTION

	/*
	* person[i].<name of the member function/variable>;
	*/

}

void addressOfFunction()
{
	Person a, b, c;

	Person* p1 = nullptr;
	Person* p2 = &b;
	Person* p3 = nullptr;

	// always check if pointers are not a nullptr before using them by dereferencing
	if (p1 != nullptr)
	{
		p1->age = 42;
		(*p1).age = 42;
	}

	// Though p1, p2 and p3 all different addresses in memory, their value is still the same (the address where person a lives)
	p1 = &a;
	p2 = &a;
	p3 = &a;

	// with pointers, they still store a value. It's just the value just happens to be the address of where some other object lives
	p1 = &a;
	p1 = &b;
	p1 = &c;

	//just like
	int num;
	num = 3;
	num = 5;
	num = 8;

	Person* personPtr;
	*personPtr;
}

void normalCopy()
{
	Person a;
	Person b;

	a = b;
}

void copyingWithPointers()
{
	Person a;
	Person b;
	Person* p1 = &a;

	// copies the contents of b into whatever p1 is pointing to (a)
	*p1 = b;

}

int Person::run(int howFast, bool startWithLeftFoot)
{
	this->distanceTraveled = this->leftFoot.stepForward() + this->rightFoot.stepForward();
}

void test()
{
	Person p;

}

// THINK OF THE THIS KEYWORD AS THOUGH YOUR FUNCTION WAS WRITTING THIS WAY
// The following two functions show what happens when you call a member function
// IT'S CALLED 'HIDDEN THIS' https://www.learncpp.com/cpp-tutorial/the-hidden-this-pointer/
// Conversely, the static keyword tells the compiler 'don't add a hidden 'Type* this' at the beginning of class member function's parameter list. It's the same reason static functions cannot use member variables inside their function body (no means of accessing any member variables inside that function body). Static member variables are tied to the lifetime of the program not an object
int Person::run(Person* this, int howFast, bool startWithLeftFoot)
{
	this->distanceTraveled = this->leftFoot.stepForward() + this->rightFoot.stepForward();
}

// Calling run()
void test()
{
	Person p;
	Person* ptrToThis = &p; // this is this
	Person::run(ptrToThis, 45, true);
}










//==============================================================================
class HelloWorldApplication : public juce::JUCEApplication
{
public:
	//==============================================================================
	HelloWorldApplication() {}

	const juce::String getApplicationName() override { return ProjectInfo::projectName; }
	const juce::String getApplicationVersion() override { return ProjectInfo::versionString; }
	bool moreThanOneInstanceAllowed() override { return true; }

	//==============================================================================
	void initialise(const juce::String& commandLine) override
	{
		// This method is where you should put your application's initialisation code..
		doStuff();
		//familyFunction();
		//functionB();
		//Person person;
		//DBG(person.age);
		//whileTest();

		mainWindow.reset(new MainWindow(getApplicationName()));
	}

	void shutdown() override
	{
		// Add your application's shutdown code here..

		mainWindow = nullptr; // (deletes our window)
	}

	//==============================================================================
	void systemRequestedQuit() override
	{
		// This is called when the app is being asked to quit: you can ignore this
		// request and let the app carry on running, or call quit() to allow the app to close.
		quit();
	}

	void anotherInstanceStarted(const juce::String& commandLine) override
	{
		// When another instance of the app is launched while this one is running,
		// this method is invoked, and the commandLine parameter tells you what
		// the other instance's command-line arguments were.
	}

	//==============================================================================
	/*
		This class implements the desktop window that contains an instance of
		our MainComponent class.
	*/
	class MainWindow : public juce::DocumentWindow
	{
	public:
		MainWindow(juce::String name)
			: DocumentWindow(name,
				juce::Desktop::getInstance().getDefaultLookAndFeel()
				.findColour(juce::ResizableWindow::backgroundColourId),
				DocumentWindow::allButtons)
		{
			setUsingNativeTitleBar(true);
			setContentOwned(new MainComponent(), true);

#if JUCE_IOS || JUCE_ANDROID
			setFullScreen(true);
#else
			setResizable(true, true);
			centreWithSize(getWidth(), getHeight());
#endif

			setVisible(true);
		}

		void closeButtonPressed() override
		{
			// This is called when the user tries to close this window. Here, we'll just
			// ask the app to quit when this happens, but you can change this to do
			// whatever you need.
			JUCEApplication::getInstance()->systemRequestedQuit();
		}

		/* Note: Be careful if you override any DocumentWindow methods - the base
		   class uses a lot of them, so by overriding you might break its functionality.
		   It's best to do all your work in your content component instead, but if
		   you really have to override any DocumentWindow methods, make sure your
		   subclass also calls the superclass's method.
		*/

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
	};

private:
	std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(HelloWorldApplication)
