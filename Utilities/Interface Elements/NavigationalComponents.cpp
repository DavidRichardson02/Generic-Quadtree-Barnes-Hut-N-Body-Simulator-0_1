//  NavigationalComponents.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#include "NavigationalComponents.hpp"





/**
 * Slider
 *
 * Default constructor for the Slider class.
 * Initializes the slider with no label, default position, size, and range.
 */
Slider::Slider()
{
	/// Set default values
	label = ""; // Set the label as an empty string
	rect = ofRectangle(); //  Initialize the rectangle representing the slider's position and size
	min = 0;
	max = 0;
	value = 0;
}


/**
 * Slider
 *
 * Constructor for the Slider class. Initializes the slider with a label, specific position, size, and range.
 *
 * @param _label: The label for the slider
 * @param _x: The x-coordinate of the slider's position
 * @param _y: The y-coordinate of the slider's position
 * @param _w: The width of the slider
 * @param _h: The height of the slider
 * @param _min: The minimum value of the slider
 * @param _max: The maximum value of the slider
 * @param _value: The initial value of the slider
 * @return None
 */
Slider::Slider(std::string _label, float _x, float _y, float _w, float _h, float _min, float _max, float &_value)
{
	/// Assign the label, minimum value, maximum value, and current value of the slider
	label = _label;
	min = _min;
	max = _max;
	value = &_value;
	
	/// Set the position and size of the slider
	rect.set(_x, _y, _w, _h);
}


/**
 * Slider
 *
 * Constructor for the Slider class. Initializes the slider with a label, specific position,
 * size, range, and precision of the value displayed in the Slider object.
 *
 * @param _label: The label for the slider
 * @param _x: The x-coordinate of the slider's position
 * @param _y: The y-coordinate of the slider's position
 * @param _w: The width of the slider
 * @param _h: The height of the slider
 * @param _min: The minimum value of the slider
 * @param _max: The maximum value of the slider
 * @param _value: The initial value of the slider
 * @param _precision: precision needed to fully capture the value displayed in the Slider object
 */
Slider::Slider(std::string _label, float _x, float _y, float _w, float _h, float _min, float _max, float &_value, int _precision)
{
	label = _label;
	rect.set(_x, _y, _w, _h);
	min = _min;
	max = _max;
	value = &_value;
	precision = _precision;
}


/**
 * setPosition
 * Sets the position of the slider while keeping the same width and height.
 *
 * @param rectPos: The new position of the slider
 */
void Slider::setPosition(ofVec2f rectPos)
{
	// Set the new position of the slider
	rect.set(rectPos.x, rectPos.y, rect.width, rect.height);
}


/**
 * draw
 *
 * Draws the slider on the screen. The slider is represented by a rectangle.
 * The current value of the slider is represented by a smaller filled rectangle inside the slider rectangle.
 * /
void Slider::draw()
{
	/// Set the color and draw the outline of the slider rectangle
	ofNoFill();
	ofSetColor(127);
	ofDrawRectangle(rect);
	
	/// Calculate the x-coordinate of the filled rectangle inside the slider rectangle
	float x = ofMap(*value, min, max, rect.x, rect.x + rect.width);
	
	/// Set the color and draw the filled rectangle
	ofSetColor(191);
	ofFill();
	ofDrawRectangle(x - 5, rect.y, 10, rect.height);
	
	/// Set the color and draw the label and the current value of the slider
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(label + ": " + ofToString(value, 3), rect.x + rect.width + 10, rect.y + rect.height * 0.5);
}
//*/
/*
 The draw function renders a slider UI element. It begins by drawing the
 slider’s outline, then calculates the fill rectangle based on the slider’s
 current value. Finally, it displays a textual label to convey both the
 slider’s name and numeric value, providing users with visual feedback.
 */
void Slider::draw()
{
	/// Step 1: Draw the outline of the slider
	// Switch to outline mode for shapes
	ofNoFill();
	// Use a medium-gray color
	ofSetColor(127);
	// Draw the bounding rectangle that represents the slider’s full range
	ofDrawRectangle(rect);
	
	/// Step 2: Map the current slider value to a screen position
	// “ofMap” re-maps the numerical value range to the slider’s rectangle width
	float x = ofMap(*value, min, max, rect.x, rect.x + rect.width);
	
	/// Step 3: Draw the filled portion of the slider
	// Switch to filled shapes, use a lighter gray color
	ofSetColor(191);
	ofFill();
	// Draw a small filled rectangle to illustrate the slider’s current value
	ofDrawRectangle(x - 5, rect.y, 10, rect.height);
	
	/// Step 4: Show the label and current numeric value
	// Switch the color to white
	ofSetColor(255, 255, 255);
	// Render text to the right of the slider’s bounding rectangle
	ofDrawBitmapString(label + ": " + ofToString(value, 3),
					   rect.x + rect.width + 10,
					   rect.y + rect.height * 0.5);
}


/**
 * mousePressed
 *
 * Handles the mouse pressed event. If the mouse is pressed inside the slider rectangle,
 * sets isDragging to true. Otherwise, sets isDragging to false.
 *
 * @param x: The x-coordinate of the mouse press
 * @param y: The y-coordinate of the mouse press
 * @param button: The mouse button that was pressed
 */
void Slider::mousePressed(int x, int y, int button)
{
	/// Check if the mouse press was inside the slider rectangle
	if (rect.inside(x, y))
	{
		/// If the mouse press was inside the slider rectangle, set isDragging to true
		isDragging = true;
	}
	else
	{
		/// If the mouse press was not inside the slider rectangle, set isDragging to false
		isDragging = false;
	}
}


/**
 * mouseDragged
 *
 * Handles the mouse dragged event. If the mouse is being dragged and isDragging is true, updates the value of the slider to correspond to the x-coordinate of the mouse.
 *
 * @param x: The x-coordinate of the mouse drag
 * @param y: The y-coordinate of the mouse drag
 * @param button: The mouse button that is being dragged
 */
void Slider::mouseDragged(int x, int y, int button)
{
	/// Check if the mouse is being dragged and isDragging is true
	if (isDragging)
	{
		/// If the mouse is being dragged and isDragging is true, calculate the new value of the slider
		float newValue = ofMap(x, rect.x, rect.x + rect.width, min, max, true);
		
		/// Update the value of the slider
		*value = newValue;
		
	}
}


/**
 * mouseReleased
 * Handles the mouse released event. Whenever the mouse is released, sets isDragging to false.
 *
 * @param x: The x-coordinate of the mouse release
 * @param y: The y-coordinate of the mouse release
 * @param button: The mouse button that was released
 */
void Slider::mouseReleased(int x, int y, int button)
{
	/// Whenever the mouse is released, set isDragging to false
	isDragging = false;
}

















/**
 * ~Table
 * Destructor for the Table class. Clears all the elements in the table.
 */
Table::~Table()
{
	/// Call the clear function to clear all the elements in the table
	clear();
}


/**
 * Table
 *
 * Constructor for the Table class. Initializes the table with a label, specific position, size, and opened state.
 *
 * @param _label: The label for the table
 * @param _x: The x-coordinate of the table's position
 * @param _y: The y-coordinate of the table's position
 * @param _w: The width of the table
 * @param _h: The height of the table
 * @param _isOpened: The opened state of the table
 */
