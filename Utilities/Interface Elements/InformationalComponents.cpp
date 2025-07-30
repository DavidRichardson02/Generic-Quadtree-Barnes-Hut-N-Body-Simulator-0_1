//  InformationalComponents.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#include "InformationalComponents.hpp"






Tooltip::Tooltip() : message(""), position(0, 0), isMessageVisible(false), isLargeMessage(false) {}





Tooltip::Tooltip(std::string message, float x, float y) : message(message), position(x, y), isMessageVisible(false), isLargeMessage(message.length() > 250)
{
	// Initialize message box based on the message length
	float width = isLargeMessage ? 300 : 150;
	float height = isLargeMessage ? 100 : 50;
	float xOffset = isLargeMessage ? ofGetWidth() / 2 - width / 2 : x - width / 2;
	float yOffset = isLargeMessage ? ofGetHeight() / 2 - height / 2 : y - height / 2;
	messageBox.set(xOffset, yOffset, width, height);
}



// Set the position of the tooltip icon
void Tooltip::setPosition(float x, float y)
{
	position.set(x, y);
}

// Set the message to be displayed in the tooltip
void Tooltip::setMessage(const std::string& newMessage)
{
	message = newMessage;
	isLargeMessage = message.length() > 250;
}




void Tooltip::toggleVisibility()
{
	isMessageVisible = !isMessageVisible;
}




// Draw the tooltip icon and the message box if it is visible
void Tooltip::draw() 
{
	drawTooltipIcon();
	if (isMessageVisible)
	{
		drawMessageBox();
	}
}

// Handle mouse pressed events
void Tooltip::mousePressed(int x, int y, int button)
{
	if (isMouseInside(x, y, ofRectangle(position.x - 10, position.y - 10, 20, 20))) 
	{
		isMessageVisible = !isMessageVisible;
	} 
	else if (isMessageVisible && !isLargeMessage)
	{
		isMessageVisible = false;
	}
}

// Handle mouse released events
void Tooltip::mouseReleased(int x, int y, int button) 
{
	// No action needed on mouse release
}








// Draw the tooltip icon
void Tooltip::drawTooltipIcon() 
{
	ofFill();
	ofSetColor(255, 255, 255);
	ofDrawCircle(position, 10);
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("?", position.x - 4, position.y + 5);
}




// Draw the message box
void Tooltip::drawMessageBox() 
{
	float boxWidth = 300;
	float boxHeight = 150;
	float xPos, yPos;
	
	if (isLargeMessage) {
		xPos = ofGetWidth() / 2 - boxWidth / 2;
		yPos = ofGetHeight() / 2 - boxHeight / 2;
	} else {
		xPos = position.x - boxWidth / 2;
		yPos = position.y - boxHeight / 2;
	}
	
	messageBox.set(xPos, yPos, boxWidth, boxHeight);
	
	
	// Draw message box inner
	ofFill();
	ofSetColor(255, 255, 255);
	ofDrawRectangle(messageBox);
	
	
	// Draw message box border
	ofNoFill();
	ofSetLineWidth(2.5);
	ofSetColor(255, 0, 0);
	ofDrawRectangle(messageBox);
	
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(message, xPos + 10, yPos + 20);
	
	if (isLargeMessage)
	{
		ofSetColor(255, 0, 0);
		ofDrawBitmapString("X", xPos + boxWidth - 15, yPos + 15);
	}
}




// Check if the mouse is inside a given rectangle
bool Tooltip::isMouseInside(int x, int y, ofRectangle rect) 
{
	return x >= rect.x && x <= rect.x + rect.width && y >= rect.y && y <= rect.y + rect.height;
}
