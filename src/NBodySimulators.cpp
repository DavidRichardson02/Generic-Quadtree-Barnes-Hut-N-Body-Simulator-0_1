//  NBodySimulators.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#include "NBodySimulators.hpp"






void BarnesHutSimulation::config(std::string simulatorTitle, std::string simulationMode)
{
	/**
	 * initialize the user interface and simulation configuration instances. These are pretty much purely for user interface stuff, feel free to ignore the 'SimulationConfig'
	 * and 'UserInterface' classes if you don't care about the openframeworks user interface stuff, I would actually encourage this.
	 *
	 * Not only does the user interface stuff have nothing to do with the actual algorithmic logic of the barnes-hut algorithm, but it also has no relevance
	 * to the math or physics of the simulation, also it's not super readable/easy to follow/organized.
	 *
	 * IMPORTANT NOTE: you can completely ignore the entire 'UserInterface' file, but DO NOT IGNORE THE 'SimulationConfig' file HAS THE INLINE FUNCTIONS TO BEGIN THE SIMULATION,
	 * 'BeginSimulation', as well as the inline functions to create models of galaxies, which are used to actually initialize the bodies in the simulation, and
	 * you SHOULD NOT ignore these inline functions.
	 *
	 */
	
	
	
	
	//RectangularGridDragSelection vectorGrid("", 0, 0, 0, 0);
	simulationConfigure.setup(theta, G, e, dt);
	
	
	
	/*----------------------------------------   BARNES HUT, QUADTREE  ----------------------------------------*/
	/** initialConditionsMode
	 * modify this to choose the initial conditions you want to have for the first galaxy that is created upon running the simualtion.
	 *
	 * initialConditionsMode == 0 : ColdStartInitialConditions
	 * initialConditionsMode == 1 : KeplerOrbitInitialConditions
	 * initialConditionsMode == 2 : CollidingDiskModelInitialConditions
	 * initialConditionsMode == 3 : DiskModelInitialConditions
	 * initialConditionsMode == 4 : PlummerModelInitialConditions
	 */
	initialConditionsMode = 5;
	BeginSimulation(simulationConfigure, bodies, initialConditionsMode);
	
	
	
	
	
	
	//if(simulationConfigure.userInterface.switchIntegrationMethod) {ComputePositionAtHalfTimeStep(dt, bodies);}  //only do halftimestep for LeapFrog KDK integration scheme
	
	
	TestBuildQuadtree(rootQuadtree,  bodies, simulationConfigure.bodyPool);
	
	
	//ofVec2f* bodiesAccelerations;
	bodiesAccelerations = new ofVec2f[bodies.size()];
	//ResetofVec2f(bodiesAccelerations, bodies.size());
	
	
	ComputeAllForces(rootQuadtree,  bodies, bodiesAccelerations, G, theta);
	//IntegrationScheme(dt, bodies, bodiesAccelerations, simulationConfigure.userInterface.switchIntegrationMethod->isOn, simulationConfigure.userInterface.slowMotionMode->isOn, simulationConfigure.userInterface.fastMotionMode->isOn);
	//IntegrateRK4Force(dt, bodies, bodiesAccelerations);
	//IntegrateRK4Fors(dt, bodies, bodiesAccelerations, rootQuadtree, G, theta);
	ComputeVelocityAndPosition(dt, bodies, bodiesAccelerations); //do LeapFrog KDK
	
	ComputeSystemEnergy(bodies, systemEnergy, systemKineticEnergy, systemPotentialEnergy);
	
	
	//ResetAccelerations(bodies);
	//delete[] bodiesAccelerations;
	
	cout<<"\n\n Setup Complete ofGetElapsedTimef(): " << ofGetElapsedTimef();
	
	//rootQuadtree->printTree();
	
	
	RectangularGridDragSelection vectorGrid("Test grid", (ofGetWidth() * 0.5 - 1250), (ofGetHeight() * 0.5 - 1250), 5, 2500);
	simulationConfigure.config(simulatorTitle, simulationMode, rootQuadtree, bodies, bodiesAccelerations, vectorGrid, theta, G, e, dt);
	
}