Table::Table(std::string _label, float _x, float _y, float _w, float _h, bool _isOpened)
{
	/// Assign the label, opened state, and type of the table
	label = _label;
	isOpened = _isOpened;
	tableType = 0;  // Initialize the table type
	
	
	/// Initialize the rectangle
	labelRect = GetBoundingBox(label, _x, _y + _h*0.3125, 1, 1); // Set the rectangle representing the label's bounding box
	tableTab.set(ofVec2f(labelRect.x + labelRect.width + 10, _y - _h * 0.5 + 2), ofVec2f(_w, _h)); // Set the rectangle representing the table's position and size
	
	
	
	//scaleTable = 1;
	//tableOffset = 0;
}


/**
 * Table
 *
 * Constructor for the Table class. Initializes the table with a label, specific position, size, opened state, and type.
 *
 * @param _label: The label for the table
 * @param _x: The x-coordinate of the table's position
 * @param _y: The y-coordinate of the table's position
 * @param _w: The width of the table
 * @param _h: The height of the table
 * @param _isOpened: The opened state of the table
 * @param _tableType: The type of the table
 */
Table::Table(std::string _label, float _x, float _y, float _w, float _h, bool _isOpened, int _tableType)
{
	/// Assign the label, opened state, and type of the table
	label = _label;
	isOpened = _isOpened;
	tableType = _tableType;
	
	
	
	/// Initialize the rectangle
	labelRect = GetBoundingBox(label, _x, _y + _h*0.3125, 1, 1); // Set the rectangle representing the label's bounding box
	tableTab.set(ofVec2f(labelRect.x + labelRect.width + 10, _y - _h * 0.5 + 2), ofVec2f(_w, _h)); // Set the rectangle representing the table's position and size
	
	
	
	//scaleTable = 1;
	//tableOffset = 0;
}


//
/*
 Table::Table(std::string _label, float _x, float _y, float _w, float _h, bool _isOpened, int _scaleTable, int _tableOffset)
 {
 label = _label;
 isOpened = _isOpened;
 labelRect = GetBoundingBox(label, _x, _y + _h*0.3125, 1, 1);
 tableTab.set(ofVec2f(labelRect.x + labelRect.width + 10, _y - _h * 0.5 + 2), ofVec2f(_w, _h));
 scaleTable = _scaleTable;
 tableOffset = _tableOffset;
 tableType = 0;
 }
 //*/

/**
 * addSliderElement
 * Adds a slider element to the table.
 *
 * @param _sliderElement: A pointer to the slider element to be added
 */
void Table::addSliderElement(Slider* &_sliderElement)
{
	/// Add the slider element to the list of slider elements
	sliderElements.emplace_back(_sliderElement);
}


/**
 * addButtonElement
 * Adds a button element to the table.
 *
 * @param _buttonElement: A pointer to the button element to be added
 */
void Table::addButtonElement(Button* &_buttonElement)
{
	/// Add the button element to the list of button elements
	buttonElements.emplace_back(_buttonElement);
}


/**
 * addToggleElement
 * Adds a toggle element to the table.
 *
 * @param _toggleElement: A pointer to the toggle element to be added
 */
void Table::addToggleElement(Toggle* &_toggleElement)
{
	/// Add the toggle element to the list of toggle elements
	toggleElements.emplace_back(_toggleElement);
}


/**
 * addTextFieldElement
 * Adds a text field element to the table.
 *
 * @param _textFieldElement: A pointer to the text field element to be added
 */
void Table::addTextFieldElement(TextField* &_textFieldElement)
{
	/// Add the text field element to the list of text field elements
	textfieldElements.emplace_back(_textFieldElement);
}


void Table::addTooltipElement(Tooltip* &_toolTipElement)
{
	toolTipElements.emplace_back(_toolTipElement);
}



/**
 * tableElementsDimensions
 *
 * This function calculates and returns the dimensions of the table based on its current state and the elements it contains.
 * It iterates through each type of elements in the table(Slider, Button, Toggle, TextField, etc.). For each element,
 * it calculates the bounding box for the label and adjusts the width and height of the table accordingly.
 *
 * If the table is open, the function will iterate through each type of element in the
 * table(slider, button, toggle, textfield) and if the element's type is not empty,
 * it calculates dimensions to enclose at least the widest table contained within,
 * and if the tableHeight is less than a certain value, it adjusts the tableHeight.
 * If the table is closed, it calculates the bounding box for the label and adjusts the width and height of the table accordingly.
 * Lastly, if the tableType is 1, the function adjusts the width to be double and the height to be half.
 *
 * @return ofVec2f: The width and height of the table
 */
ofVec2f Table::tableElementsDimensions()
{
	/// Initialize tableHeight and tableWidth
	float tableHeight, tableWidth;
	
	/// If the table is open
	if(isOpened)
	{
		/// Check if there are any slider elements
		if (!sliderElements.empty())
		{
			/// Iterate through each slider element
			for (auto& slider : sliderElements)
			{
				ofRectangle labilRect = GetBoundingBox(slider->label, slider->rect.x, slider->rect.y, 1, 1); // Calculate the bounding box for the label
				
				
				/// Adjust the width of the table to enclose at least the widest table contained within
				if(labilRect.width > tableWidth || slider->rect.width > tableWidth)
				{
					tableWidth = std::max(labilRect.width, slider->rect.width);
				}
				
				tableHeight += labelRect.height; // Adjust the height of the table
			}
		}
		
		/// Repeat the process for button elements
		if (!buttonElements.empty())
		{
			for (auto& myButton : buttonElements)
			{
				ofRectangle labilRect = GetBoundingBox(myButton->label, myButton->rect.x, myButton->rect.y, 1, 1);
				if(labilRect.width > tableWidth || myButton->rect.width > tableWidth)
				{
					tableWidth = std::max(labilRect.width, myButton->rect.width);
				}
				tableHeight += labelRect.height;
			}
		}
		
		/// Repeat the process for toggle elements
		if (!toggleElements.empty())
		{
			for (auto& toggle : toggleElements)
			{
				ofRectangle labilRect = GetBoundingBox(toggle->label, toggle->rect.x, toggle->rect.y, 1, 1);
				if(labilRect.width > tableWidth || toggle->rect.width > tableWidth)
				{
					tableWidth = std::max(labilRect.width, toggle->rect.width);
				}
				tableHeight += labelRect.height;
			}
		}
		
		/// Repeat the process for textfield elements
		if (!textfieldElements.empty())
		{
			for (auto& textField : textfieldElements)
			{
				ofRectangle labilRect = GetBoundingBox(textField->label, textField->rect.x, textField->rect.y, 1, 1);
				if(labilRect.width > tableWidth || textField->rect.width > tableWidth)
				{
					tableWidth = std::max(labilRect.width, textField->rect.width);
				}
				tableHeight += labelRect.height;
			}
		}
		
		
		
		/// The acceptable table height is at least twice the height of the tab rectangle multiplied by the total number of elements
		/// If the tableHeight is less than the acceptable height, the tableHeight is set to be the determined acceptable height
		if(tableHeight < (tableTab.rect.height * 2 * (sliderElements.size() + buttonElements.size() + toggleElements.size())))
		{
			tableHeight = (tableTab.rect.height * 2 * (sliderElements.size() + buttonElements.size() + toggleElements.size()));
		}
	}
	
	/// Else the table is closed, and now the function calculates the bounding box for the label and adjusts the width and height of the table accordingly
	else
	{
		ofRectangle labilRect = GetBoundingBox(label, labelRect.x, labelRect.y, 1, 1); // Calculate bounding box for the label
		
		/// Adjust width and height of the table accordingly
		tableHeight = labilRect.height;
		if(labilRect.width > tableWidth || labelRect.width > tableWidth)
		{
			tableWidth = std::max(labilRect.width, labelRect.width);
		}
	}
	
	
	/// Adjusts the width and height of the table based on the table type
	if(tableType == 1)
	{
		tableWidth *= 2;
		tableHeight *= 0.5;
	}
	return ofVec2f(tableWidth, tableHeight);
}




