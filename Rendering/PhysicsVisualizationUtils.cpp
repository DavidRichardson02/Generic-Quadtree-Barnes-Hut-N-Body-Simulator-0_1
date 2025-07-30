//  PhysicsVisualizationUtils.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1

/**
 * The utilities provided in this file are tightly coupled with the specific implementation details of
 * the user-interface for handling dynamic interactions with the physics simulation. They rely on the
 * methodologies/functionalities provided by my OpenFrameworks user-interface library in order to facilitate
 * message passing between the user-experience and the simulation specifc physics logic in order to visualize
 * various physics phenomena on demand(most of the really cool/useful visualization options introduce a VERY
 * heavy computational burden to the simulation, relative to the main performance bottleneck, and focal point of the program, the force approximations).
 */


#include "PhysicsVisualizationUtils.hpp"





/**
 Please help me create a vector grid class to serve as a container for mapping and accomodating operations at each point on a user-parameterized vector of grid cells,
 this class is designed to be a generic container for operations necessitating a mapping of the space of interest to be computed for/on(here used almost exclusively for
 stuff w/vector fields, i.e., gravitational potential, etc.) while also providing functionality to perform operations on the grid cells themselves, such as color-coding
 the cells to visualize the "gravitational wells" of the system.
 
 
 furthermore, due to the standalone implementation details unique to the context of this program, the deployment of class object will be
 made to generate only a single instantiation that will last the lifetime of the program,
 
 
 
 
 
 
 
 while the core logic of the class will remain largely unaffected in it's primary purpose, this design is intended to adhere to a two-state singleton design pattern,
 characterized by the on demand reuse/recycling of a single instantiation of a global class object that will persist in dormant/passive state until the explicit commencement
 of the active state(preceded by completion of the parameterization phase
whereupon the object will be in a passive/dormant state until the user provides the stimuli for the class to transition between these states.
 
 either it's default dormant state or for the lifetime of the application
 
 class which lasts the lifetime of the application and will transition from a dormant to
 an active state upon the completion of a implementation specific parameterization phase(a complex process involving a series of nuanced steps to guide the user to
 provide arguments with which the default dormant grid will be reinitialized with the grid)
 

 
 class will adhere to a two-state system design pattern consisting of a dormant state and an active state, where the dormant state acts as the starting
 
 
 
 
 
 
 , where the active state of the object is the exception, the dormant state acts as the starting
 point with parameters always set to some standard acting as the zeroing of the object, the transition from dormant to active is preceded by a program unique
 paramaterization phase which endeavors to extract paramaterization arguments from user-interactions to setup the 'vector field', involves a nuanced series of
 steps taken for the purpose of returning a single string of formatted data to be used as arguments for initializing/reinitializing the object and is a methodology outside the scope of this class(i.e., the parameterization phase focuses on parsing user-interactions to extract the arguments for initializing the active state)
 
 
 , where the commencement of the active state will not functionally
 begin until the halting of all user-interactions in the application has been ensured, 
 
 
 
 where this active state will persist until it's explicit endtime event is triggered by the user clicking a dedicated button to transition the object back to the
 dormant state by resetting the parameters of the object to the standard values of the dormant state such that the object will be ready for reuse.
 

 
 
 
 
 
 ,
 as this vector of grid cells will be designed to accomodate extraneous functionalities for the program that are unnessecary to the main physics simulation, as well as
 computationally bothersome, the primary strategy for implementation be to create the class to always be in either a dormant state or an active state,
 where the dormant state exists to act as a starting point, as well as the point to reset to, for any of the potential specifications for instantiation of the object
 and the transition to the active state will have the real-time simulation completely stop it's evolution(dt=0) and enter a unique parameterization phase
 where the user will be able to specify the parameters of the vector of grid cells, such as the rectangular bounds of the grid, the granularity of the cells, etc.
 
 
 This process of transitioning the class object(single, global, lasts the application lifetime) from the dormant state
 to the active state will be comprised of a series of nuanced steps guiding the user to initialize the grid, the high level overview of the process is as follows:
 - will be initiated by clicking a unique dedicated button
 - will be progressed through by the user interacting with the menu interface to specify the parameters of the vector of grid cells, where the user-interactions will be captured as inputs to a string which will be parsed as an argument for
 ... will continue to persist/evolve as a function(and/or constuctor?) argument for whatever task it was assigned to act as a container for representing a vector field for
 

 
 
 
 
 
 
 as a text prompt appears telling the user to select a rectangular area to serve as the bounds of the vector of grid cells(by clicking mouse somewhere on the 
 navigable coordinate system to set an anchor point for the top left corner, then dragging the mouse to be released at the point which will act as the anchor
 for the bottom right corner of the rectangular bounds, as well as the granularity of the cells() user interacts with the menu interface
 to specify the parameters of the vector of grid cells(user provides the stimuli for the class to transition between these states.


 */
