/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/**
 * @file Main.cpp
 * @author Mikael Kindborg
 *
 * This is the main entry point for the example application
 * that demonstrates NativeUI on MoSync.
 */
#include <ma.h> 				// Syscalls
#include <MAUtil/String.h>		// C++ String class
#include <MAUtil/Moblet.h>		// Moblet class
#include <conprint.h>			// lprintfln for logging

#include "Util.h"

using namespace MAUtil;

/**
 * Moblet for the  application.
 */
class TestMoblet : public Moblet
{
public:
	/**
	 * Constructor.
	 */
	TestMoblet():
	mTestCount(0)
	{
		printf("Running tests ...............\n");
		createTest();
	}

	void TestMoblet::createTest()
	{
		mTestCount = 1;
		// Call the maAlert syscall with all 3 buttons.
		maAlert("First test", "Press <<OK>> for the test to pass.", "Ok", "Maybe", "Cancel");
	}

	/**
	 * Destructor.
	 */
	virtual ~TestMoblet()
	{
	}

	/**
	 * This method is called when the application is closed.
	 */
	void TestMoblet::closeEvent()
	{
		// Exit the app.
		close();
	}

	void TestMoblet::testFailed(int testNumber)
	{
		printf("Test %d has failed", testNumber);
	}

	void TestMoblet::testsSucceeded()
	{
		printf("All test have passed. You can now exit.");
	}

	/**
	* This function is called when an event that Moblet doesn't recognize is recieved.
	*/
	void TestMoblet::customEvent(const MAEvent& event)
	{
		if ( event.type == EVENT_TYPE_ALERT)
		{
//			printf("\n =========== Alert Event received ======\n");
			MAUtil::String temp = "";
			switch( event.alertButtonIndex)
			{
			case 1:
				temp += "First ";
				if (mTestCount == 1)
				{
					printf("First test has passed");
					mTestCount ++;
					maAlert("Second test", "Press <<Maybe>> for the test to pass.", "Ok", "Maybe", "Cancel");
				}
				else
				{
					testFailed(1);
				}
				break;
			case 2:
				temp += "Second ";
				if (mTestCount == 2)
				{
					printf("Second test has passed");
					mTestCount++;
					maAlert("Third test", "Press <<Cancel>> for the test to pass.", "Ok", "Maybe", "Cancel");
				}
				else
				{
					testFailed(2);
				}
				break;
			case 3:
				temp += "Third ";
				if (mTestCount == 3)
				{
					printf("Third test has passed");
					if ( isAndroid() )
					{
						mTestCount++;
						maAlert("Fourth test", "Press Back key for the test to pass.", "Ok", "Maybe", "Cancel");
					}
					else
					{
						testsSucceeded();
					}
				}
				else
				{
					testFailed(3);
				}
				break;
			default:
				temp = "err";
			}
			temp += " button was clicked";
			printf(temp.c_str());
		}
		else if( event.type == EVENT_TYPE_ALERT_DISMISSED )
		{
			printf("Alert was dismissed by pressing back!");
			if (mTestCount == 4)
			{
				testsSucceeded();
			}
			else
			{
				testFailed(4);
			}
		}
	}

	/**
	 * Method called when a key is pressed.
	 */
	void TestMoblet::keyPressEvent(int keyCode, int nativeCode)
	{
	    // Close the application if the back key is pressed.
	    if(MAK_BACK == keyCode)
	    {
	        closeEvent();
	    }
	}
private:
	int mTestCount;
};

/**
 * Main function that is called when the program starts.
 */
extern "C" int MAMain()
{
	// Create a moblet.
	TestMoblet* moblet = new TestMoblet();

	// Run the moblet event loop.
	Moblet::run(moblet);

	// Deallocate objects.
	delete moblet;

	return 0;
}
