
Part 1 of a undergraduate directed study on the variations of the Barnes-Hut algorithm for N-body simulations. A generic 2D implementation in c++, visualized using OpenFrameworks.


<br />
<br />



Latest Updates:
      -Preparing program for large scale refactoring of structure of logic flow and implementation. To give it as an analogy, the recipe(data structure foundational logic), the ingredients(simulation entities logic), and the oven(force calculation w/approximation
      methods) are all ready to go, but the garnishing is horrific(UI is a mess).  
      - The plan-> go from 'get a working model' mindset   ==>   'clean the code and documentation' which is done to hopefully minimize confusion and just seems necessary if it 's ever going to be used as an educational resource.


<br />
<br />



https://github.com/user-attachments/assets/e80f2876-66ae-4536-9ff8-328aba6bec21



<br />
<br />



https://github.com/user-attachments/assets/2d87b186-3691-4ab4-a9a1-b8dce3caa7b2



<br />
<br />
<br />


https://github.com/user-attachments/assets/9e5a9025-6654-4f6c-804e-1369f02dc021




<br />




https://github.com/user-attachments/assets/3eb512a9-7c98-4df1-9710-0e45b7131f8d




<br />
<br />
<br />
<br />





General Information: This collection of code constitutes a specific implementation of the Barnes-Hut approximation algorithm for gravitational N-body simulations, utilizing a generic pointer-based quadtree. This version represents one variant among several explored in a broader directed study focused on the different implementations of the Barnes-Hut algortihmic technique for approximating force calculations.

Context for Current State of Program: The logic of the simulation has been completed for a long time, but because this was my first big coding project in general, my UI and visualization code was pretty ugly and not at all generalized, so I decided to completely refactor it in the hope to make it not only readable and streamlined, but also designed so that it might find use in applications unrelated to this project. Anyway, the old user-interface was completely functional despite the bad coding practices it was made in, and included a bunch of cool features that still function in the current version of the project, but are no longer accessible because the current user-interface has not yet fully integrated all of these capabilities, and while it would not take very long to add the code for all these functionalities(much quicker than typing out this readme), I'm focused on redesigning the way the UI interacts with the simulation at large, with my end goal centered around achieving a modularized implementation of the UI elements in a hierarchical structure of element management such that a single instantation of a 'TableManager' object will be responsible for all UI in the simulation and will require no additional assistance after it has been initialized with the UI elements.

Basically, TableManager manages the individual tables, the individual tables are made up of UI elements that execute similar functionalities, and the individual UI elements each handle a single task(defined when initializing using a lambda function) that is executed when the UI element is interacted with(i.e., when a button is clicked, a toggle is toggled, a slider is adjusted, etc.). Additionally, the tables also serve to group together UI elements based on broad categories of their purpose, for example, there is a table for handling visualization of parameters of the quadtree, a table for handling visualization of body data(like angular orientation), a table for handling visualization of some physics related stuff(like the gravitational vector field and the relative potential energy field), a special case table for custom galaxy creation(menus to begin, models of galaxies to distrubute bodies initial positions by to be chosen from, sliders for the number of bodies and their properties, etc.), as well as a few more tables, the main ones of which are involved in stuff like tweaking simulation parameters and interacting with bodies.

My main difficulty in making and implementing the above described UI is in defining the function callbacks for each UI element while maintaning the hierarchical structure grouping elements without necessitating too much dedicated data(that is otherwise irrelevant to the rest of the program). The other two less tricky problems are minimally inhibiting the performance of the simulation when the UI is not being used and completing all dynamic visualization with a single isolated coordinate system transform, where dynamic visualization just means the parts of the simulation that will be visualized relative to the user's dynamic configuration of the scene, basically the easiest way to understand what this means is by thinking of the window that the simulation is occuring in as being nothing but a viewing port through which you can look into the simulation, while the simulation itself can be thought of as happening on the coordinate system your looking into(kind of like how you can look at apple maps on your phone and zoom in/out and slide around, but here instead of the viewing port being your phone it's just the app window), where the affect of moving around your perspective is achieved by scaling and transforming the coordinate system(and by extension all the things in it) to reflect whatever configuration the user interaction specify.

Learn More about This Work:  [Real-Time Quadtree Barnes-Hut N-Body Simulation.pdf](https://github.com/user-attachments/files/21508718/Real-Time.Quadtree.Barnes-Hut.N-Body.Simulation.pdf)


