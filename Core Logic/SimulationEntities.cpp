//  SimulationEntities.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

#include "SimulationEntities.hpp"






Body::Body()
{
	position.set(0, 0);
	velocity.set(0, 0);
	mass = 0;
}

Body::Body(ofVec2f pos, ofVec2f vel, float _mass)
{
	position = pos;
	velocity = vel;
	mass = _mass;
}



// Copy constructor
Body::Body(const Body& other) : position(other.position), velocity(other.velocity), mass(other.mass){}

Body::~Body()
{
	position = {0,0};
	velocity = {0,0};
	mass = 0;
}


// Assignment operator
Body& Body::operator=(const Body& other)
{
	if (this != &other)
	{
		position = other.position;
		velocity = other.velocity;
		mass = other.mass;
	}
	return(*this);
}



bool Body::operator!=(const Body& other)
{
	bool notEqual = false;
	if (this == &other)
	{
		notEqual = true;
	}
	return(notEqual);
}




void Body::applyForce(ofVec2f& force)
{
	ofVec2f acceleration = force / mass;
	velocity = velocity + acceleration;
}

void Body::dampMotion(float dampParameter)
{
	velocity = velocity*dampParameter;
}


void Body::setParameters(ofVec2f pos, ofVec2f vel, float _mass)
{
	position = pos;
	velocity = vel;
	mass = _mass;
}



void Body::reset()
{
	position.set(0, 0);
	velocity.set(0, 0);
	mass = 0;
}





void Body:: draw(bool colorMode)
{
	//
	/*
	 float energyNormalized = kineticEnergy / (kineticEnergy + fabs(potentialEnergy));
	 
	 
	 ofColor energyLevel(0,255,0);
	 
	 if (kineticEnergy <= fabs(potentialEnergy))
	 {
	 if(colorMode)
	 {
	 energyLevel.r = energyNormalized * 2.0 * 255;
	 energyLevel.g = 255;
	 
	 energyLevel.b = 0;
	 }
	 else if(!colorMode)
	 {
	 energyLevel.b = energyNormalized * 2.0 * 255;
	 energyLevel.r = 255;
	 energyLevel.g = 0;
	 }
	 }
	 else
	 {
	 if(colorMode)
	 {
	 energyLevel.r = 255;
	 energyLevel.g = 255 - (energyNormalized - 0.5) * 2.0 * 255;
	 
	 energyLevel.b = 0;
	 }
	 else if(!colorMode)
	 {
	 energyLevel.b = 255;
	 energyLevel.r = 255 - (energyNormalized - 0.5) * 2.0 * 255;
	 energyLevel.g = 0;
	 }
	 }
	 //*/
	
	
	
	ofFill();
	//ofSetColor(energyLevel);
	ofDrawCircle(position.x, position.y, mass);
	
	// Draw orientation line
	//ofSetColor(ofColor::white);
	//float orientationLineLength = mass * 2;  // Length of the line can be proportional to mass or some fixed value
	//ofVec2f orientationVector = ofVec2f(cos(orientation), sin(orientation)) * mass;
	//ofDrawLine(position, position + orientationVector);
}
















BodyData::BodyData(float mass)
{
	kineticEnergy = 0;
	potentialEnergy = 0;
	
	momentOfInertia = 0.25 * mass * (mass * mass); // I = 1/4 * mass * radius^2
	orientation = 0;
	angularVelocity = 0;
}


BodyData::BodyData(ofVec2f position, ofVec2f velocity, float mass)
{
	kineticEnergy = 0.5 * mass * velocity.lengthSquared();
	potentialEnergy = 0;
	
	momentOfInertia = 0.25 * mass * (mass * mass); // I = 1/4 * mass * radius^2
	angularVelocity = velocity.lengthSquared() / (mass * mass); // mass is analogous to radius for rigid 2D bodies, using squared's for efficiency
	orientation = 0 + angularVelocity;
}

BodyData::BodyData(const Body body)
{
	kineticEnergy = 0.5 * body.mass * body.velocity.lengthSquared();
	potentialEnergy = 0;
	
	momentOfInertia = 0.25 * body.mass * (body.mass * body.mass); // I = 1/4 * mass * radius^2
	angularVelocity = body.velocity.lengthSquared() / (body.mass * body.mass);
	orientation = 0 + angularVelocity;
}



// Copy constructor
BodyData::BodyData(const BodyData& other) : kineticEnergy(other.kineticEnergy), potentialEnergy(other.potentialEnergy), momentOfInertia(other.momentOfInertia), orientation(other.orientation), angularVelocity(other.angularVelocity){}


BodyData::~BodyData()
{
	kineticEnergy = 0;
	potentialEnergy = 0;
	momentOfInertia = 0;
	orientation = 0;
	angularVelocity = 0;
}




