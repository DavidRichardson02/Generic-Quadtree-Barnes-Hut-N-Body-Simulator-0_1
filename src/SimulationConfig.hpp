//  SimulationConfig.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


/*
 * SimulationConfig Class: Configures and governs the overall simulation environment.
 *
 * The SimulationConfig class serves as the main hub for configuring and operating
 * the simulation. It holds an object pool for Body objects and initializes the
 * quadtree. It encapsulates all the core functionalities of the simulation and acts
 * as the interface for starting, updating, and rendering the simulation. It also
 * contains utility functions to generate initial conditions based on various
 * astrophysical models. These models range from cold starts with random positions to
 * more complex arrangements like the Plummer model.
 */


#pragma once
#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"
#include "DrawingUtilities.hpp"
#include "SequenceContainers.hpp"


#include "SimulationEntities.hpp"
#include "ObjectPool.hpp"
#include "Quadtree.hpp"
#include "PhysicsLogic.hpp"
#include "VisualizationUtils.hpp"
#include "UserInterface.hpp"
#include "ofMain.h"






//CoordinateSystem2D GlobalCoordinateSystem2D; // 2D coordinate system for the simulation



class SimulationConfig;



// ------------- Simulation Initialization -------------
/**
 * Begin the simulation based on the specified simulation mode.
 *
 * @param simulationConfigure A reference to the simulation configuration object.
 * @param bodies A reference to the vector containing body pointers.
 * @param initialConditionsMode An integer specifying the simulation mode.
 */
static inline void BeginSimulation(SimulationConfig &simulationConfigure, std::vector<Body*> &bodies, int initialConditionsMode);








// ------------- Galaxy Models for Initial Conditions -------------
/**
 * ColdStartInitialConditions: Initialize a 'cold start' galaxy, where bodies are positioned randomly within a circular area and have zero initial velocity.
 *
 * Here, we use a simple random distribution of bodies within a defined circle. This is an idealized situation and
 * does not correspond to any realistic galaxy model. However, it can serve as a testbed for the simulation algorithms.
 * Each body starts with zero velocity, and they are placed randomly within the specified galaxySize radius circle.
 * The anchorMass is the mass of a hypothetical body located at the center of the circle.
 *
 *
 * @param numBodies Number of bodies in the simulation.
 * @param bodiesMass Mass of each individual body.
 * @param bodyPool Object pool for acquiring body objects.
 * @param anchorMass Mass at the center of the galaxy.
 * @param galaxySize Size of the circular area where bodies are positioned.
 * @param galaxyAnchorPoint Central point of the galaxy.
 * @return A vector of pointers to the bodies.
 */
static inline std::vector<Body *> ColdStartInitialConditions(int numBodies, float bodiesMass, ObjectPool<Body> &bodyPool, float anchorMass, float galaxySize, ofVec2f galaxyAnchorPoint);




/**
 * KeplerOrbitInitialConditions: Initialize bodies in a Keplerian orbit around a massive central body.
 *
 * In this setup, bodies orbit around a central massive body according
 * to Kepler's laws. Each body is assigned a velocity that ensures a circular orbit.
 * This is a useful model for simulating planetary systems or simplified models of galaxies.
 *
 *
 * @param numBodies Number of bodies in the simulation.
 * @param anchorMass Mass at the center of the galaxy.
 * @param bodiesMass Mass of each individual body.
 * @param bodyPool Object pool for acquiring body objects.
 * @param orbitalRadius Radius of the orbit.
 * @param galaxyAnchorPoint Central point of the galaxy.
 * @return A vector of pointers to the bodies.
 */
static inline std::vector<Body*> KeplerOrbitInitialConditions(int numBodies, float anchorMass, float bodiesMass, ObjectPool<Body> &bodyPool, float orbitalRadius, ofVec2f galaxyAnchorPoint);




/**
 * DiskModelInitialConditions: Initialize a disk galaxy model, in which bodies are placed in a disk-like distribution.
 *
 * This is a simple disk galaxy model. Bodies are placed in a disk-like distribution around a
 * central mass (the anchorMass). Initial velocities are assigned such that the bodies will
 * orbit the center in a stable fashion.
 *
 *
 * @param numBodies Number of bodies in the simulation.
 * @param bodiesMass Mass of each individual body.
 * @param bodyPool Object pool for acquiring body objects.
 * @param anchorMass Mass at the center of the galaxy.
 * @param galaxyRadius Radius of the galaxy disk.
 * @param galaxyAnchorPoint Central point of the galaxy.
 * @return A vector of pointers to the bodies.
 */