/**
 * Adjusts the layout of elements within the tableRect based on their dimensions.
 * /
void Table::layoutElements()
{
	float currentY = tableRect.y; // Start y-coordinate within the tableRect
	float elementWidth = tableRect.width; // All elements will match the width of tableRect
	
	// Calculate the space needed for each type of element and adjust their position and size
	for (auto& slider : sliderElements) 
	{
		float elementHeight = slider->rect.height; // Preserving original element height
		slider->rect.set(tableRect.x, currentY, elementWidth, elementHeight);
		currentY += elementHeight; // Move the next element down
	}
	
	for (auto& button : buttonElements)
	{
		float elementHeight = button->rect.height; // Preserving original element height
		button->rect.set(tableRect.x, currentY, elementWidth, elementHeight);
		currentY += elementHeight; // Move the next element down
	}
	
	for (auto& toggle : toggleElements)
	{
		float elementHeight = toggle->rect.height; // Preserving original element height
		toggle->rect.set(tableRect.x, currentY, elementWidth, elementHeight);
		currentY += elementHeight; // Move the next element down
	}
	
	for (auto& textField : textfieldElements)
	{
		float elementHeight = textField->rect.height; // Preserving original element height
		textField->rect.set(tableRect.x, currentY, elementWidth, elementHeight);
		currentY += elementHeight; // Move the next element down
	}
}
//*/
/*
 The layoutElements function systematically arranges the Table’s
 UI components—sliders, buttons, toggles, and text fields—within
 the rectangular region defined by tableRect. It preserves each
 element’s original height, stacks them vertically in the order
 they appear, and ensures all elements match tableRect’s width.
 As a result, the Table presents a clean, aligned interface
 with proportional spacing for its child elements.
 */
void Table::layoutElements()
{
	/// Step 1: Initialize vertical position and fixed width
	float currentY = tableRect.y; // Starting y-position at the top of tableRect
	float elementWidth = tableRect.width; // Enforce consistent width for all elements
	
	/// Step 2: Position slider elements
	// Each slider retains its own height; subsequent sliders are stacked below
	for (auto& slider : sliderElements)
	{
		float elementHeight = slider->rect.height; // Preserve the slider's original height
		slider->rect.set(tableRect.x, currentY, elementWidth, elementHeight);
		currentY += elementHeight; // Shift the y-position for the next element
	}
	
	/// Step 3: Position button elements
	// Same stacking logic is applied to buttons
	for (auto& button : buttonElements)
	{
		float elementHeight = button->rect.height; // Preserve the button's original height
		button->rect.set(tableRect.x, currentY, elementWidth, elementHeight);
		currentY += elementHeight; // Shift the y-position for the next element
	}
	
	/// Step 4: Position toggle elements
	// Toggles also follow the established vertical placement strategy
	for (auto& toggle : toggleElements)
	{
		float elementHeight = toggle->rect.height; // Preserve the toggle's original height
		toggle->rect.set(tableRect.x, currentY, elementWidth, elementHeight);
		currentY += elementHeight; // Shift the y-position for the next element
	}
	
	/// Step 5: Position text field elements
	// Text fields share the same logic to maintain layout consistency
	for (auto& textField : textfieldElements)
	{
		float elementHeight = textField->rect.height; // Preserve the text field's original height
		textField->rect.set(tableRect.x, currentY, elementWidth, elementHeight);
		currentY += elementHeight; // Shift the y-position for the next element
	}
}



/**
 * setPosition
 * Sets the position of the table. Adjusts the position of the label and tableTab according to the new position.
 *
 * @param rectPos: The new position of the table
 */
void Table::setPosition(ofVec2f rectPos)
{
	/// Calculates the bounding box for the label based on the new position
	labelRect = GetBoundingBox(label, rectPos.x, rectPos.y + tableTab.rect.height * 0.375, 1, 1);
	
	/// Sets the position of the tableTab based on the new position and the dimensions of the labelRect
	tableTab.setPosition(ofVec2f(labelRect.x + labelRect.width + 10, rectPos.y - tableTab.rect.height * 0.5 + 2));
	
	layoutElements();
}



void Table::callbackUpdate()
{
	if(!toggleElements.empty())
	{
		for(auto& toggle : toggleElements)
		{
			toggle->callbackUpdate();
		}
	}
}