void BarnesHutSimulation::setup()
{
	/**
	 * initialize the user interface and simulation configuration instances. These are pretty much purely for user interface stuff, feel free to ignore the 'SimulationConfig'
	 * and 'UserInterface' classes if you don't care about the openframeworks user interface stuff, I would actually encourage this.
	 *
	 * Not only does the user interface stuff have nothing to do with the actual algorithmic logic of the barnes-hut algorithm, but it also has no relevance
	 * to the math or physics of the simulation, also it's not super readable/easy to follow/organized.
	 *
	 * IMPORTANT NOTE: you can completely ignore the entire 'UserInterface' file, but DO NOT IGNORE THE 'SimulationConfig' file HAS THE INLINE FUNCTIONS TO BEGIN THE SIMULATION,
	 * 'BeginSimulation', as well as the inline functions to create models of galaxies, which are used to actually initialize the bodies in the simulation, and
	 * you SHOULD NOT ignore these inline functions.
	 *
	 */
	simulationConfigure.setup(theta, G, e, dt);
	
	
	
	
	/*----------------------------------------   BARNES HUT, QUADTREE  ----------------------------------------*/
	/** initialConditionsMode
	 * modify this to choose the initial conditions you want to have for the first galaxy that is created upon running the simualtion.
	 *
	 * initialConditionsMode == 0 : ColdStartInitialConditions
	 * initialConditionsMode == 1 : KeplerOrbitInitialConditions
	 * initialConditionsMode == 2 : CollidingDiskModelInitialConditions
	 * initialConditionsMode == 3 : DiskModelInitialConditions
	 * initialConditionsMode == 4 : PlummerModelInitialConditions
	 */
	initialConditionsMode = 5;
	BeginSimulation(simulationConfigure, bodies, initialConditionsMode);
	
	
	
	
	
	
	//ResetAccelerations(bodies);
	//if(simulationConfigure.userInterface.switchIntegrationMethod) {ComputePositionAtHalfTimeStep(dt, bodies);}  //only do halftimestep for LeapFrog KDK integration scheme
	
	
	
	TestBuildQuadtree(rootQuadtree,  bodies, simulationConfigure.bodyPool);
	
	
	bodiesAccelerations = new ofVec2f[bodies.size()];
	
	
	
	ComputeAllForces(rootQuadtree,  bodies, bodiesAccelerations, G, theta);
	//IntegrationScheme(dt, bodies, bodiesAccelerations, simulationConfigure.userInterface.switchIntegrationMethod->isOn, simulationConfigure.userInterface.slowMotionMode->isOn, simulationConfigure.userInterface.fastMotionMode->isOn);
	//IntegrateRK4Force(dt, bodies, bodiesAccelerations);
	//IntegrateRK4Fors(dt, bodies, bodiesAccelerations, rootQuadtree, G, theta);
	ComputeVelocityAndPosition(dt, bodies, bodiesAccelerations); //do LeapFrog KDK
	
	ComputeSystemEnergy(bodies, systemEnergy, systemKineticEnergy, systemPotentialEnergy);
	
	
	ResetofVec2f(bodiesAccelerations, bodies.size());
	//delete[] bodiesAccelerations;
	
	cout<<"\n\n Setup Complete ofGetElapsedTimef(): " << ofGetElapsedTimef();
	
	//rootQuadtree->printTree();
}




void BarnesHutSimulation::update()
{
	simulationConfigure.update(rootQuadtree, theta, G, e, dt);
}








void BarnesHutSimulation::draw()
{
	//ResetAccelerations(bodies);
	//if(simulationConfigure.userInterface.switchIntegrationMethod) {ComputePositionAtHalfTimeStep(dt, bodies);}  //only do halftimestep for LeapFrog KDK integration scheme
	
	ComputePositionAtHalfTimeStep(dt, bodies, bodiesAccelerations);
	BuildQuadtree(rootQuadtree,  bodies, simulationConfigure.bodyPool);
	ResetofVec2f(bodiesAccelerations, bodies.size());
	
	
	
	
	ComputeAllForces(rootQuadtree,  bodies, bodiesAccelerations, G, theta);
	//IntegrationScheme(dt, bodies, bodiesAccelerations, simulationConfigure.userInterface.switchIntegrationMethod->isOn, simulationConfigure.userInterface.slowMotionMode->isOn, simulationConfigure.userInterface.fastMotionMode->isOn);
	//IntegrateRK4Force(dt, bodies, bodiesAccelerations);
	//IntegrateRK4Fors(dt, bodies, bodiesAccelerations, rootQuadtree, G, theta);
	ComputeVelocityAndPosition(dt, bodies, bodiesAccelerations); //do LeapFrog KDK
	
	
	ComputeSystemEnergy(bodies, systemEnergy, systemKineticEnergy, systemPotentialEnergy);
	
	simulationConfigure.draw(rootQuadtree, bodies, bodiesAccelerations, G, dt, systemEnergy, systemKineticEnergy, systemPotentialEnergy);
	
	
	
	
	/*-----------   Reset the tree(free memory) after drawing the quadrant bounds(if applicable)   -----------*/
	ResetTree(rootQuadtree);
}


void BarnesHutSimulation::exit()
{
	simulationConfigure.exit();
	ResetObjectPool(simulationConfigure.bodyPool, bodies);
	bodies.clear();
	ResetTree(rootQuadtree);
}




void BarnesHutSimulation::keyPressed(int key)
{
	simulationConfigure.keyPressed(key);
}


void BarnesHutSimulation::keyReleased(int key)
{
	simulationConfigure.keyReleased(key);
}



void BarnesHutSimulation::mouseDragged(int x, int y, int button)
{
	simulationConfigure.mouseDragged(x, y, button, rootQuadtree, bodies, theta, G);
	
	
}



void BarnesHutSimulation::mousePressed(int x, int y, int button)
{
	simulationConfigure.mousePressed(x, y, button, bodies, theta, G, lastG, e, dt, systemEnergy, systemKineticEnergy, systemPotentialEnergy);
	
}


void BarnesHutSimulation::mouseReleased(int x, int y, int button)
{
	simulationConfigure.mouseReleased(x, y, button, rootQuadtree, bodies);
	
}





void BarnesHutSimulation::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	simulationConfigure.mouseScrolled(x, y, scrollX, scrollY);
	
}



void BarnesHutSimulation::windowResized(int w, int h)
{
	simulationConfigure.windowResized(w,h);
}