static inline std::vector<Body*> DiskModelInitialConditions(int numBodies, float bodiesMass, ObjectPool<Body> &bodyPool,float anchorMass, float galaxyRadius, ofVec2f galaxyAnchorPoint);




/**
 * CollidingDiskModelInitialConditions: Initialize conditions for the collision of two disk galaxies.
 *
 * This model is meant to simulate the collision of two disk galaxies.
 * Bodies are initialized in two separate disk-like distributions, and they move towards each other.
 *
 *
 * @param numBodies Number of bodies in the simulation.
 * @param bodiesMass Mass of each individual body.
 * @param bodyPool Object pool for acquiring body objects.
 * @param mainAnchorMass Mass at the center of the main galaxy.
 * @param secondaryAnchorMass Mass at the center of the secondary galaxy.
 * @param mainRadius Radius of the main galaxy disk.
 * @param secondaryRadius Radius of the secondary galaxy disk.
 * @param mainAnchorPoint Central point of the main galaxy.
 * @param secondaryAnchorPoint Central point of the secondary galaxy.
 * @return A vector of pointers to the bodies.
 */
static inline std::vector<Body*> CollidingDiskModelInitialConditions(int numBodies, float bodiesMass, ObjectPool<Body> &bodyPool, float mainAnchorMass, float secondaryAnchorMass, float mainRadius, float secondaryRadius, ofVec2f mainAnchorPoint, ofVec2f secondaryAnchorPoint);




/**
 * PlummerModelInitialConditions: Initialize a Plummer model for galaxy simulation.
 *
 * Distribute the mass of the bodies following a spherically symmetric density profile by sampling the
 * cumulative distribution function (CDF) derived from the Plummer density profile ρ(r) and invert it to sample r.
 * Velocities of bodies are determined such that the system is in virial equilibrium, i.e., kinetic and potential energy of the system is balanced and the
 * mass distribution follows a Plummer density profile
 *
 *
 * @param numBodies Number of bodies in the simulation.
 * @param bodiesMass Mass of each individual body.
 * @param bodyPool Object pool for acquiring body objects.
 * @param scaleLength Characteristic scale length of the Plummer sphere.
 * @param galaxyAnchorPoint Central point of the Plummer sphere.
 * @return A vector of pointers to the bodies.
 *
 * @details
 * The Plummer model is a spherically symmetric stable isotropic distribution of particles.
 * It is often used to initialize N-body simulations for its mathematical simplicity and
 * physical relevance. In this model, both the density and potential are smooth everywhere,
 * and the distribution function depends solely on energy.
 *
 * The spatial coordinates (x, y) and velocities (vx, vy) of each body are generated
 * following the Plummer distribution. The characteristic scale length defines the size
 * of the core of the distribution, within which the mass density is nearly constant.
 *
 * Mathematical Background:
 * Density function: ρ(r) = (3M / 4πa³) * (1 + r²/a²)^(-5/2)
 * Cumulative mass distribution: M(r) = M * r³ / (a² + r²)^(3/2)
 * Velocity distribution: Based on isotropic Gaussian distribution scaled by (G * M / a)^(1/2)
 */
static inline std::vector<Body*> PlummerModelInitialConditions(int numBodies, float bodiesMass, ObjectPool<Body> &bodyPool, float anchorMass,  float galaxyScatter, float orbitalRadius, ofVec2f galaxyAnchorPoint);












class SimulationConfig
{
public:
	~SimulationConfig();
	
	
	// ------------- Setup and Initialization -------------
	// Sets up the initial simulation configuration parameters.
	void config(std::string simulatorTitle, std::string simulationMode, Quadtree* &rootQuadtree, std::vector<Body *> &bodies, const ofVec2f* bodiesAccelerations, RectangularGridDragSelection vectorGrid, float &theta, double &G, float &e, float &dt);
	void setup(float &theta, double &G, float &e, float &dt);
	
