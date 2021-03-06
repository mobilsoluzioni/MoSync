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
 * @file TestScreen.cpp
 * @author Bogdan Iusco.
 *
 * @brief Shows the tested Image widget.
 */

#define SCREEN_TITLE "Test screen"

#include <conprint.h>
#include <wchar.h>
#include <ma.h>
#include <maassert.h>
#include <mawstring.h>
#include <mastdlib.h>

#include "TestScreen.h"
#include "MAHeaders.h"

namespace ImageTest
{
	/**
	 * Constructor.
	 */
	TestScreen::TestScreen() :
		Screen(),
		mMainLayout(NULL),
		mImage(NULL),
		mGetImageAlpha(NULL),
		mImageAlpha(NULL),
		mImageSlider(NULL),
		mLayout(NULL),
		mGetLayoutAlpha(NULL),
		mLayoutAlpha(NULL),
		mLayoutSlider(NULL)
	{
		this->setTitle(SCREEN_TITLE);

		createMainLayout();
		mGetImageAlpha->addButtonListener(this);
		mGetLayoutAlpha->addButtonListener(this);
		mImageSlider->addSliderListener(this);
		mLayoutSlider->addSliderListener(this);
	}

	/**
	 * Destructor.
	 */
	TestScreen::~TestScreen()
	{
		mGetImageAlpha->removeButtonListener(this);
		mGetLayoutAlpha->removeButtonListener(this);
		mImageSlider->removeSliderListener(this);
		mLayoutSlider->removeSliderListener(this);
	}

	/**
	 * Display a image from a given file path.
	 * @param path Image file path.
	 */
	void TestScreen::showImageUsingFilePath(const MAUtil::String& path)
	{
		mImage->setImagePath(path);
	}

	/**
	 * Display the image from resources.
	 * @param handle Image handle.
	 */
	void TestScreen::showImageUsingHandle(MAHandle handle)
	{
		mImage->setImage(handle);
	}

	/**
	 * Get previous set image path.
	 */
	MAUtil::String TestScreen::getImagePath()
	{
		return mImage->getImagePath();
	}

	/**
	 * This method is called when there is an event for this widget.
	 * @param widget The widget object of the event.
	 * @param widgetEventData The low-level event data.
	 */
	void TestScreen::handleWidgetEvent(Widget* widget,
			MAWidgetEventData* widgetEventData)
	{

	}

	/**
	 * Creates and adds main layout to the screen.
	 */
	void TestScreen::createMainLayout() {
		// Create and add the main layout to the screen.
		mMainLayout = new VerticalLayout();
		mMainLayout->setBackgroundColor(0xFF0000);
		Screen::setMainWidget(mMainLayout);

		mImage = new Image();
		mMainLayout->addChild(mImage);

		int result = mImage->setImage(RES_IMAGE);
		printf("result setImage = %d", result);
		mImage->setScaleMode(IMAGE_SCALE_NONE);

		Label* infoImage = new Label();
		infoImage->setText("Set the image transparency");
		mMainLayout->addChild(infoImage);

		// Slider with alpha value, button for getting the value and
		// label for printing it.
		mImageSlider = new Slider();
		mImageSlider->fillSpaceHorizontally();
		mImageSlider->setMaximumValue(100);
		mImageSlider->setValue(100);
		mMainLayout->addChild(mImageSlider);

		mGetImageAlpha = new Button();
		mGetImageAlpha->setText("Get Image alpha");
		mMainLayout->addChild(mGetImageAlpha);

		mImageAlpha = new Label();
		mImageAlpha->setText("The image alpha = ");
		mMainLayout->addChild(mImageAlpha);

		// Spacer
		Layout* spacer = new VerticalLayout();
		spacer->fillSpaceHorizontally();
		spacer->setHeight(40);
		mMainLayout->addChild(spacer);

		Label* infoLayout = new Label();
		infoLayout->setText("Set the blue layout transparency");
		mMainLayout->addChild(infoLayout);

		mLayoutSlider = new Slider();
		mLayoutSlider->fillSpaceHorizontally();
		mLayoutSlider->setMaximumValue(100);
		mLayoutSlider->setValue(0);
		mMainLayout->addChild(mLayoutSlider);

		mGetLayoutAlpha = new Button();
		mGetLayoutAlpha->setText("Get layout alpha");
		mMainLayout->addChild(mGetLayoutAlpha);

		mLayoutAlpha = new Label();
		mLayoutAlpha->setText("The layout alpha = ");
		mMainLayout->addChild(mLayoutAlpha);

		mLayout = new VerticalLayout();
		mLayout->setBackgroundColor(0x0000FF);
		mLayout->fillSpaceHorizontally();
		mLayout->setAlpha(0.0);
		mLayout->setHeight(50);
		mMainLayout->addChild(mLayout);
	}


	/**
	 * This method is called when the value of the slider was modified by
	 * the user.
	 * @param slider The slider object that generated the event.
	 * @param sliderValue The new slider's value.
	 */
	void TestScreen::sliderValueChanged(
		Slider* slider,
		const int sliderValue)
	{
		float alphaValue = (float) sliderValue / 100;
		if ( slider == mImageSlider )
		{
			mImage->setAlpha(alphaValue);
		}
		else if ( slider == mLayoutSlider )
		{
			mLayout->setAlpha(alphaValue);
		}
	}

	/**
	 * This method is called if the touch-up event was inside the
	 * bounds of the button.
	 * @param button The button object that generated the event.
	 */
	void TestScreen::buttonClicked(Widget* button)
	{
		if ( mGetImageAlpha == button )
		{
			float alphaValue = mImage->getAlpha();
			char buf[MAX_BUF_SIZE];
			sprintf(buf, "Image Alpha: %f",alphaValue);
			mImageAlpha->setText(buf);
		}
		else if ( mGetLayoutAlpha == button )
		{
			float alphaValue = mLayout->getAlpha();
			char buf[MAX_BUF_SIZE];
			sprintf(buf, "Layout Alpha: %f",alphaValue);
			mLayoutAlpha->setText(buf);
		}
	}

} // end of ImageTest