/**
 * draw
 * This function is responsible for drawing the table and its elements. It first sets the color and draws the label.
 * Then it draws the tableTab. If the table is opened, it calculates the dimensions of the table and determines the size
 * and position of the opened table rectangle based on the position of the tableTab. It then draws the opened table rectangle.
 * After that, it calculates the y position and height of the table elements and draws and positions the slider elements,
 * textField elements, button elements, and toggle elements accordingly.
 * /
void Table::draw()
{
	// Get the window dimensions
	float xWind = ofGetWidth(), yWind = ofGetHeight();
	
	// Set color to white
	ofSetColor(255, 255, 255);
	
	// Draw the label
	ofDrawBitmapString(label, labelRect.x, labelRect.y);
	
	// Set color to white with 50% transparency
	ofSetColor(255, 255, 255, 127);
	
	// Draw the tableTab
	tableTab.draw();
	
	
	// If the table is opened
	if (isOpened)
	{
		//
		/*
		 if (!textfieldElements.empty())
		 {
		 for (auto& textField : textfieldElements)
		 {
		 if(textField->warningMode)
		 {
		 tableOffset = textField->rect.height;
		 }
		 else
		 {
		 tableOffset = 0;
		 }
		 }
		 }
		 //* /
		
		
		
		/// Calculate the dimensions of the table
		ofVec2f tableBounds = tableElementsDimensions();
		//float scaleHeight = scaleTable + (1*scaleTable);
		//scaleHeight = (scaleHeight/(scaleTable+1));
		float totalHeight = tableBounds.y; //(tableTab.rect.height * 2 * (sliderElements.size() + buttonElements.size() + toggleElements.size()));  // Determine the size and position of the opened table rectangle
		float openedTableWidth = tableBounds.x;//tableTab.rect.width * 12;
		float openedTableHeight;
		
		
		
		
		/// Determine the size and position of the opened table rectangle
		openedTableHeight = totalHeight;
		
		float openedTableX, openedTableY;
		// Determine the position of the opened table rectangle based on the position of the tableTab
		// The four conditions correspond to the four quadrants of the window
		if (tableTab.rect.x < xWind * 0.5 && tableTab.rect.y < yWind * 0.5) //top left
		{
			openedTableX = tableTab.rect.x + tableTab.rect.width + 15;
			openedTableY = tableTab.rect.y + tableTab.rect.height * 0.5;
		}
		else if (tableTab.rect.x >= xWind * 0.5 && tableTab.rect.y < yWind * 0.5) //top right
		{
			openedTableX = tableTab.rect.x - openedTableWidth - tableTab.rect.width;
			openedTableY = tableTab.rect.y + tableTab.rect.height*2;
		}
		else if (tableTab.rect.x < xWind * 0.5 && tableTab.rect.y >= yWind * 0.5) //bottom left
		{
			openedTableX = tableTab.rect.x + tableTab.rect.width + 15;
			openedTableY = tableTab.rect.y - openedTableHeight - tableTab.rect.height * 2;
		}
		else if (tableTab.rect.x >= xWind * 0.5 && tableTab.rect.y >= yWind * 0.5) //bottom right
		{
			openedTableX = tableTab.rect.x - openedTableWidth - tableTab.rect.width;
			openedTableY = tableTab.rect.y - openedTableHeight - tableTab.rect.height;
			openedTableWidth = openedTableWidth * 1.75;
		}
		
		
		/// Draw the opened table rectangle
		ofFill();
		ofSetColor(255, 255, 255, 18.75);
		ofDrawRectangle(openedTableX, openedTableY - tableTab.rect.height, openedTableWidth * 1.25 , openedTableHeight * 1.05);
		ofNoFill();
		
		
		
		/// Calculate the y position and height of the table elements
		float elementHeight = openedTableHeight / (sliderElements.size() + buttonElements.size() + toggleElements.size());
		float yPos = openedTableY;
		
		
		
		/// Draw and position the slider elements
		for (auto& slider : sliderElements)
		{
			slider->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos));
			slider->draw();
			yPos += elementHeight;
		}
		yPos += 5;
		
		
		/// Draw and position the textField elements
		for (auto& textField : textfieldElements)
		{
			textField->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos));
			textField->draw();
			yPos += elementHeight+35;
		}
		
		
		/// Draw and position the button elements
		for (auto& button : buttonElements)
		{
			button->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos ));
			button->draw();
			yPos += elementHeight;
		}
		
		
		/// Draw and position the toggle elements
		int i = 0;
		for (auto& toggle : toggleElements)
		{
			i++;
			if(!textfieldElements.empty())
			{
				if(i>3)
				{
					toggle->setPosition(ofVec2f((openedTableX + tableTab.rect.width)*1.625, (yPos - elementHeight*3) ));
				}
				else
				{
					toggle->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos ));
				}
			}
			else
			{
				toggle->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos ));
			}
			toggle->draw();
			yPos += elementHeight;
		}
		
		
		/// Draw and position the button elements
		for (auto& toolTip : toolTipElements)
		{
			//toolTip->setPosition(openedTableX + tableTab.rect.width, yPos);
			toolTip->draw();
			//yPos += elementHeight;
		}
	}
}
//*/
/*
 The draw function orchestrates the visual presentation of a Table object
 within the OpenFrameworks environment. It initially draws the table’s label
 and tab, then conditionally calculates, sizes, and positions a background
 rectangle if the table is open. After establishing this backdrop, the
 function arranges and renders any sliders, text fields, buttons, and toggles
 within the Table. The final layout logic adapts to screen quadrants, ensuring
 the table elements unfold in a suitable direction without clutter.
 */
void Table::draw()
{
	/// Step 1: Render the label and table tab
	// Get the window dimensions for any positional logic
	float xWind = ofGetWidth(), yWind = ofGetHeight();
	
	// Set rendering color to white
	ofSetColor(255, 255, 255);
	// Draw the table’s label text at the label rectangle
	ofDrawBitmapString(label, labelRect.x, labelRect.y);
	
	// Switch to white with 50% opacity
	ofSetColor(255, 255, 255, 127);
	// Draw the visual tab associated with the Table
	tableTab.draw();
	
	/// Step 2: Check if this table is currently open
	if (isOpened)
	{
		/// Step 2a: Compute table dimensions
		// Gather spatial bounds from all contained elements
		ofVec2f tableBounds = tableElementsDimensions();
		float totalHeight = tableBounds.y;
		float openedTableWidth = tableBounds.x;
		float openedTableHeight = totalHeight;
		
		/// Step 2b: Determine drawing coordinates based on screen quadrant
		float openedTableX, openedTableY;
		if (tableTab.rect.x < xWind * 0.5 && tableTab.rect.y < yWind * 0.5)
		{
			// Top-left quadrant
			openedTableX = tableTab.rect.x + tableTab.rect.width + 15;
			openedTableY = tableTab.rect.y + tableTab.rect.height * 0.5;
		}
		else if (tableTab.rect.x >= xWind * 0.5 && tableTab.rect.y < yWind * 0.5)
		{
			// Top-right quadrant
			openedTableX = tableTab.rect.x - openedTableWidth - tableTab.rect.width;
			openedTableY = tableTab.rect.y + tableTab.rect.height * 2;
		}
		else if (tableTab.rect.x < xWind * 0.5 && tableTab.rect.y >= yWind * 0.5)
		{
			// Bottom-left quadrant
			openedTableX = tableTab.rect.x + tableTab.rect.width + 15;
			openedTableY = tableTab.rect.y - openedTableHeight - tableTab.rect.height * 2;
		}
		else
		{
			// Bottom-right quadrant
			openedTableX = tableTab.rect.x - openedTableWidth - tableTab.rect.width;
			openedTableY = tableTab.rect.y - openedTableHeight - tableTab.rect.height;
			// Increase width for bottom-right layout
			openedTableWidth *= 1.75;
		}
		
		/// Step 2c: Draw the background rectangle for the opened table
		ofFill();
		// Very light fill for the table’s backdrop
		ofSetColor(255, 255, 255, 18.75);
		// Render a slightly scaled rectangle
		ofDrawRectangle(openedTableX,
						openedTableY - tableTab.rect.height,
						openedTableWidth * 1.25,
						openedTableHeight * 1.05);
		ofNoFill();
		
		/// Step 2d: Lay out table elements (sliders, text fields, buttons, toggles)
		// Compute available vertical space for each element
		float elementHeight = openedTableHeight
		/ (sliderElements.size()
		   + buttonElements.size()
		   + toggleElements.size());
		float yPos = openedTableY;
		
		/// Step 2d-i: Position and draw slider elements
		for (auto& slider : sliderElements)
		{
			// Shift the slider’s position just right of the table tab
			slider->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos));
			slider->draw();
			yPos += elementHeight;
		}
		// Slight padding after sliders
		yPos += 5;
		
		/// Step 2d-ii: Position and draw textField elements
		for (auto& textField : textfieldElements)
		{
			textField->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos));
			textField->draw();
			yPos += elementHeight + 35;
		}
		
		/// Step 2d-iii: Position and draw button elements
		for (auto& button : buttonElements)
		{
			button->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos));
			button->draw();
			yPos += elementHeight;
		}
		
		/// Step 2d-iv: Position and draw toggle elements
		int i = 0;
		for (auto& toggle : toggleElements)
		{
			i++;
			// If text fields exist and we exceed 3 toggles, shift to a second column
			if(!textfieldElements.empty())
			{
				if(i > 3)
				{
					toggle->setPosition(
										ofVec2f((openedTableX + tableTab.rect.width) * 1.625,
												(yPos - elementHeight * 3)));
				}
				else
				{
					toggle->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos));
				}
			}
			else
			{
				toggle->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos));
			}
			toggle->draw();
			yPos += elementHeight;
		}
		
		/// Step 2d-v: Draw any tooltip elements, if present
		for (auto& toolTip : toolTipElements)
		{
			// The toolTip might manage its own position and just needs drawing
			toolTip->draw();
		}
	}
}






