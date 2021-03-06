#include "stdafx.h"
#include <iostream>

/*
The Singleton Pattern ensures that a class has only one instance.  I've only used this in the past to give objects
a unique ID number (for example with the Cat/Dog queue in problem 3.6, but there have also been others).

Suppose we want to create a class which follows the singleton pattern --- let's call it MyClass.

The basic idea is that (i) the constructor should be private (in the book it's protected, but that's a decision which
should be made on a case-by-case basis), and (ii) the class should have a private static member variable of type MyClass
which plays the role of the one and only instance of an object of type MyClass.

(iii) Finally, to access this object, we should have some *static* method with a signature something like
	public static MyClass getInstance() { ..... }
which returns *the* static instance we set up earlier.

This method needs to be static because static class methods can be called without specifying an object, so we can 
call the method even if we haven't instantiated our MyClass object yet.  This is necessitated, for one thing, by the
fact that our constructor is private. 
*/


/*
I forgot just how strangely static objects behave in C++.  All sorts of compile errors, so I had to shave it down to
what we have below.  Some day, look into how static stuff works, but for now this is an OK reference on creating
a simple singleton pattern.
*/

class MyClass
{
private:
	int m_data = 0;	
	MyClass() {}


public:
	static MyClass & getInstance()
	{
		static MyClass ourInstance;
		return ourInstance;
	}

	void incrementData()
	{
		++m_data;
	}

	void saySomething()
	{
		std::cout << m_data << std::endl;
	}

	MyClass(const MyClass &) = delete;
	void operator=(const MyClass &) = delete;
};



int main()
{
	MyClass * someObj;
	MyClass * someOtherObj;

	
	someObj->getInstance().saySomething();
	someOtherObj->getInstance().saySomething();
	someObj->getInstance().incrementData();

	someObj->getInstance().saySomething();
	someOtherObj->getInstance().saySomething();
	someOtherObj->getInstance().incrementData();

	someObj->getInstance().saySomething();
	someOtherObj->getInstance().saySomething();
	someObj->getInstance().incrementData();
	

	//MyClass  someOtherObj = MyClass::getInstance();
	/*
	someObj.incrementData();
	someObj.saySomething();
	someOtherObj.saySomething();

	someOtherObj.incrementData();
	someObj.saySomething();
	someOtherObj.saySomething();
	*/
    return 0;
}