	// ------------- Update and Compute -------------
	// Updates the Quadtree and performs force calculations.
	void update(Quadtree* &rootQuadtree, float &theta, double &G, float &e, float &dt);
	
	// ------------- Rendering -------------
	// Draws the Quadtree and Body objects.
	void draw(Quadtree* &rootQuadtree,  std::vector<Body *> &bodies, ofVec2f* &bodiesAccelerations, double &G, float &dt, float &systemEnergy, float &systemKineticEnergy, float &systemPotentialEnergy);
	
	
	
	// ------------- Event Handlers -------------
	void exit();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button, Quadtree* &rootQuadtree, std::vector<Body *> &bodies, float &theta, double &G);
	void mousePressed(int x, int y, int button, std::vector<Body *> &bodies, float &theta, double &G, double &lastG, float &e, float &dt, float &systemEnergy, float &systemKineticEnergy, float &systemPotentialEnergy);
	void mouseReleased(int x, int y, int button, Quadtree* &rootQuadtree, std::vector<Body *> &bodies);
	void mouseScrolled(int x, int y, float scrollX, float scrollY);
	void windowResized(int w, int h);
	
	
	// ------------- Utility and Management -------------
	ObjectPool<Body> bodyPool; // Object pool for Body objects
	UserInterface userInterface; // Handles user interface components
	
	// ------------- Coordinate Systems and User Interaction -------------
	CoordinateSystem2D coordinateSystem2D; // 2D coordinate system for the simulation
	ofVec2f userForceVector; // User-defined force vector for interaction
	ofVec2f userDampingVector; // User-defined damping vector
	ofVec2f startMouse; // Initial mouse position for interaction
	ofVec2f offsetMouse; // Mouse offset for panning
	ofVec2f scaledMousePos; // Mouse position scaled to the coordinate system
};






