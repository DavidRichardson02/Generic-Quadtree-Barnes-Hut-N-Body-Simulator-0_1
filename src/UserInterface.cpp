//  UserInterface.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 dev NOTE:
 The files in the 'src' folder(not including ofApp.cpp, ofApp.h, and main.cpp) are placed in there because they are antiquated implementations the large scale refactoring of the program is taking place to amend this, feel free to use these files as learning tools for available ways to access the simulation using OOP, but it was hardly made with rigorous
 methodologies, just a working model.
 */


#include "UserInterface.hpp"
#include "VisualizationUtils.hpp"




UserInterface::~UserInterface()
{
	exit();
}



void UserInterface::config(std::string simulatorTitle, std::string simulationMode, Quadtree* &rootQuadtree, std::vector<Body *> &bodies, const ofVec2f* bodiesAccelerations, RectangularGridDragSelection vectorGrid, float &theta, double &G, float &e, float &dt)
{
	int simMode = stoi(simulationMode);
	assert(simMode >= 0 && simMode <= 3);
	
	
	tableManager = new TableManager(std::stoi(simulationMode), simulatorTitle, 0 + ofGetWidth() * 0.025, ofGetHeight() * 0.030, 15, 15);
	if(simMode == 0) // deafult mode
	{
		cout << "\nDefault mode\n" << endl;
		/**
		 * This code snippet creates a Toggle object for the option to visualize Quadtree bounds.
		 * The Toggle object is initialized with the label "Visualize Quadtree Bounds", and a lambda function
		 * that calls the VisualizeQuadtreeBounds function with the rootQuadtree as an argument.
		 * The lambda function is executed when the Toggle is switched on.
		 * The Toggle is initially set to off (false).
		 */
		Toggle* visualizeQuadtreeBounds = new Toggle("Visualize Quadtree Bounds", 125, 175, 20, 15, false,
													 [&rootQuadtree]() {
			/// The lambda function begins here.
			// The VisualizeQuadtreeBounds function is called with rootQuadtree as an argument.
			VisualizeQuadtreeBounds(rootQuadtree);
			/// The lambda function ends here.
		});
		
		
		
		Toggle *visualizeQuadtreeCentresOfMass = new Toggle("Visualize Quadtree Centres of Mass", 125, 175, 20, 15, false, [&rootQuadtree]() {
			VisualizeQuadtreeCentresOfMass(rootQuadtree);
		});
		
		
		Toggle *visualizeQuadtreeNodeProperties = new Toggle("Visualize Quadtree Node Properties", 125, 175, 20, 15, false);
		Toggle *visualizeQuadtreeDiagram = new Toggle("Visualize Quadtree Diagram", 125, 175, 20, 15, false);
		
		Table *quadtreeVisualization = new Table("Quadtree Visualization", 0 + ofGetWidth() * 0.05, ofGetHeight() * 0.0625, 15, 15, false, 1);
		quadtreeVisualization->addToggleElement(visualizeQuadtreeBounds);
		quadtreeVisualization->addToggleElement(visualizeQuadtreeCentresOfMass);
		quadtreeVisualization->addToggleElement(visualizeQuadtreeNodeProperties);
		quadtreeVisualization->addToggleElement(visualizeQuadtreeDiagram);
		Tooltip *tooltip;
		tooltip = new Tooltip("This is a tooltip message. It can be short or long depending on the message length. hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh", 100, 100);
		quadtreeVisualization->addTooltipElement(tooltip);
		
	
		
		Toggle *visualizeBodiesAngularOrientation = new Toggle("Visualize Body Angular Orientation", 375, 175, 20, 15, false, [&bodies, bodiesAccelerations]() {
			VisualizeBodiesAngularOrientation(bodies, bodiesAccelerations);
		});
		Toggle *visualizeBodiesEnergyGradient = new Toggle("Visualize Body Energy Gradient", 375, 200, 20, 15, false);
		
		Table *bodiesVisualization = new Table("N-Bodies Visualization", 0 + ofGetWidth() * 0.05, ofGetHeight() * 0.125, 15, 15, false, 0);
		bodiesVisualization->addToggleElement(visualizeBodiesAngularOrientation);
		bodiesVisualization->addToggleElement(visualizeBodiesEnergyGradient);
		
		
		
		
		
		Toggle* visualizeGravitationalVectorField = new Toggle("Visualize Gravitational Vector Field", 125, 200, 20, 15, false, [&bodies, bodiesAccelerations, vectorGrid]() {
			VisualizeGravitationalVectorField(bodies, bodiesAccelerations, vectorGrid);
		});
		
		
		
		
		Toggle* visualizeRelativePotentialEnergyFields = new Toggle("Visualize Relative Potential Energy Fields", 125, 225, 20, 15, false, [&bodies, &G, vectorGrid]() {
			PrepareRelativePotentialEnergyField(bodies, G, vectorGrid);
		}); //Computing the gravitational potential at each point on a grid and color-coding these points to visualize "gravitational wells". Then, to make the visualization more insightful, sophisticated color mapping algorithms are used.
		
		Table *physicsVisualization = new Table("Physics Visualization", 0 + ofGetWidth() * 0.05, ofGetHeight() * 0.1875, 15, 15, false, 0);
		physicsVisualization->addToggleElement(visualizeGravitationalVectorField);
		physicsVisualization->addToggleElement(visualizeRelativePotentialEnergyFields);
		
		
		
		
		
		Toggle *visualizeSimulationStats = new Toggle("Simulation Stats: ", 125, 300, 15, 15, true); //FPS, num bodies, total energy, kinetic, potential, G
		Toggle *visualizeQuadtreeBenchmarks = new Toggle("Visualize Quadtree Benchmarks: ", 125, 300, 15, 15, true);
		//average tree construction time
		//average force computation time
		
		Table *benchmarksVisualization = new Table("Benchmarks Visualization", 0 + ofGetWidth() * 0.05, ofGetHeight() * 0.25, 15, 15, false, 0);
		benchmarksVisualization->addToggleElement(visualizeSimulationStats);
		benchmarksVisualization->addToggleElement(visualizeQuadtreeBenchmarks);
		
		
		
		
		
		Slider* thetaSlider = new Slider("MAC", 125, 50, 150, 10, 0, 2, theta);
		Slider* coefOfRestitution = new Slider("e", 125, 100, 150, 10, 0, 1, e);
		TextField* GTextField = new TextField("G", 125, 75, 200, 35, 6.67430e-11, 6.67430e4, G, 15);
		Toggle* toggleGravity = new Toggle("Toggle Gravity", 125, 125, 20, 15, false);
		Toggle* toggleCollisions = new Toggle("Toggle Collisions", 125, 150, 20, 15, false);
		Toggle* switchIntegrationMethod = new Toggle("Toggle Integration \nMethods: ", 125, 175, 20, 15, false);
		Toggle* slowMotionMode = new Toggle("Toggle Slow-Motion Mode", 225, 150, 20, 15, false);
		Toggle* fastMotionMode = new Toggle("Toggle Fast-Motion Mode", 225, 150, 20, 15, false);
		
		Table* parametersConfiguration = new Table("Configure Simulation Parameters", 0 + ofGetWidth() * 0.05, ofGetHeight() * 0.3125, 15, 15, false, 1);
		parametersConfiguration->addSliderElement(thetaSlider);
		parametersConfiguration->addSliderElement(coefOfRestitution);
		parametersConfiguration->addTextFieldElement(GTextField);
		parametersConfiguration->addToggleElement(toggleGravity);
		parametersConfiguration->addToggleElement(toggleCollisions);
		parametersConfiguration->addToggleElement(switchIntegrationMethod);
		parametersConfiguration->addToggleElement(slowMotionMode);
		parametersConfiguration->addToggleElement(fastMotionMode);
		
		
		tableManager->addTable(quadtreeVisualization);
		tableManager->addTable(bodiesVisualization);
		tableManager->addTable(physicsVisualization);
		tableManager->addTable(benchmarksVisualization);
		tableManager->addTable(parametersConfiguration);
	}
	else if(simMode == 1) // performance mode
	{
		
	}
	else if(simMode == 2) // benchmarking mode
	{
		Table *quadtreeVisualization;
		Table *bodiesVisualization;
		Table *physicsVisualization;
		
		
		
		
		Toggle* visualizeSimulationStats; //FPS, num bodies, total energy, kinetic, potential, G
		Toggle *visualizeQuadtreeBenchmarks;
		//average tree construction time
		//average force computation time
		
		Table *benchmarksVisualization;
	}
	else if(simMode == 3) // testing mode
	{
		
		
		
	}
	else if(simMode == 4) // teaching mode
	{
		
	}
	
	
	//
	/*
	 tableManager = new TableManager(std::stoi(simulationMode), simulatorTitle, 0 + ofGetWidth() * 0.025, ofGetHeight() * 0.030, 15, 15);
	 
	 for(auto &tempTable : tempTableManager->tables)
	 {
	 tableManager->addTable(tempTable);
	 tableManager->addTable(tempTable);
	 tableManager->addTable(tempTable);
	 tableManager->addTable(tempTable);
	 tableManager->addTable(tempTable);
	 }
	 
	 //tempTableManager->exit();
	 //delete[] tempTableManager;
	 //*/
}






