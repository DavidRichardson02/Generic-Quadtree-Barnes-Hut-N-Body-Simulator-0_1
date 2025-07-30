//  NBodySimulators.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 dev NOTE:
 The files in the 'src' folder(not including ofApp.cpp, ofApp.h, and main.cpp) are placed in there because they are antiquated implementations the large scale refactoring of the program is taking place to amend this, feel free to use these files as learning tools for available ways to access the simulation using OOP, but it was hardly made with rigorous
 methodologies, just a working model.
 */



#pragma once
#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"

#include "InputControls.hpp"
#include "NavigationalComponents.hpp"


#include "SequenceContainers.hpp"
#include "ObjectPool.hpp"
#include "DrawingUtilities.hpp"


#include "SimulationEntities.hpp"
#include "QuadrantUtils.hpp"
#include "Quadtree.hpp"
#include "PhysicsLogic.hpp"
#include "SimulationConfig.hpp"

#include "VisualizationUtils.hpp"
#include "UserInterface.hpp"

#include "ofMain.h"















/*----------------------------------------   SERIAL POINTER-BASED QUADTREE BARNES-HUT SIMULATION  ----------------------------------------*/
/**
 * Defines the BarnesHutSimulation class for gravitational N-Body simulation
 *
 * The BarnesHutSimulation class manages the entire n-body simulation, encompassing initialization,
 * update, and visualization of the simulation. It uses the Barnes-Hut approximation algorithm for efficient
 * computation of gravitational forces between bodies in the simulation. This class also manages the
 * overall state of the simulation, including total energy calculations and UI interactions.
 */
//BarnesHutSimulation Class: Orchestrator of the n-body simulation using Barnes-Hut algorithm.
class BarnesHutSimulation
{
public:
	
	// --------------- Member variables ---------------
	SimulationConfig simulationConfigure;  // Configuration object to hold various simulation parameters
	
	
	float theta = 1;  // Barnes-Hut approximation parameter, commonly known as theta or multipole acceptance criterion
	double G = 66.743;//6.67430e-11;  // Universal gravitation constant
	double lastG;  // Previous value of the gravitation constant for toggling gravity
	float e = 0.25;  // Coefficient of restitution for collisions
	float dt = 0.01;  // Size of simulation steps (time delta)
	
	
	float systemKineticEnergy = 0;  // Kinetic energy of the entire system
	float systemPotentialEnergy = 0;  // Potential energy of the entire system
	float systemEnergy = 0;  // Total energy of the entire system
	
	
	std::vector<Body*> bodies; // Vector of pointers to Body objects managed by object pool in SimulationConfig class
	Quadtree* rootQuadtree; // Root node of the Quadtree
	ofVec2f* bodiesAccelerations; // Array of accelerations for each Body object
	
	int simulationMode; // The current simulation mode
	int initialConditionsMode; // The initial conditions of bodies for a simulation
	
	
	
	// --------------- Member Functions ---------------
	void config(std::string simulatorTitle, std::string simulationMode);
	void setup(); // Initializes simulation parameters and prepares for simulation run.
	void update(); //Updates the simulation by calculating forces, updating Body states, and reorganizing the quadtree.
	void draw(); // Draws the Body objects and any other visualization elements to the screen.
	
	
	// --------------- Event Handlers ---------------
	void exit();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y, float scrollX, float scrollY);
	void windowResized(int w, int h);
};














class NBodySimulators
{
public:
	BarnesHutSimulation NBodySimulation;
	
	//pure barnes hut simulation
	
	
	//barnes hut simulation with cool visualization options
	
	
	
	//naive simulation
	
	
	//testing mode
	
	
	
};



static inline void ResetVec2D(Vec2D *&vec2d, int numVecs)
{
	if(!vec2d)
	{
		throw std::invalid_argument("vec3d is a null pointer in 'ResetVec3D'.");
	}
	
	for(int i = 0; i < numVecs; i++)
	{
		vec2d[i].reset();
	}
}