static inline void BeginSimulation(SimulationConfig &simulationConfigure, std::vector<Body*> &bodies, int initialConditionsMode)
{
	assert(initialConditionsMode >= 0 && initialConditionsMode <= 5);
	
	
	if(initialConditionsMode == 0)
	{
		bodies  = ColdStartInitialConditions(10000, 2, simulationConfigure.bodyPool, 150, ofGetWidth()*1.5, ofVec2f(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
	}
	else if(initialConditionsMode == 1)
	{
		bodies = KeplerOrbitInitialConditions(12500, 6250, 2, simulationConfigure.bodyPool, ofGetWidth()*1.5, ofVec2f(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
	}
	else if(initialConditionsMode == 2)
	{
		bodies = CollidingDiskModelInitialConditions(10000, 10, simulationConfigure.bodyPool, 180, 140, 10000, 6000, ofVec2f(ofGetWidth() * 1.75, ofGetHeight() * 1.75), ofVec2f(ofGetWidth() * 0.125, ofGetHeight() * 0.125));
	}
	else if(initialConditionsMode == 3)
	{
		bodies = DiskModelInitialConditions(5000, 5, simulationConfigure.bodyPool, 50, 7500, ofVec2f(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
	}
	else if(initialConditionsMode == 4)
	{
		bodies = PlummerModelInitialConditions(25000, 10, simulationConfigure.bodyPool, 187500, 1, 25000, ofVec2f(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
	}
	else if(initialConditionsMode == 5)
	{
		bodies = PlummerModelInitialConditions(1250, 2, simulationConfigure.bodyPool, 187500*0.5, 1, 5000*0.5, ofVec2f(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
	}
	else
	{
		throw std::runtime_error("Initial Conditions Mode index is out of bounds");
	}

	
	
}








inline  std::vector<Body *> ColdStartInitialConditions(int numBodies, float bodiesMass, ObjectPool<Body> &bodyPool, float anchorMass, float galaxySize, ofVec2f galaxyAnchorPoint)
{
	std::vector<Body *> coldStartBodies;
	for (int i = 0; i < numBodies; i++)
	{
		ofVec2f position = ofVec2f(ofRandom(galaxyAnchorPoint.x - galaxySize * 0.5, galaxyAnchorPoint.x + galaxySize * 0.5), ofRandom(galaxyAnchorPoint.y - galaxySize * 0.5, galaxyAnchorPoint.y + galaxySize * 0.5));
		ofVec2f velocity = ofVec2f(0, 0);
		
		
		auto coldBody = bodyPool.acquire();
		coldBody->setParameters(position, velocity, bodiesMass);
		coldStartBodies.emplace_back(coldBody);
	}
	return(coldStartBodies);
}





inline std::vector<Body*> KeplerOrbitInitialConditions(int numBodies, float anchorMass, float bodiesMass, ObjectPool<Body> &bodyPool,float orbitalRadius, ofVec2f galaxyAnchorPoint)
{
	std::vector<Body *> keplerBodies;
	for (int i = 0; i < numBodies; i++)
	{
		ofVec2f position = ofVec2f(orbitalRadius * cos(i * 2 * PI / (numBodies - 1)), orbitalRadius * sin(i * 2 * PI / (numBodies - 1)));    // place other bodies in orbit around the  body
		position.x += galaxyAnchorPoint.x;
		position.y += galaxyAnchorPoint.y;
		ofVec2f velocity = ofVec2f(-(6.67430e-11 * anchorMass / orbitalRadius) * sin(i * 2 * PI / (numBodies - 1)), (6.67430e-11 * anchorMass / orbitalRadius) * cos(i * 2 * PI / (numBodies - 1)));     // set velocity for a circular orbit
		
		auto keplerBodY = bodyPool.acquire();
		keplerBodY->setParameters(position, velocity, bodiesMass);
		keplerBodies.emplace_back(keplerBodY);
	}
	//keplerBodies[0]->radius = sqrt(anchorMass)*2;  // bodies[0] is the central body
	keplerBodies[0]->mass = anchorMass;
	keplerBodies[0]->position = galaxyAnchorPoint;
	keplerBodies[0]->velocity = ofVec2f(0, 0);
	return(keplerBodies);
}




inline std::vector<Body*>  DiskModelInitialConditions(int numBodies, float bodiesMass, ObjectPool<Body> &bodyPool,float anchorMass, float galaxyRadius, ofVec2f galaxyAnchorPoint)
{
	std::vector<Body *> diskModelBodies;
	std::default_random_engine generator;
	
	std::uniform_real_distribution<float> uniform(0.0, 2.0);
	std::uniform_real_distribution<float> distribution(1.5*bodiesMass*10, 12*bodiesMass*10);
	std::uniform_real_distribution<float> distribution_theta(0.0, 2 * PI);
	
	for (int i = 0; i < numBodies; ++i)
	{
		float theta = distribution_theta(generator);
		float r = distribution(generator);
		ofVec2f position, velocity;
		
		// set velocity of particle
		auto diskModelBody = bodyPool.acquire();
		
		if (i == 0)
		{
			position = galaxyAnchorPoint;
			velocity = ofVec2f(0, 0);
			
			diskModelBody->setParameters(position, velocity, bodiesMass*5);
			diskModelBodies.emplace_back(diskModelBody);
		}
		else
		{
			position = ofVec2f(r * cos(theta) + galaxyAnchorPoint.x, r * sin(theta) + galaxyAnchorPoint.y);
			float v = sqrt(6.67430e-11 * (bodiesMass*5) / r);
			velocity = ofVec2f(-v * sin(theta), v * cos(theta));
			
			diskModelBody->setParameters(position, velocity, bodiesMass);
			diskModelBodies.emplace_back(diskModelBody);
			
			
		}
	}
	return diskModelBodies;
}




inline std::vector<Body*> CollidingDiskModelInitialConditions(int numBodies, float bodiesMass, ObjectPool<Body> &bodyPool,float mainAnchorMass, float secondaryAnchorMass, float mainRadius, float secondaryRadius, ofVec2f mainAnchorPoint, ofVec2f secondaryAnchorPoint)
{
	std::vector<Body *> collidingDiskBodies;
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution1(1.5*mainAnchorMass, 12*mainAnchorMass);
	std::uniform_real_distribution<float> distribution2(1*secondaryAnchorMass, 8*secondaryAnchorMass);
	std::uniform_real_distribution<float> distribution_theta(0.0, 2 * PI);
	
	
	for (int i = 0; i < numBodies; ++i)
	{
		float theta = distribution_theta(generator);
		float r1 = distribution1(generator);
		float r2 = distribution2(generator);
		ofVec2f position, velocity;
		
		auto collidingDiskModelBody = bodyPool.acquire();
		
		
		if (i == 0)
		{
			position = mainAnchorPoint;
			velocity = ofVec2f(0, 0);
			
			collidingDiskModelBody->setParameters(position, velocity, mainAnchorMass*0.5);
			collidingDiskBodies.emplace_back(collidingDiskModelBody);
			
		}
		else if (i == 1)
		{
			position = secondaryAnchorPoint;
			velocity = ofVec2f(0, 0);
			
			collidingDiskModelBody->setParameters(position, velocity, secondaryAnchorMass*0.5);
			collidingDiskBodies.emplace_back(collidingDiskModelBody);
		}
		else if (i <= 3 * numBodies / 4)
		{
			position = ofVec2f(r1 * cos(theta) + mainAnchorPoint.x, r1 * sin(theta) + mainAnchorPoint.y);
			float v1 = sqrt(6.67430e-11 * mainAnchorMass / r1);
			velocity = ofVec2f(-v1 * sin(theta), v1 * cos(theta));
			
			collidingDiskModelBody->setParameters(position, velocity, bodiesMass);
			collidingDiskBodies.emplace_back(collidingDiskModelBody);
		}
		else
		{
			position = ofVec2f(r2 * cos(theta) + secondaryAnchorPoint.x, r2 * sin(theta) + secondaryAnchorPoint.y);
			float v2 = sqrt(6.67430e-11 * secondaryAnchorMass / r2);
			velocity = ofVec2f(-v2 * sin(theta), v2 * cos(theta));
			
			collidingDiskModelBody->setParameters(position, velocity, bodiesMass);
			collidingDiskBodies.emplace_back(collidingDiskModelBody);
			
		}
	}
	return collidingDiskBodies;
}




inline std::vector<Body*> PlummerModelInitialConditions(int numBodies, float bodiesMass, ObjectPool<Body> &bodyPool,float anchorMass, float galaxyScatter, float orbitalRadius, ofVec2f galaxyAnchorPoint)
{
	std::vector<Body *> plummerModelBodies;
	//float squaredAnchorMass = anchorMass * anchorMass / orbitalRadius; //want the bodies to be distributed around the anchor mass, using the square of the anchor mass to avoid having to compue the square root of the position later, sqrt() very slow
	//the position is dictated by the orbital radius, so by dividing the anchormass/centralbody by the orbital radius, it's being scaled to the bodies position magnitude. This ensures that the bodies will be distributed following the plummer distribution, while also maintaining a nearby perimeter around the central body of the galaxy
	
	
	float mass, uniformRandom, r, theta, phi, x, y, u1, u2, z1, v, vx, vy;
	ofVec2f position, velocity;
	for (int i = 0; i < numBodies; ++i)
	{
		uniformRandom = ofRandom(galaxyScatter);          // Generate uniform random number between 0 and 1
		r = orbitalRadius * sqrt(pow(uniformRandom, -2.0 / 3) - 1);
		theta = 2 * PI * ofRandom(1.0);      // Generate random angles uniformly distributed
		phi = acos(1 - 2 * ofRandom(1.0));
		x = r * sin(phi) * cos(theta);
		y = r * sin(phi) * sin(theta);
		
		
		
		
		position = ofVec2f(x + galaxyAnchorPoint.x, y + galaxyAnchorPoint.y);
		
		
		//Generate normal distributed random numbers using Box-Muller transformation
		u1 = ofRandom(1.0);
		u2 = ofRandom(1.0);
		z1 = sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2); // Box-Muller transformation
		v = sqrt(2) * pow((1 + r * r), -0.25);
		vx = v * sqrt(2) * pow(1 + r * r, -0.25) * z1;
		vy = sqrt(v * v - vx * vx) * (ofRandom(1.0) > 0.5 ? 1 : -1);
		velocity = ofVec2f(vx, vy);
		
		auto plummerModelBodY = bodyPool.acquire();
		plummerModelBodY->setParameters(position, velocity, bodiesMass);
		plummerModelBodies.emplace_back(plummerModelBodY);
	}
	
	
	return(plummerModelBodies);
}
