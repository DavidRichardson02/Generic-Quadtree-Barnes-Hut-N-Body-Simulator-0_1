//  SimulationEntities.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#pragma once
#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"
#include "DrawingUtilities.hpp"
#include "SequenceContainers.hpp"
#include "ofMain.h"


const float epsilon = 50; // softening parameer in force calculations, (usualy < 1, but set at a higher value to keep bodies from having a too great accel from close encounters);



 
/*
 * Body Class: the n-bodies in the n-body simulation
 *
 * This file defines the Body class, which is responsible for encapsulating the properties and behavior of
 * the individual bodies in the simulation, and contains all relevant information about the position,
 * velocity, and mass of a body. They are the objects to be inserted into the quadctree.
 * Will be computed with some initial conditions, from which a quadctree that encompasses all bodies
 * will be generated.
 *
 *  NOTE: Mass is used as analogous to radius for the rigid 2D bodies of this simulation
 */
class Body
{
public:
	// ------------- Constructors and Destructor -------------
	Body();
	Body(ofVec2f pos, ofVec2f vel, float _mass);
	Body(const Body& other);
	~Body();
	
	
	// ------------- Comparison operators -------------
	Body& operator=(const Body& other);
	bool operator!=(const Body& other);
	
	
	// ------------- Kinematic Operations -------------
	void applyForce(ofVec2f& force);  //Applies a force vector to update position and velocity.
	void dampMotion(float dampParameter); //Dampens the body's motion based on the damping parameter.
	
	
	// ------------- Utility Methods For Object Pooling-------------
	void setParameters(ofVec2f pos, ofVec2f vel, float mass); // Sets the properties of an acquired body from object pool
	void reset(); //used to restore the body to a state that makes it ready for reuse     puts the object back to its initial state
	
	
	
	
	// ------------- Visualization -------------
	void draw(bool colorMode);
	
	
	
	
	// ------------- Member variables -------------
	ofVec2f position; // Position of the body in 2D space.
	ofVec2f velocity; // Velocity of the body in 2D space.
	float mass; // Mass of the body, used as analogous to radius for the rigid circular body.
};



static inline void ComputeEntitiesEnergy();








/**
 * BodyData Class: An extension of the Body class, manages the parameters non-essential for computing the motions of simulation entities
 *
 * This class serves the purpose of seperating, storing, and handling the parameters of the entities
 * that are in constant demand/reference from the parameters of the entities that are only needed
 * in certain circumstances(ex. energy only needs to be kept track of in the non-performance modes of simulation,
 * but for testing and benchmarking simulators)
 */
class BodyData
{
public:
	// ------------- Constructors and Destructor -------------
	BodyData(float mass);
	BodyData(ofVec2f position, ofVec2f velocity, float mass);
	BodyData(const Body body);
	BodyData(const BodyData& other);
	~BodyData();
	
	
	// ------------- Comparison operators -------------
	BodyData& operator=(const BodyData& other);
	bool operator!=(const BodyData& other);
	
	
	
	// ------------- Utility Methods For Object Pooling-------------
	void setParameters(ofVec2f position, ofVec2f velocity, float mass); // Sets the properties of an acquired body from object pool
	void reset(); //used to restore the body to a state that makes it ready for reuse     puts the object back to its initial state
	
	
	
	// ------------- Visualization -------------
	void draw(bool colorMode, const Body body);
	
	
	
	
	
	
	// ------------- Member variables -------------
	float kineticEnergy; // Kinetic energy of the body.
	float potentialEnergy; // Potential energy of the body.
	
	
	
	float angularVelocity; // Angular velocity of the body.
	float orientation; // Current angle (orientation) of the body
	float momentOfInertia; // Moment of Inertia
};
