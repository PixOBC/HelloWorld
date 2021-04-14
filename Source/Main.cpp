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
    // int age = 0
    int age = 0;
    int heightInInches = 0;
    float hairLength{ 0.0f };
    float GPA = 0.0f;
    unsigned int SATScore{ 0 };
    int distanceTraveled = 0;
    juce::String name;

    // Conststructor is called AFTER all member variables that can be default-constructed ARE constructed
    Person(juce::String personsName)
        : name(personsName)
    {
        DBG("Person constructor: " + name); // could use <<
    }
    // NB Destructor is called first and then member variables are destroyed after the destructor has finished executing
    ~Person() 
    {
        DBG("Person destructor: " + name);
    } 

    // int run(int howFast, bool startWithLeftFoot);
};

void PersonFunction()
{
    Person p;
}

Person::Person() 
    : age(0)
{

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

struct Family
{
    // order initialised is the order in which they were declared
    // order of destruction is reverse of construction

    Person mum;
    Person dad;
    Person child1;
    Person child2;
};

void familyFunction()
{
    // a member variables lifetime is that of its owning object
    Family family;
    family.mum.age = 42; // sequencing access mum(Family).age(Person)
}




//==============================================================================
class HelloWorldApplication  : public juce::JUCEApplication
{
public:
    //==============================================================================
    HelloWorldApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        //functionC();
        //functionB();
        //Person person;
        //DBG(person.age);
        //whileTest();

        mainWindow.reset (new MainWindow (getApplicationName()));
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

    void anotherInstanceStarted (const juce::String& commandLine) override
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
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
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
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (HelloWorldApplication)