void Table::exit()
{
	clear();
	
	
	if (!sliderElements.empty())
	{
		for(int i=0; i < sliderElements.size();i++)
		{
			if(sliderElements[i] != nullptr)
			{
				sliderElements.erase(sliderElements.begin()+i);
				
				delete sliderElements[i];
			}
		}
		sliderElements.clear();
	}
	
	if (!buttonElements.empty())
	{
		for(int i=0; i < buttonElements.size();i++)
		{
			if(buttonElements[i] != nullptr)
			{
				buttonElements.erase(buttonElements.begin()+i);
				
				delete buttonElements[i];
			}
		}
		buttonElements.clear();
	}
	
	
	if (!toggleElements.empty())
	{
		for(int i=0; i < toggleElements.size();i++)
		{
			if(toggleElements[i] != nullptr)
			{
				toggleElements.erase(toggleElements.begin()+i);
				
				delete toggleElements[i];
			}
		}
		toggleElements.clear();
	}
	
	if (!textfieldElements.empty())
	{
		for(int i=0; i < textfieldElements.size();i++)
		{
			if(textfieldElements[i] != nullptr)
			{
				textfieldElements.erase(textfieldElements.begin()+i);
				
				delete textfieldElements[i];
			}
		}
		textfieldElements.clear();
	}
	
}




void Table::clear()
{
	if (!sliderElements.empty())
	{
		for(int i=0; i < sliderElements.size();i++)
		{
			if(sliderElements[i] != nullptr)
			{
				sliderElements.erase(sliderElements.begin()+i);
			}
		}
		sliderElements.clear();
	}
	
	if (!buttonElements.empty())
	{
		for(int i=0; i < buttonElements.size();i++)
		{
			if(buttonElements[i] != nullptr)
			{
				buttonElements.erase(buttonElements.begin()+i);
			}
		}
		buttonElements.clear();
	}
	
	
	if (!toggleElements.empty())
	{
		for(int i=0; i < toggleElements.size();i++)
		{
			if(toggleElements[i] != nullptr)
			{
				toggleElements.erase(toggleElements.begin()+i);
			}
		}
		toggleElements.clear();
	}
	
	if (!textfieldElements.empty())
	{
		for(int i=0; i < textfieldElements.size();i++)
		{
			if(textfieldElements[i] != nullptr)
			{
				textfieldElements.erase(textfieldElements.begin()+i);
			}
		}
		textfieldElements.clear();
	}
	
	if (!toolTipElements.empty())
	{
		for(int i=0; i < toolTipElements.size();i++)
		{
			if(toolTipElements[i] != nullptr)
			{
				toolTipElements.erase(toolTipElements.begin()+i);
			}
		}
		toolTipElements.clear();
	}
}

void Table::keyReleased(int key)
{
	if (!textfieldElements.empty())
	{
		for (auto& textField : textfieldElements)
		{
			textField->keyReleased(key);
		}
	}
}

void Table::mousePressed(int x, int y, int button)
{
	tableTab.mousePressed(x, y, button);
	
	if (tableTab.rect.inside(x, y))
	{
		isOpened = !isOpened;
	}
	
	
	
	if (isOpened)
	{
		if (!sliderElements.empty())
		{
			for (auto& slider : sliderElements)
			{
				slider->mousePressed(x, y, button);
			}
		}
		
		if (!buttonElements.empty())
		{
			for (auto& myButton : buttonElements)
			{
				myButton->mousePressed(x, y, button);
			}
		}
		
		
		if (!toggleElements.empty())
		{
			for (auto& toggle : toggleElements)
			{
				toggle->mousePressed(x, y, button);
			}
		}
		
		
		if (!textfieldElements.empty())
		{
			for (auto& textField : textfieldElements)
			{
				textField->mousePressed(x, y, button);
			}
		}
	}
}

void Table::mouseDragged(int x, int y, int button)
{
	if (!sliderElements.empty())
	{
		for (auto& slider : sliderElements)
		{
			slider->mouseDragged(x, y, button);
		}
	}
}

void Table::mouseReleased(int x, int y, int button)
{
	if (!sliderElements.empty())
	{
		for (auto& slider : sliderElements)
		{
			slider->mouseReleased(x, y, button);
		}
	}
	
	if (!buttonElements.empty())
	{
		for (auto& myButton : buttonElements)
		{
			myButton->mouseReleased(x, y, button);
		}
	}
	
	
	if (!textfieldElements.empty())
	{
		for (auto& textField : textfieldElements)
		{
			textField->mouseReleased(x, y, button);
		}
	}
}













TableManager::TableManager()
{
	simulationMode = 0;
	galaxyCreationMode = false;
	isOpened = false;
}



TableManager::TableManager(int _mode, std::string _label)
{
	simulationMode = _mode;
	label = _label;
	
	galaxyCreationMode = false;
	isOpened = false;
	
	if(simulationMode == 0)
	{
		
	}
	
	labelRect = GetBoundingBox(label, 0 + ofGetWidth() * 0.01, 0 + ofGetHeight() * 0.01, 1, 1);
	rect.set(labelRect.x + labelRect.width + 10, 25, 200, 200); // `10` is a space between label and rect
	
	
	
	
}

TableManager::TableManager(int _mode, std::string _label, float _x, float _y, float _w, float _h)
{
	simulationMode = _mode;
	label = _label;
	
	galaxyCreationMode = false;
	isOpened = false;
	
	if(simulationMode == 0)
	{
		
	}
	
	labelRect = GetBoundingBox(label, _x, _y + _h*0.3125, 1, 1);
	rect.set(labelRect.x + labelRect.width + 10, _y - _h * 0.5 + 2, _w, _h); // `10` is a space between label and rect
	
	
}



TableManager::~TableManager()
{
	clear();
}



//
/*
void TableManager::setPosition(ofVec2f rectPos) //adjust position and size of entire table manager based on table elements, then adjust table elements to match tableManager
{
	/**
	 * reposition tables based on which table are currently open
	 *
	 * grow or shrink table manager's menu to always enclose all tables (excluding special cases(galaxy creator))
	 *
	 * set positions and size of all tables to keep them equidistant, equally scaled, and within table manager
	 *
	 *
	 *
	 * do the above steps every time a table is opened, everytime a table is closed, and everytime the window is resized
	 *
	 * when the table is closed, set the position and size of all tables back to how they originally were (be sure to account for any change in window size)
	 
	 * /
	
	labelRect = GetBoundingBox(label, rectPos.x, rectPos.y + rect.height * 0.375, 1, 1);
	rect.x = labelRect.x + labelRect.width + 10;
	rect.y = rectPos.y - rect.height * 0.5 + 2;
	
	
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->draw();
		}
	}
}
//*/
/*
 The setPosition function recalculates the TableManager’s bounding area and
 positions its label as well as any contained tables. By accepting a new
 position vector (rectPos), it aligns the manager’s coordinates based on the
 label’s bounding box and shifts the manager’s top-left corner accordingly.
 Any tables currently stored in the manager (and deemed open) are then redrawn
 to reflect the updated layout.
 
 @param rectPos: The new position vector to base the TableManager’s layout on.
 @return void
 */
