//  InputControls.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#pragma once
#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"
#include "DrawingUtilities.hpp"
#include "ofMain.h"
#include <functional> // <-- library for 'std::function' to handle function callbacks






/**
 * Button class representing a GUI button.
 *
 * The Button class represents a basic GUI button with a label, position, and size.
 * It provides functionalities for user interactions, including mouse pressed and released events.
 *
 */
class Button
{
public:
	/// Constructors
	Button(); // Basic constructor that initializes a button with no label and default position and size
	Button(std::string _label, float _x, float _y, float _w, float _h); // Constructor that initializes a button with a label and specific position and size
	Button(std::string _label, float _x, float _y, float _w, float _h, std::function<void()> callback);
	
	
	/// Setters
	void setPosition(ofVec2f rectPos); // Sets the position of the button
	void set(ofVec2f rectPos, ofVec2f rectSize); // Sets the position and size of the button
	
	
	
	/// User Interaction
	void draw(); // Draws the button on the screen
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	void mouseReleased(int x, int y, int button); // Handles the mouse released event
	
	
	
	
	/// Button Attributes
	ofRectangle rect; // Represents the size and position of the button
	bool isPressed; // Indicates whether the button is currently pressed
	std::string label; // The label displayed on the button
	std::function<void()> onClick; // Callback function for click events
};








/**
 * Toggle class representing a GUI toggle button.
 *
 * The Toggle class represents a basic GUI toggle button with a label, position, size, and state.
 * It provides functionalities for user interactions, including mouse pressed events.
 *
 */
class Toggle
{
public:
	/// @section Constructors
	Toggle(); // Default constructor that initializes a toggle button with no label, default position, size, and state
	Toggle(std::string _label, float _x, float _y, float _w, float _h, bool _isOn); // Constructor that initializes a toggle button with a label, specific position, size, and state
	Toggle(std::string _label, float _x, float _y, float _w, float _h, bool _isOn, std::function<void()> callback);
	
	
	/// @section Setters
	void setPosition(ofVec2f rectPos); // Sets the position of the toggle button
	
	
	/// @section Callbacks
	void callbackUpdate(); // Continuously calls the callback function while the toggle is on.
	
	
	/// @section User Interaction
	void draw(); // Draws the toggle button on the screen
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	
	
	
	/// @section Toggle Button Attributes
	ofRectangle rect; // Represents the size and position of the toggle button
	bool isOn = false; // Represents the state of the toggle button (on/off)
	std::string label; // The label displayed on the toggle button
	std::function<void()> onClick; // Callback function for click events
};








/**
 * TextField class representing a GUI text field.
 *
 * The TextField class represents a basic GUI text field with a label, position, size, min, max, value, and precision.
 * It provides functionalities for user interactions, including mouse pressed, mouse released and key released events.
 *
 */
class TextField
{
public:
	/// @section Constructors
	TextField(); // Default constructor that initializes a text field with no label, default position, size, min, max, value, and precision
	TextField(std::string _label, float _x, float _y, float _w, float _h, float _min, float _max, double &_value, int _precision); // Constructor that initializes a text field with a label, specific position, size, min, max, value, and precision
	
	
	
	/// @section Setters
	void setPosition(ofVec2f rectPos); // Sets the position of the text field
	
	
	
	/// @section User Interaction
	void draw(); // Draws the text field on the screen
	void keyReleased(int key); // Handles the key released event
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	void mouseReleased(int x, int y, int button); // Handles the mouse released event
	void validateAndSetValue(); // Validates the input and sets the value
	
	
	
	
	/// @section Text Field Attributes
	double *value; // The value to be manipulated
	double min, max; // Minimum and maximum acceptable values
	bool isTyping = false; // Flag to indicate if the user is currently editing the field
	ofRectangle rect; // Rectangle representing the TextField's area
	Button resetButton; // Button for resetting the inputted value
	Button meanButton; // Button for setting the value to the mean between the inputted min and max
	bool warningMode;
	std::string inputString; // The current string in the TextField
	std::string currentString; // The current value of the TextField
	bool inputInRange = true; // Flag check to ensure the inputted value falls within the acceptable range
	std::string label; // Label for the textfield, shown inside of the textfield box, preceding the user defined text space
	int precision;  // Integer to track the degree of precision needed to record and display value of object passed into slider. For example, gravitational constant, 'g', needs approximately 15 digits of precision
};






/**
 * Tab class representing a GUI tab.
 *
 * The Tab class represents a basic GUI tab with a label, position, size, and state.
 * It provides functionalities for user interactions, including mouse pressed events.
 *
 */
class Tab
{
public:
	///=== Constructors
	Tab(); // Instantiates a tab with default labeling and geometry
	Tab(std::string _label, float _x, float _y, float _w, float _h, bool _isPressed); // Instantiates a labeled tab with defined dimensions and state
	Tab(std::string _label, float _x, float _y, float _w, float _h, bool _isPressed, std::function<void()> callback); // Instantiates a labeled tab with a callback, dimensions, and state
	
	
	
	
	
	///=== Setters
	void setPosition(ofVec2f rectPos); // Updates the tab's positional coordinates
	void set(ofVec2f rectPos, ofVec2f rectSize); // Configures both tab position and dimensions
	
	
	
	
	
	///=== User Interaction
	void draw(); // Renders the tab onto the screen
	void mousePressed(int x, int y, int button); // Detects and processes mouse press events over the tab
	
	
	
	
	
	///=== Tab Attributes
	ofRectangle rect; // Represents the size and position of the tab
	bool isPressed;   // Indicates the current pressed/unpressed state of the tab
	std::string label; // The text label shown on the tab
	std::function<void()> onClick; // Callback function triggered upon a click event
								   //TabClickCallback onClickCallback; // Function pointer for an alternative click callback
};
