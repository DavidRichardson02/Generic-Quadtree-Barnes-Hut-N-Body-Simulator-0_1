#pragma once
#include "InputControls.hpp"


/// This class provides an interactive tooltip that displays a message at a given position.
/// Its message box can be toggled on or off, and is drawn conditionally based on user interaction.
/// It helps deliver contextual information to the user.
class Tooltip
{
public:
	
	
	/// Constructors
	Tooltip(); // Initializes a default tooltip with no message and default position
	Tooltip(std::string message, float x, float y); // Initializes a tooltip using the given message and position
	
	
	
	
	/// Setters
	void setPosition(float x, float y); // Updates the tooltip's position on the screen
	void setMessage(const std::string &newMessage); // Changes the displayed message text
	void toggleVisibility(); // Flips the visibility state of the tooltip's message box
	
	
	
	
	/// Upkeep
	void draw(); // Renders the tooltip icon and, if visible, the tooltip's message box onto the screen
	
	
	
	
	/// User Interaction
	void mousePressed(int x, int y, int button); // Responds to mouse press events on or near the tooltip icon
	void mouseReleased(int x, int y, int button); // Responds when mouse button is released, finalizing interaction
	
private:
	ofVec2f position;       // Coordinates for the tooltip icon
	std::string message;    // The text content to display
	bool isMessageVisible;  // Tracks whether the tooltip message is currently visible
	ofRectangle messageBox; // Defines the bounding box of the tooltip message
	bool isLargeMessage;    // Flags if the message content is lengthy
	
	void drawTooltipIcon(); // Draws the icon representing the tooltip
	void drawMessageBox();  // Draws the rectangular message box if visible
	bool isMouseInside(int x, int y, ofRectangle rect); // Checks if mouse coordinates lie within a given rectangle
};




//
/*
//  InformationalComponents.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#pragma once
#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"
#include "InputControls.hpp"




class Tooltip
{
public:
	Tooltip();
	Tooltip(std::string message, float x, float y);
	
	void setPosition(float x, float y);
	void setMessage(const std::string &newMessage);
	void draw();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void toggleVisibility();  // Toggle the visibility of the message box
	
private:
	ofVec2f position;  // Tooltip icon position
	std::string message;  // Message displayed in the tooltip
	bool isMessageVisible;  // Visibility state of the message box
	ofRectangle messageBox;  // Bounding box for the message
	bool isLargeMessage;  // Flag to check if message is long
	
	void drawTooltipIcon();
	void drawMessageBox();
	bool isMouseInside(int x, int y, ofRectangle rect);
};
//*/