void TableManager::setPosition(ofVec2f rectPos)
{
	/// Step 1: Recalculate label bounding box based on the given position
	// Compute how the label should be drawn relative to rectPos
	labelRect = GetBoundingBox(label, rectPos.x, rectPos.y + rect.height * 0.375, 1, 1);
	
	// Align the main rectangle’s x-position to the right edge of the label, plus a margin
	rect.x = labelRect.x + labelRect.width + 10;
	// Lift the y-position to keep the manager slightly above the midpoint
	rect.y = rectPos.y - rect.height * 0.5 + 2;
	
	/// Step 2: Redraw the open tables within the manager
	if (!tables.empty())
	{
		// Iterate through each table and invoke its draw() routine
		for (auto& table : tables)
		{
			table->draw();
		}
	}
}

//
/*
void TableManager::draw()
{
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(label, labelRect.x, labelRect.y);
	
	//need all visualization table inside one table manager
	
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->callbackUpdate();
		}
	}
	
	
	
	//depending on which tables are open, the others need to move around to make room
	// Draw the opened table rectangle
	if(isOpened)
	{
		ofFill();
		ofSetColor(222, 222, 222, 37.5);
		ofDrawRectangle(rect);
		
		
		
		
		if (!tables.empty())
		{
			
			for (auto& table : tables)
			{
				if(table->tableType == 2)
				{
					// Special case handling for galaxy creation
				}
				table->draw();
			}
		}
		
		
		
		
		ofNoFill();
		ofSetColor(255, 255, 255, 77);
		ofSetLineWidth(2);
		ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
		ofSetLineWidth(1);
		ofDrawLine(rect.x + 2, rect.y + rect.height * 0.5, rect.x + rect.width - 2, rect.y + rect.height * 0.5);
	}
	else
	{
		ofNoFill();
		ofSetColor(255, 255, 255, 77);
		ofSetLineWidth(2);
		ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
		ofSetLineWidth(1);
		ofDrawLine(rect.x + rect.width * 0.5, rect.y + 2, rect.x + rect.width * 0.5, rect.y + rect.height - 2);
		ofDrawLine(rect.x + 2, rect.y + rect.height * 0.5, rect.x + rect.width - 2, rect.y + rect.height * 0.5);
	}
}
//*/

/*
 The draw function manages the rendering of the TableManager’s label and
 the relevant tables it holds. It begins by drawing the manager’s label
 at a designated position. Next, it calls each table’s callbackUpdate
 before deciding how to render the visual layout based on whether the
 table manager is in an opened or closed state. If opened, a semi-transparent
 rectangle is drawn behind all tables, which are then individually rendered.
 If closed, a minimal bounding box with cross lines is displayed instead.
 This function ensures visual consistency and an up-to-date display
 of the included tables’ current states.
 */
void TableManager::draw()
{
	/// Step 1: Draw the label for this TableManager
	// Set the drawing color (white)
	ofSetColor(255, 255, 255);
	// Draw the label string at the coordinates of the label rectangle
	ofDrawBitmapString(label, labelRect.x, labelRect.y);
	
	/// Step 2: Update each table’s state before rendering
	// Only proceed if there are any tables stored
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			// Fire a table-specific update callback
			table->callbackUpdate();
		}
	}
	
	/// Step 3: Render differently if TableManager is open or closed
	// If open, display a background rectangle and allow tables to draw themselves
	if (isOpened)
	{
		/// Step 3a: Draw a semi-transparent filled background for open manager
		ofFill();  // Switch to filled shape drawing
				   // Light gray tone with low opacity
		ofSetColor(222, 222, 222, 37.5);
		// Draw the manager’s bounding rectangle
		ofDrawRectangle(rect);
		
		/// Step 3b: Draw each table’s content if any tables exist
		if (!tables.empty())
		{
			for (auto& table : tables)
			{
				// Check if the table is a certain type (e.g., for galaxy creation)
				if (table->tableType == 2)
				{
					// Special case handling can go here
				}
				// Each table draws itself
				table->draw();
			}
		}
		
		/// Step 3c: Outline the bounding rectangle with a half-opacity stroke
		ofNoFill(); // Switch back to outline stroke
		ofSetColor(255, 255, 255, 77);
		// Make the outline thicker temporarily
		ofSetLineWidth(2);
		ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
		// Reset line width and draw a dividing line
		ofSetLineWidth(1);
		ofDrawLine(rect.x + 2, rect.y + rect.height * 0.5,
				   rect.x + rect.width - 2, rect.y + rect.height * 0.5);
	}
	else
	{
		/// Step 3d: If not opened, outline only
		ofNoFill();
		ofSetColor(255, 255, 255, 77);
		ofSetLineWidth(2);
		// Draw the manager’s bounding rectangle
		ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
		ofSetLineWidth(1);
		// Draw cross lines for closed state
		ofDrawLine(rect.x + rect.width * 0.5, rect.y + 2,
				   rect.x + rect.width * 0.5, rect.y + rect.height - 2);
		ofDrawLine(rect.x + 2, rect.y + rect.height * 0.5,
				   rect.x + rect.width - 2, rect.y + rect.height * 0.5);
	}
}




















//
/*
void TableManager::repositionTables()
{
	int tableManagerHeight = 0, tableManagerWidth = 0;
	
	
	if (!tables.empty())
	{
		int margin = 10;  // Margin between tables
		int currentX = margin;  // Start position x
		int currentY = margin;  // Start position y
		int maxHeightInRow = 0;  // Track the maximum height in the current row
		
		float screenWidth = ofGetWidth();  // Get the current screen width from openFrameworks
		
		// Iterate over all tables to set their new positions
		for (auto& table : tables)
		{
			if (!table->isOpened) 
			{
				continue;  // Skip tables that are not active
			}
			
			
			if(table->labelRect.width > tableManagerWidth || table->tableTab.rect.width > tableManagerWidth) //adjust width of table manager to enclose at least the widest table contained within
			{
				tableManagerWidth = std::max(table->labelRect.width, table->tableTab.rect.width);
			}
			
			ofVec2f tableSize = table->tableElementsDimensions();  // Assume this method returns the width and height of the table
			
			// Check if adding this table would exceed the screen width, i.e., if the current table would fit in the current row
			if (currentX + tableSize.x  + margin > screenWidth)
			{
				// Move to the next row
				currentX = margin;
				currentY += maxHeightInRow + margin;
				maxHeightInRow = 0;
			}
			
			// Set the table's new position
			table->setPosition(ofVec2f(currentX, currentY));
			
			// Update currentX and maxHeightInRow for the next table
			currentX += tableSize.x + margin;
			if (tableSize.y > maxHeightInRow)
			{
				maxHeightInRow = tableSize.y;
			}
			
			
			//
			if(table->isOpened)
			{
				tableManagerHeight += table->tableTab.rect.height;
			}
			else
			{
				
			}
			tableManagerHeight += table->labelRect.height;
		}
	}
	
	rect.height += tableManagerHeight;
	rect.width = tableManagerWidth;
}
//*/





/*
 The repositionTables function orchestrates a systematic placement of all
 currently active ("opened") tables in a spatial layout. By scanning and
 positioning each table sequentially, it packs them automatically into rows
 and columns according to the screen width constraints, ensuring that each
 table has enough space and does not overflow to the right. This arrangement
 also accumulates an overall width and height, enabling the surrounding
 container (the table manager) to be sized appropriately for display.
 */

