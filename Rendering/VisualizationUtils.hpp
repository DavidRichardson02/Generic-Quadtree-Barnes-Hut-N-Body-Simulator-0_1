//  VisualizationUtils.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/*
 * VisualizationUtils: Utility functions for visualization of various simualtion parameters, including: visualizing bodies of the simulation,
 *
 * Description:
 * This file defines a collection of utility functions designed to assist with
 * the the visualization required in an N-Body simulation,
 *
 */


#pragma once
#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"
#include "NavigationalComponents.hpp"
#include "DrawingUtilities.hpp"
#include "SequenceContainers.hpp"
#include "SimulationEntities.hpp"
#include "ObjectPool.hpp"
#include "Quadtree.hpp"
#include "PhysicsLogic.hpp"
#include "ofMain.h"






// ------------- Bodies Visualization ------------------
/// \{

static inline void VisualizeBodies(std::vector<Body*>& bodies, bool visualizeBodyEnergyGradient);

static inline void VisualizeBodyData(std::vector<Body*>& bodies, std::vector<BodyData*>& bodiesData, bool visualizeBodyEnergyGradient);


static inline void VisualizeBodiesAngularOrientation(std::vector<Body*>& bodies, const ofVec2f* bodiesAccelerations)
{
	//cout<<"\n\n bodies.size(): " << bodies.size();
	for (size_t i = 0; i < bodies.size(); i++)
	{
		
		float momentOfInertia = 0.25 * bodies[i]->mass * (bodies[i]->mass * bodies[i]->mass); // I = 1/4 * mass * radius^2
		float angularVelocity = bodies[i]->velocity.lengthSquared() / (bodies[i]->mass * bodies[i]->mass);
		float orientation = 0 + angularVelocity;
		
		
		float d = 0.5 * bodies[i]->mass;  // off-center distance
		
		// Assume a radius vector from center to the point where the force is applied.
		// This is a simplification; in a real scenario, you'll need to determine this based on the physical situation.
		ofVec2f radialVector(d, 0);  // Example: assuming d(force applied) is along x-axis, you can rotate this based on body orientation
		
		// Calculate torque due to gravitational forces (using 2D cross product, which yields a scalar)
		float torque = radialVector.x * bodiesAccelerations[i].y * bodies[i]->mass - radialVector.y * bodiesAccelerations[i].x * bodies[i]->mass;
		
		
		// Calculate angular acceleration
		float angularAcceleration = torque / momentOfInertia;
		
		// Update angular velocity (using Euler integration)
		angularVelocity += angularAcceleration * 0.01; // Assuming a small time step of 0.01
		
		
		// Update orientation (angle), assuming it starts from an initial angle of 0
		// (assuming no external torques for simplicity)
		orientation += angularVelocity * 0.01; // Assuming a small time step of 0.01
		
		
		// Draw orientation line
		ofSetColor(0, 0, 255); // ofColor::white
		ofSetLineWidth(1);
		float orientationLineLength = bodies[i]->mass * log2(bodies[i]->velocity.length());  // Length of the line can be proportional to mass or some fixed value
		ofVec2f orientationVector = ofVec2f(cos(orientation), sin(orientation)) * orientationLineLength;
		ofDrawLine(bodies[i]->position, bodies[i]->position + orientationVector);
	}
	
}



static inline void RenderSimulation(Quadtree *&rootQuadtree, std::vector<Body*>& bodies, std::vector<BodyData*>& bodiesData);
/// \}



// ------------- Quadtree Visualization ------------------
/// \{
static inline void VisualizeQuadtreeBounds(Quadtree *&rootQuadtree)
{
	if(rootQuadtree == nullptr)
	{
		std::cout << "\n\nRoot Quadtree is null" << std::endl;
		return;
	}
	if (rootQuadtree->hasChildren)
	{
		for (int i=0; i<4;i++)
		{
			if (rootQuadtree->children[i] != nullptr)
			{
				VisualizeQuadtreeBounds(rootQuadtree->children[i]);
			}
		}
	}
	
	ofNoFill();
	ofSetLineWidth(0.75);
	ofSetColor(255, 255, 255, 96.75);
	ofDrawRectangle(rootQuadtree->bounds);  // draw the bounding box of the node
}