void UserInterface::update(float &theta, double &G, float &e, float &dt)
{
	if (tableManager->galaxyCreationMode)
	{
		tableManager->galaxyMode(); //set all other tables to closed
		dt = 0.001; //slowmo affect while the create galaxy table is open, looks really cool
	}
	else if (!tableManager->galaxyCreationMode)
	{
		dt = 0.01;
	}
	
}






void UserInterface::draw(double &G, float &dt, int &numBodies, float &systemEnergy, float &systemKineticEnergy, float &systemPotentialEnergy)
{
	tableManager->draw();
	
	
	//if (simulationStats->isOn && visualizationParametersTable->isOpened)
	//{
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 2), ofGetWidth() - 350, 340);
	ofDrawBitmapString("Bodies: " + ofToString(numBodies, 1), ofGetWidth() - 350, 355);
	ofDrawBitmapString("Total Energy: " + ofToString(systemEnergy, 8) + "\n" + "Kinetic Energy: " + ofToString(systemKineticEnergy, 8) + "\n" + "Potential Energy: " + ofToString(systemPotentialEnergy, 8) + "\nUniversal Constant G: " + ofToString(G, 16), ofGetWidth() - 350, 370);
	//}
}




//draw inside the isolated coordinate system transform
void UserInterface::drawICST(CoordinateSystem2D &coordinateSystem2D, Quadtree* &rootQuadtree,  std::vector<Body *> &bodies, ofVec2f* &bodiesAccelerations, ofVec2f &startMouse, float &dt)
{
	/*----------------------   Begin the isolated coordinate system transform   ----------------------*/
	ofPushMatrix();
	ofTranslate(coordinateSystem2D.offset.x, coordinateSystem2D.offset.y);
	ofScale(coordinateSystem2D.zoomScale, coordinateSystem2D.zoomScale);
	
	
	for (int i = 0; i < bodies.size(); i++)
	{
		//ofSetColor(140, 140, 222, 127); // Set the color to bluish-gray
		ofSetColor(140, 140, 140); // Set the color to bluish-gray
		bodies[i]->draw(false);
	}
	
	
	
	
	//double G = 6.67430; // Define the gravitational constant
	//float minPotential = 0, maxPotential = 10000; // Define the minimum and maximum potential energy in the system
	//float boundsSize = 1000.0f; // Define the bounds size for the grid
	//float CELLSIZE = 6; // Define the cell size for the grid
	//std::vector<std::vector<float>> potentialGrid; // Define the potential grid
	
	
	
	
	
	//VisualizeRelativePotentialEnergyField(potentialGrid, bodies, G, minPotential, maxPotential, boundsSize, CELLSIZE); // Call the function to visualize the relative potential energy field
	//VisualizeGravitationalVectorField(bodies, bodiesAccelerations, 5000, 100);
	//VisualizeQuadtreeCentresOfMass(rootQuadtree);
	
	
	
	
	ofPopMatrix();
	/*----------------------   End the isolated coordinate system transform   ----------------------*/
}






void UserInterface::exit()
{
	tableManager->exit();
}






void UserInterface::keyReleased(int key)
{
	tableManager->keyReleased(key);
}






void UserInterface::mouseDragged(int x, int y, int button)
{
	tableManager->mouseDragged(x, y, button);
}






void UserInterface::mousePressed(int x, int y, int button, float &theta, double &G, double &lastG, float &e, float &dt)
{
	tableManager->mousePressed(x, y, button);
	
	
	//
	/*
	 
	 if (modifyParametersTable->isOpened)
	 {
	 switchIntegrationMethod;
	 }
	 
	 
	 
	 if (toggleGravity->isOn)
	 {
	 if (G != 0)
	 {
	 lastG = G;
	 G = 0;
	 }
	 }
	 
	 if (!toggleGravity->isOn)
	 {
	 if (lastG != 0)
	 {
	 G = lastG;
	 lastG = 0;
	 }
	 }
	 //*/
	
}






void UserInterface::mouseReleased(int x, int y, int button)
{
	tableManager->mouseReleased(x, y, button);
}






void UserInterface::windowResized(int w, int h)
{
	//tableManager->setPosition(ofVec2f(0 + ofGetWidth() * 0.025, ofGetHeight() * 0.030));
}