void TableManager::repositionTables()
{
	/// Step 1: Initialize accumulators and check if there are any tables at all
	// Initialize overall width/height for the table manager
	// Only proceed if tables are present
	int tableManagerHeight = 0, tableManagerWidth = 0;
	
	if (!tables.empty())
	{
		/// Step 2: Prepare basic layout parameters and get screen width
		// margin => spacing between consecutively placed tables
		// currentX/currentY => track the current drawing position
		// maxHeightInRow => track tallest table in the current row
		int margin = 10;  // Spacing between tables
		int currentX = margin;  // Horizontal start position
		int currentY = margin;  // Vertical start position
		int maxHeightInRow = 0; // Tracks tallest table in the current row
		
		float screenWidth = ofGetWidth();  // Retrieve current display width
		
		/// Step 3: Iterate over tables and place only those that are opened
		// If a table is closed, skip it
		for (auto& table : tables)
		{
			if (!table->isOpened)
			{
				continue;  // Skip non-active tables
			}
			
			/// Step 4: Adjust manager width if current table is wider
			// Compare the table's label width vs. tab width
			if (table->labelRect.width > tableManagerWidth
				|| table->tableTab.rect.width > tableManagerWidth)
			{
				tableManagerWidth = std::max(table->labelRect.width,
											 table->tableTab.rect.width);
			}
			
			// Retrieve the table's width and height for layout calculations
			ofVec2f tableSize = table->tableElementsDimensions();
			
			/// Step 5: Check if the next table would overflow the right edge
			// If so, move to the next row
			if (currentX + tableSize.x + margin > screenWidth)
			{
				currentX = margin;
				currentY += maxHeightInRow + margin;
				maxHeightInRow = 0;
			}
			
			/// Step 6: Position the table and update layout metrics
			// Move the table to the calculated position
			table->setPosition(ofVec2f(currentX, currentY));
			
			// Shift to the right for the next table
			currentX += tableSize.x + margin;
			// Keep track of the maximum row height
			if (tableSize.y > maxHeightInRow)
			{
				maxHeightInRow = tableSize.y;
			}
			
			/// Step 7: Accumulate height for the table manager
			// If a table is open, include tableTab height (or labelRect height otherwise)
			if (table->isOpened)
			{
				tableManagerHeight += table->tableTab.rect.height;
			}
			tableManagerHeight += table->labelRect.height;
		}
	}
	
	/// Step 8: Finalize the table manager's overall dimensions
	// Increase its height and set its width accordingly
	rect.height += tableManagerHeight;
	rect.width = tableManagerWidth;
}

























void TableManager::exit()
{
	if (!tables.empty())
	{
		for(int i=0; i < tables.size();i++)
		{
			if(tables[i] != nullptr)
			{
				tables[i]->clear();
				//tables[i]->exit();
				
				tables[i] = nullptr;
			}
		}
		tables.clear();
	}
}



void TableManager::clear()
{
	if (!tables.empty())
	{
		for(int i=0; i < tables.size();i++)
		{
			if(tables[i] != nullptr)
			{
				tables.erase(tables.begin()+i);
			}
		}
		tables.clear();
	}
}

void TableManager::keyReleased(int key)
{
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->keyReleased(key);
		}
	}
}

void TableManager::mousePressed(int x, int y, int button)
{
	if (rect.inside(x, y))
	{
		isOpened = !isOpened;
	}
	
	
	
	if (isOpened)
	{
		if(!tables.empty())
		{
			for (auto& table : tables)
			{
				table->mousePressed(x, y, button);
				
				
				if(table->tableType == 2)
				{
					if(table->isOpened)
					{
						galaxyCreationMode = true;
					}
					else
					{
						galaxyCreationMode = false;
					}
				}
			}
		}
	}
}

void TableManager::mouseDragged(int x, int y, int button)
{
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->mouseDragged(x, y, button);
		}
	}
}

void TableManager::mouseReleased(int x, int y, int button)
{
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->mouseReleased(x, y, button);
		}
	}
}








void TableManager::addTable(Table* &table)
{
	tables.emplace_back(table);
}




void TableManager::adjustTableManagerDimensions(float newHeight)
{
	// Set the height of the TableManager to include all tables and some margin
	rect.setHeight(newHeight);
	rect.setWidth(ofGetWidth() - 2 * 20); // margin==20 on either side
}


void TableManager::galaxyMode()
{
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			
			if(table->tableType == 2 && table->isOpened) //this means that the galaxy special case table is opened, in which case, close all other tables except table manager
			{
				table->isOpened = true;
				galaxyCreationMode = true;
			}
			else
			{
				galaxyCreationMode = false;
			}
		}
	}
	
	
	if(galaxyCreationMode)
	{
		for (auto& table : tables)
		{
			if(!(table->tableType == 2)) //this means that the galaxy special case table is opened, in which case, close all other tables except table manager
			{
				table->isOpened = false;
			}
			
		}
	}
}









// Constructor that initializes a RectangularGridDragSelection with a label, specific position, and size
RectangularGridDragSelection::RectangularGridDragSelection(std::string label, float _x, float _y, float _w, float _h)
: gridLabel(label), gridBounds(_x, _y, _w, _h), isPressed(false), isDragging(false), granularity(_w * 0.005) {}



// Constructor that initializes a RectangularGridDragSelection with a label, specific position, size, and min/max values for the slider
RectangularGridDragSelection::RectangularGridDragSelection(std::string label, float _x, float _y, float _w, float _h, float _min, float _max)
: gridLabel(label), gridBounds(_x, _y, _w, _h), min(_min), max(_max), isPressed(false), isDragging(false) {}




/**
 * setPosition
 * Sets the position of the top left corner of RectangularGridDragSelection while keeping the same width and height.
 *
 * @param rectPos: The new position of the slider
 * /
void RectangularGridDragSelection::setPosition(ofVec2f rectPos)
{
	// Set the new position of the slider
	gridBounds.set(rectPos.x, rectPos.y, gridBounds.width, gridBounds.height);
	rectangleGranularitySlider.setPosition(ofVec2f(rectPos.x, rectPos.y + gridBounds.getHeight() + 10));
	gridGranularitySubmit.setPosition(ofVec2f(rectPos.x, rectPos.y + gridBounds.getHeight() + 40));
	updateGridCells();
}
//*/
/*
 * Big picture summary:
 * The setPosition function repositions the RectangularGridDragSelection by altering its
 * top-left corner coordinates while preserving its width and height. It also repositions
 * related UI components to maintain their relative alignment, and finally triggers an
 * update to ensure the grid’s cells remain accurately mapped.
 */

/**
 * setPosition
 * Sets the position of the top left corner of RectangularGridDragSelection while keeping the same width and height.
 *
 * @param rectPos: The new position of the slider
 */
void RectangularGridDragSelection::setPosition(ofVec2f rectPos)
{
	/// 1. Update bounding rectangle with new x,y coordinates while preserving existing dimensions.
	// Overwrite the bounding rectangle values, maintaining the original width and height
	gridBounds.set(rectPos.x, rectPos.y, gridBounds.width, gridBounds.height);
	
	/// 2. Reposition the rectangleGranularitySlider a fixed distance below the updated bounding rectangle.
	// Offset the slider based on the bounding box height to maintain layout consistency
	rectangleGranularitySlider.setPosition(ofVec2f(rectPos.x, rectPos.y + gridBounds.getHeight() + 10));
	
	/// 3. Reposition the gridGranularitySubmit button an additional distance below the slider.
	// Offset the submit button further down to avoid overlap
	gridGranularitySubmit.setPosition(ofVec2f(rectPos.x, rectPos.y + gridBounds.getHeight() + 40));
	
	/// 4. Refresh the grid cells to reflect the new bounding rectangle position.
	// Triggers recalculation or repositioning of internal grid cells
	updateGridCells();
}







