//
//  PhysicsVisualizationUtils.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//
//  Created by David Richardson on 6/7/24.
//

#ifndef PhysicsVisualizationUtils_hpp
#define PhysicsVisualizationUtils_hpp

#include <stdio.h>

#endif /* PhysicsVisualizationUtils_hpp */


/**
 * VectorGrid Class: A Container for Mapping and Operations on a User-Parameterized Vector of Grid Cells
 *
 * This class serves as a generic container for operations that require mapping the space of interest to be computed or operated on.
 * It's primarily used for tasks involving vector fields, such as calculating gravitational potential, and provides functionality to
 * perform operations on the grid cells themselves, such as color-coding to visualize gravitational wells.
 *
 * Class Design:
 * - The class is implemented as a singleton, ensuring only a single instance exists throughout the program's lifetime.
 * - It adheres to a two-state system design pattern, consisting of a dormant state and an active state.
 * - The dormant state is the default starting point, with standard parameter values.
 * - The active state is initiated by user interaction and persists until explicitly reset to the dormant state.
 *
 * Transitioning from Dormant to Active State:
 * - The transition begins with a unique dedicated button click.
 * - The user interacts with a menu interface to specify parameters for the vector of grid cells, such as the rectangular bounds and cell granularity.
 * - These interactions are captured as inputs and parsed as arguments to initialize the grid.
 * - The real-time simulation stops during this parameterization phase (dt = 0) to allow for accurate setup.
 *
 * Key Features:
 * - The grid accommodates operations at each point, supporting tasks like gravitational potential calculations.
 * - The grid cells can be color-coded to visualize different aspects of the system, such as gravitational wells.
 * - The class is designed for reuse, with the dormant state acting as a reset point for any new specifications.
 *
 * Example Workflow:
 * 1. User clicks a button to initiate the transition from dormant to active state.
 * 2. A prompt appears for the user to select a rectangular area as the grid bounds.
 * 3. User clicks and drags the mouse to set the top-left and bottom-right corners of the rectangular bounds.
 * 4. The user specifies the granularity of the cells through the menu interface.
 * 5. The grid is initialized with these parameters, transitioning the class to its active state.
 *
 * This class is designed to be flexible and modular, providing a robust container for mapping and operations on a user-parameterized vector of grid cells,
 * while also offering additional functionalities to support visualization and other extraneous tasks within the program.
 */