// Assignment operator
BodyData& BodyData::operator=(const BodyData& other)
{
	if (this != &other)
	{
		kineticEnergy = other.kineticEnergy;
		potentialEnergy = other.potentialEnergy;
		
		momentOfInertia = other.momentOfInertia;
		orientation = other.orientation;
		angularVelocity = other.angularVelocity;
	}
	return(*this);
}



bool BodyData::operator!=(const BodyData& other)
{
	bool notEqual = false;
	if (this == &other)
	{
		notEqual = true;
	}
	return(notEqual);
}









void BodyData:: draw(bool colorMode, const Body body)
{
	float energyNormalized = kineticEnergy / (kineticEnergy + fabs(potentialEnergy));
	
	
	ofColor energyLevel(0,255,0);
	
	if (kineticEnergy <= fabs(potentialEnergy))
	{
		if(colorMode)
		{
			energyLevel.r = energyNormalized * 2.0 * 255;
			energyLevel.g = 255;
			
			energyLevel.b = 0;
		}
		else if(!colorMode)
		{
			energyLevel.b = energyNormalized * 2.0 * 255;
			energyLevel.r = 255;
			energyLevel.g = 0;
		}
	}
	else
	{
		if(colorMode)
		{
			energyLevel.r = 255;
			energyLevel.g = 255 - (energyNormalized - 0.5) * 2.0 * 255;
			
			energyLevel.b = 0;
		}
		else if(!colorMode)
		{
			energyLevel.b = 255;
			energyLevel.r = 255 - (energyNormalized - 0.5) * 2.0 * 255;
			energyLevel.g = 0;
		}
	}
	
	
	
	
	ofFill();
	ofSetColor(energyLevel);
	ofDrawCircle(body.position.x, body.position.y, body.mass);
	
	// Draw orientation line
	ofSetColor(ofColor::white);
	float orientationLineLength = body.mass * 1;  // Length of the line can be proportional to mass or some fixed value
	ofVec2f orientationVector = ofVec2f(cos(orientation), sin(orientation)) * orientationLineLength;
	ofDrawLine(body.position, body.position + orientationVector);
}













/**
 * fourth-order runge-kutta, a fourth order method, generally offers greater accuracy
 * per time step at the cost of increased computational complexity. It approximates
 * the solution by taking a weighted average of four different approximations at each
 * time step, however this method does not preserve time symmetry, so errors in the
 * total energy of the system will increase without bound over time.
 */
inline void IntegrateRK4Force(float dt, std::vector<Body*> &bodies, ofVec2f*& bodiesAccelerations)
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		ofVec2f k1v = dt * bodiesAccelerations[i];
		
		ofVec2f k1x = dt * bodies[i]->velocity;
		
		ofVec2f k2v = dt * (bodiesAccelerations[i] + 0.5 * k1v);
		ofVec2f k2x = dt * (bodies[i]->velocity + 0.5 * k1x);
		
		ofVec2f k3v = dt * (bodiesAccelerations[i] + 0.5 * k2v);
		ofVec2f k3x = dt * (bodies[i]->velocity + 0.5 * k2x);
		
		ofVec2f k4v = dt * (bodiesAccelerations[i] + k3v);
		ofVec2f k4x = dt * (bodies[i]->velocity + k3x);
		
		
		bodies[i]->velocity = bodies[i]->velocity + (k1v + 2 * k2v + 2 * k3v + k4v) / 6;
		bodies[i]->position = bodies[i]->position + (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
	}
}





inline void ResetAccelerations(std::vector<Body*> &bodies)
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		//bodies[i]->acceleration.set(0, 0);
	}
}
/**
 * LeapFrog KDK, a second order method that handles position ('Drift') and velocity ('Kick')
 * updates in a staggered manner, making it time-reversible which prevents systematic
 * build-up in error in the total energy of the system over time. This is crucial for
 * long-term simulations where errors might accumulate. slightly less accurate and
 * significantly cheaper than RK4
 */
inline void ComputePositionAtHalfTimeStep(float dt, std::vector<Body*> &bodies) // Drift every body once before resetting acceleration
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		bodies[i]->position = bodies[i]->position + bodies[i]->velocity * (dt * 0.5);
	}
}

inline void ComputeVelocityAndPosition(float dt, std::vector<Body*> &bodies, ofVec2f*& bodiesAccelerations) //Kick-Drift-Kick Leap-Frog integration scheme
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		//KDK Leap Frog
		bodies[i]->velocity = bodies[i]->velocity + bodiesAccelerations[i] * (dt); // Kick
		
		bodies[i]->position = bodies[i]->position + bodies[i]->velocity * (dt * 0.5); // Drift
	}
}


