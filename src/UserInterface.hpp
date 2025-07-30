//  UserInterface.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 dev NOTE:
 The files in the 'src' folder(not including ofApp.cpp, ofApp.h, and main.cpp) are placed in there because they are antiquated implementations the large scale refactoring of the program is taking place to amend this, feel free to use these files as learning tools for available ways to access the simulation using OOP, but it was hardly made with rigorous
 methodologies, just a working model.
 */

/**
 * UserInterface Class: Provides GUI components for simulation control.
 *
 * This class contains nested classes for various GUI components, such as buttons, sliders, and text fields,
 * to facilitate interaction with the simulation. It allows users to control parameters, toggle settings,
 * and visualize outcomes.
 */


#pragma once
#include "ofMain.h"
#include "SimulationEntities.hpp"
#include "Quadtree.hpp"
#include "PhysicsLogic.hpp"
#include "VisualizationUtils.hpp"

#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"


#include "InputControls.hpp"
#include "NavigationalComponents.hpp"
#include "InformationalComponents.hpp"





class UserInterface
{
public:
	~UserInterface();
	
	
	void config(std::string simulatorTitle, std::string simulationMode, Quadtree* &rootQuadtree, std::vector<Body *> &bodies, const ofVec2f* bodiesAccelerations, RectangularGridDragSelection vectorGrid, float &theta, double &G, float &e, float &dt);
	
	
	
	
	void update(float &theta, double &G, float &e, float &dt);
	void draw(double &G, float &dt, int &numBodies, float &systemEnergy, float &systemKineticEnergy, float &systemPotentialEnergy);
	void drawICST(CoordinateSystem2D &coordinateSystem2D, Quadtree* &rootQuadtree,  std::vector<Body *> &bodies, ofVec2f* &bodiesAccelerations, ofVec2f &startMouse, float &dt); //draw inside the isolated coordinate system transform
	
	
	void visualizeSimulation(CoordinateSystem2D &coordinateSystem2D, Quadtree* &rootQuadtree,  std::vector<Body *> &bodies, ObjectPool<Body> &bodyPool, ofVec2f* &bodiesAccelerations, ofVec2f &startMouse, double &G, float &dt, int &numBodies, float &systemEnergy, float &systemKineticEnergy, float &systemPotentialEnergy);
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button, float &theta, double &G, double &lastG, float &e, float &dt);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	
	
	TableManager *tableManager;
	
	
	
	float numBodies = 2500; //parameters used for creating galaxies
	float bodiesMass = 5;
	float anchorMass = 500;
	float galaxyRadius = 2500;
	bool makeGalaxy, placeGalaxy;
};