static inline void VisualizeQuadtreeCentresOfMass(Quadtree *&rootQuadtree)
{
	if (rootQuadtree->hasChildren)
	{
		for (int i=0; i<4;i++)
		{
			if (rootQuadtree->children[i] != nullptr)
			{
				VisualizeQuadtreeCentresOfMass(rootQuadtree->children[i]);
			}
		}
	}
	
	//ofFill();
	//ofSetColor(89, 66, 192);
	//ofDrawTriangle(ofVec2f(rootQuadtree->centerOfMass.x-25, rootQuadtree->centerOfMass.y+25), ofVec2f(rootQuadtree->centerOfMass.x+25, rootQuadtree->centerOfMass.y+25), ofVec2f(rootQuadtree->centerOfMass.x, rootQuadtree->centerOfMass.y+25));
	
	//ofSetColor(118, 101, 133);
	//ofDrawCircle(rootQuadtree->centerOfMass, log2(rootQuadtree->bodyCount));
	//ofDrawBitmapString("Bodies: " + ofToString(rootQuadtree->bodyCount), 1, rootQuadtree->centerOfMass.x, rootQuadtree->centerOfMass.y);
	
	
	
	if(rootQuadtree->nodeBody && rootQuadtree->hasChildren) // Draw a line from this node's body to this node's center of mass
	{
		ofFill();
		ofSetColor(118, 101, 133);
		ofDrawCircle(rootQuadtree->centerOfMass, log2(rootQuadtree->bodyCount));
		ofDrawBitmapString(ofToString(rootQuadtree->bodyCount), rootQuadtree->centerOfMass.x, rootQuadtree->centerOfMass.y);
		
		
		ofNoFill();
		//ofSetLineWidth(log2(rootQuadtree->bodyCount));
		
		
		int opacity = ofClamp(rootQuadtree->depth * log2(rootQuadtree->bodyCount), 0, 255);
		ofColor comColors = ofColor(0, 0, 255, opacity);
		comColors.g = opacity;
		
		
		
		ofSetColor(comColors);
		
		
		ofDrawRectangle(rootQuadtree->bounds);
		
		
		
		ofSetColor(255, 255, 255, 96.75);
		ofDrawLine(rootQuadtree->centerOfMass, rootQuadtree->nodeBody->position);
	}
}



static inline void VisualizeQuadtreeNodeProperties(Quadtree *&rootQuadtree); //Display the node's properties, including: depth, quadrant, mass, body count, etc.

static inline void VisualizeQuadtreeAABB(Quadtree *&rootQuadtree); //Display the "neighbourhood's" of the bodies (rectangles around bodies that are used for broad phase collision detection, will light up when they intersect another body neighbourhood, any node bounds, and of course other bodies)


/// \}








/**
 * VisualizeRelativePotentialEnergyField: Computing the gravitational potential at each point on a grid and color-coding these points using the Viridis color map to visualize "gravitational wells".
 *
 * @param potentialGrid The      potential energy in the system.
 * @param minPotential The minimum potential energy in the system.
 * @param maxPotential The maximum potential energy in the system.
 * @param WIDTH The specified width of grid cells, together with HEIGHT controls the bounds of the energy field visualization
 * @param HEIGHT The specified height of grid cells, together with WIDTH controls the bounds of the energy field visualization
 * @param CELLSIZE The specified size of grid cells, controls the granularity of the potential energy field visualization across the bounds specified by WIDTH and HEIGHT
 */
static inline void VisualizeRelativePotentialEnergyField(std::vector<std::vector<float>> &potentialGrid, std::vector<Body*>& bodies, double &G, float &minPotential, float &maxPotential, RectangularGridDragSelection vectorGrid);

static inline void PrepareRelativePotentialEnergyField(std::vector<Body*>& bodies, double &G, RectangularGridDragSelection vectorGrid);

/// \}







// ------------- Visualize Gravitational Vector Field ------------------
/// \{

/**
 * VisualizeGravitationalField: Computing the gravitational potential at each point on a grid and color-coding these points using the Viridis color map to visualize "gravitational wells".
 *
 * @param bodies The      potential energy in the system.
 * @param bodiesAccelerations The minimum potential energy in the system.
 * @param boundsSize The maximum potential energy in the system.
 * @param gridSpacing The specified width of grid cells, together with HEIGHT controls the bounds of the energy field visualization
 * @param HEIGHT The specified height of grid cells, together with WIDTH controls the bounds of the energy field visualization
 * @param CELLSIZE The specified size of grid cells, controls the granularity of the potential energy field visualization across the bounds specified by WIDTH and HEIGHT
 */
static inline void VisualizeGravitationalVectorField(const std::vector<Body*>& bodies, const ofVec2f* bodiesAccelerations, RectangularGridDragSelection vectorGrid);

/// \}





// ------------- Class For Visualization ------------------
/// \{
//class VisualizationUtils
//{
//
//};
/// \}







static inline void PrepareRelativePotentialEnergyField(std::vector<Body*>& bodies, double &G, RectangularGridDragSelection vectorGrid)
{
	//double G = 6.67430; // Define the gravitational constant
	float minPotential = 0, maxPotential = 10000; // Define the minimum and maximum potential energy in the system
	float boundsSize = 1000.0f; // Define the bounds size for the grid
	float CELLSIZE = 6; // Define the cell size for the grid
	std::vector<std::vector<float>> potentialGrid; // Define the potential grid
	
	
	

	VisualizeRelativePotentialEnergyField(potentialGrid, bodies, G, minPotential, maxPotential, vectorGrid); // Call the function to visualize the relative potential energy field
}