/**
 * set
 * Sets the position and size of the RectangularGridDragSelection
 *
 * @param rectPos: The fixed position of the RectangularGridDragSelection top left corner
 * @param rectSize: The size of the RectangularGridDragSelection
 */
void RectangularGridDragSelection::set(ofVec2f rectSize)
{
	gridBounds.set(gridBounds.x, gridBounds.y, rectSize.x, rectSize.y);
	updateGridCells();
}


//
/*
void RectangularGridDragSelection::draw()
{
	// Draw the rectangular grid selection and other components
	ofDrawRectangle(gridBounds);
	rectangleGranularitySlider.draw();
	gridGranularitySubmit.draw();
}
//*/
/*
 This function, draw(), is responsible for rendering the rectangular selection area
 within the user interface, as well as the additional controls that manage the
 granularity settings for the grid selection. It visually outlines the boundary
 of the grid and displays the slider and submission button, enabling the user to
 interactively control and apply granularity adjustments.
 */
void RectangularGridDragSelection::draw()
{
	/// Step 1: Draw the boundary of the rectangular grid selection.
	// Calls ofDrawRectangle to visually outline the region designated by gridBounds
	ofDrawRectangle(gridBounds);
	
	/// Step 2: Render the slider used for adjusting the granularity of the selection.
	// The slider is drawn on the screen, allowing user interaction
	rectangleGranularitySlider.draw();
	
	/// Step 3: Draw the submit button that applies the selected grid granularity.
	// The button is displayed for the user to confirm and apply changes
	gridGranularitySubmit.draw();
}



//
/*
void RectangularGridDragSelection::mouseDragged(int x, int y, int button)
{
	if (isDragging) // This means the user is currently selecting the bounds of the grid, where the width and height of the bounds grow at the same rate, so that there are always four right angles
	{
		
		float newWidth = std::abs(x - gridBounds.getX());
		float newHeight = std::abs(y - gridBounds.getY());
		float newSize = std::min(newWidth, newHeight); // Keep the shape square
		
		
		// Update gridBounds based on mouse drag
		//gridBounds.setWidth(x - gridBounds.getX());
		//gridBounds.setHeight(y - gridBounds.getY());
		gridBounds.setWidth(newSize);
		gridBounds.setHeight(newSize);
		updateGridCells(); // Update grid cells based on the new gridBounds
	}
	else
	{
		rectangleGranularitySlider.mouseDragged(x, y, button);
	}
}
//*/
/*
 This function facilitates the dynamic resizing of the grid's bounding box
 or the adjustment of the associated granularity slider. Specifically, it
 listens for mouse drag events and either resizes the bounding box, keeping
 it in a square shape, or updates the slider control if the bounding box is
 not currently being modified.
 
 Purpose:
 - Maintain a consistent, square bounding box by tracking mouse drag distance.
 - Update the grid cells immediately whenever resizing occurs.
 - Defer to the granularity slider for all mouse drag events when not resizing.
 
 Implementation Summary:
 - Check if isDragging is true to handle grid resizing.
 - Calculate the bounding box dimensions to enforce a square shape.
 - Update the bounding box and refresh grid cells.
 - Otherwise, delegate handling to the rectangleGranularitySlider.
 */
void RectangularGridDragSelection::mouseDragged(int x, int y, int button)
{
	/// Step 1: Determine if the user is resizing the grid bounding box.
	if (isDragging) // True if a drag has begun to define or reshape the grid area
	{
		/// Step 2: Calculate the drag distance relative to the grid's original corner.
		float newWidth = std::abs(x - gridBounds.getX());
		float newHeight = std::abs(y - gridBounds.getY());
		
		/// Step 3: Enforce a square shape by taking the smaller of the two dimensions.
		float newSize = std::min(newWidth, newHeight); // Keep the shape square
		
		// Update the bounding box dimensions to match the newly computed size
		gridBounds.setWidth(newSize);
		gridBounds.setHeight(newSize);
		
		/// Step 4: Refresh the positions and sizes of the grid's cells to reflect changes.
		updateGridCells(); // Update grid cells based on the new gridBounds
	}
	else
	{
		/// Step 5: If not resizing the grid, pass mouse drag events to the slider.
		rectangleGranularitySlider.mouseDragged(x, y, button);
	}
}



//
/*
void RectangularGridDragSelection::mousePressed(int x, int y, int button)
{
	if (gridBounds.inside(x, y))
	{
		// Start dragging if mouse is pressed inside gridBounds
		isDragging = true;
	}
	else if (rectangleGranularitySlider.rect.inside(x, y))
	{
		rectangleGranularitySlider.mousePressed(x, y, button);
		
		// Handle mouse press for slider and submit button
		//rectangleGranularitySlider.mousePressed(x, y, button);
		//gridGranularitySubmit.mousePressed(x, y, button);
	}
	else if (gridGranularitySubmit.rect.inside(x, y))
	{
		gridGranularitySubmit.mousePressed(x, y, button);
	}
}
//*/
/*
 This function manages user initiation of grid dragging behavior or interaction
 with the granularity controls. Specifically, when the mouse is pressed, it
 determines whether to begin a grid drag (if inside the grid bounds) or redirect
 the event to the appropriate UI element (the slider or the submit button).
 
 Purpose:
 - Check if the mouse press initiates a grid drag by verifying its position
 relative to the grid bounds.
 - Forward a mouse press event to the granularity slider or submit button when
 the press occurs within their respective areas.
 
 Means of Execution:
 - If the press is detected inside the rectangular grid bounds, enable dragging.
 - If the press is inside the slider or submit button regions, delegate handling
 to those components.
 */
void RectangularGridDragSelection::mousePressed(int x, int y, int button)
{
	/// Step 1: Check if the mouse press is within the grid bounds.
	if (gridBounds.inside(x, y))
	{
		// If inside, enable grid dragging behavior.
		isDragging = true;
	}
	/// Step 2: Otherwise, verify if the slider area has been clicked.
	else if (rectangleGranularitySlider.rect.inside(x, y))
	{
		// If within the slider, delegate to the slider's mousePressed handling.
		rectangleGranularitySlider.mousePressed(x, y, button);
	}
	/// Step 3: If not inside the slider, check if the submit button was clicked.
	else if (gridGranularitySubmit.rect.inside(x, y))
	{
		// If within the submit button, delegate to its mousePressed handling.
		gridGranularitySubmit.mousePressed(x, y, button);
	}
}

 
 
 
 
void RectangularGridDragSelection::mouseReleased(int x, int y, int button)
{
	isDragging = false; // Stop dragging on mouse release
	rectangleGranularitySlider.mouseReleased(x, y, button);
	gridGranularitySubmit.mouseReleased(x, y, button);
	
	if (gridGranularitySubmit.isPressed)
	{
		//finalizeGridSetup();
	}
}

void RectangularGridDragSelection::updateGridCells()
{
	// Update gridCells based on current gridBounds and granularity
	gridCells.clear();
	float cellWidth = gridBounds.getWidth() / granularity;
	float cellHeight = gridBounds.getHeight() / granularity;
	for (float i = 0; i < granularity; ++i)
	{
		for (float j = 0; j < granularity; ++j)
		{
			float cellX = gridBounds.getX() + i * cellWidth;
			float cellY = gridBounds.getY() + j * cellHeight;
			gridCells.push_back(ofRectangle(cellX, cellY, cellWidth, cellHeight));
		}
	}
}