/**
 * VisualizeRelativePotentialEnergyField
 *
 * Computing the gravitational potential at each point on a grid and color-coding these points using the Viridis color map to visualize "gravitational wells".
 * This function visualizes the relative potential energy field by computing the gravitational potential at each point on a grid and color-coding these points using the Viridis color map to visualize "gravitational wells".
 * It first initializes the potentialGrid with appropriate dimensions, then calculates the total potential at each point in the grid. The total potential is the sum of the potentials due to each body in the system.
 * The potential due to a body is calculated using the formula: -G * mass / distance, where G is the gravitational constant, mass is the mass of the body, and distance is the distance from the body to the point.
 * The function then updates the min and max potentials, which are used to normalize the potentials for visualization.
 * Finally, the function draws the potential field by color-coding each point on the grid based on its potential.
 *
 * @param potentialGrid The potential energy grid of the system.
 * @param bodies The bodies in the system.
 * @param G The gravitational constant.
 * @param minPotential The minimum potential energy in the system.
 * @param maxPotential The maximum potential energy in the system.
 * @param boundsSize The size of the bounds of the grid.
 * @param CELLSIZE The size of each cell in the grid.
 */
static inline void VisualizeRelativePotentialEnergyField(std::vector<std::vector<float>> &potentialGrid, std::vector<Body*>& bodies, double &G, float &minPotential, float &maxPotential, RectangularGridDragSelection vectorGrid)
{
	// Check if bodies vector is empty
	if(bodies.empty())
	{
		perror("\n\nError in 'VisualizeRelativePotentialEnergyField', bodies vector is empty.\n");
		exit(1);
	}
	float boundsSize = vectorGrid.gridBounds.width;
	float CELLSIZE = vectorGrid.granularity;
	
	
	/// Initialize potentialGrid with appropriate dimensions
	potentialGrid.resize(boundsSize/CELLSIZE, std::vector<float>(boundsSize/CELLSIZE, 0));
	
	/// Reset min and max potentials
	minPotential = std::numeric_limits<float>::max();
	maxPotential = std::numeric_limits<float>::min();
	
	/// Calculate the total potential at each point in the grid
	for (int x = -boundsSize*0.5; x < boundsSize; x += CELLSIZE)
	{
		for (int y = -boundsSize*0.5; y < boundsSize; y += CELLSIZE)
		{
			/// Calculate the total potential at (x, y)
			ofVec2f point(x, y);
			float totalPotential = 0;
			
			/// Sum up the potentials due to each body
			for(const auto& body : bodies)
			{
				float dist = point.distance(body->position);
				
				if(dist > 0)
				{
					float potential = -G * body->mass / dist;  // Calculate the potential due to the body
					totalPotential += potential;
				}
			}
			
			potentialGrid[fabs(x)/CELLSIZE][fabs(y)/CELLSIZE] = totalPotential; // Update the potential at this grid, ensuring the specified indices of the 2D vector are valid
			
			
			/// Update min and max potentials
			minPotential = std::min(minPotential, totalPotential);
			maxPotential = std::max(maxPotential, totalPotential);
		}
	}
	
	
	
	/// Draw the potential field
	for (int x = -boundsSize*0.5; x < boundsSize; x += CELLSIZE)
	{
		for (int y = -boundsSize*0.5; y < boundsSize; y += CELLSIZE)
		{
			/// Get the color based on the computed potential
			ofColor potentialFieldColor = GetColorFromPotential(minPotential, maxPotential, potentialGrid[fabs(x)/CELLSIZE][fabs(y)/CELLSIZE]);
			
			
			/// Draw a rectangle at the point with the color
			ofNoFill();
			ofSetColor(potentialFieldColor);
			ofDrawRectangle(x, y, CELLSIZE, CELLSIZE);
		}
	}
}




/**
 * This function visualizes the gravitational field of a system of bodies.
 * It calculates the gravitational field at each point in a grid, taking into account the influence of all bodies.
 * The field is then visualized by drawing arrows representing the direction and magnitude of the field at each point.
 */
static inline void VisualizeGravitationalVectorField(const std::vector<Body*>& bodies, const ofVec2f* bodiesAccelerations, RectangularGridDragSelection vectorGrid)
{
	ofVec2f gField; // gravitational field at a given point
	ofVec3f point;  // point in the grid
	ofVec3f arrowHead;
	
	
	float boundsSize = vectorGrid.gridBounds.width;
	float CELLSIZE = vectorGrid.granularity;
	
	/// Iterate over the grid
	for (int x = -boundsSize*0.5; x < boundsSize; x += CELLSIZE)
	{
		for (int y = -boundsSize*0.5; y < boundsSize; y += CELLSIZE)
		{
			point.set(x, y, 0);
			gField.set(0, 0);
			
			/// Sum up the influences from all bodies
			for (size_t i = 0; i < bodies.size(); ++i)
			{
				float distance = point.distance(bodies[i]->position);
				if (distance < epsilon) continue;  // Skip over the body itself
				
				
				ofVec2f direction = (bodies[i]->position - point).getNormalized();  // Calculate the direction of the influence
				gField += direction * bodiesAccelerations[i].length() / (distance * distance); // Add the influence to the total gravitational field at this point
			}
			
			
			/// Draw the vector field at this point
			ofSetColor(255, 0, 255);
			arrowHead = point + gField.getNormalized() * 10;  // Scale the vector for visualization
			ofDrawArrow(point, arrowHead, 3);
		}
	}
}

