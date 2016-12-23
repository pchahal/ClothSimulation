# ClothSimulation

The Cloth draping simulation was a project I did for my 4th year computer graphics class.  Below are some screen shots as well as the paper describing in detail how the simulation works.

# How to Use the Program

The program is very easy to use.  Under display the user can change display properties to control how rendering attributes, such as lights, camera position and drawing modes. The display of vertex/mass and springs of the cloth can be individually toggled as well.

Under Cloth Properties the user can control the physical properties of the cloth and external properties in the scene as well.  The stiffness properties for structural, shear and flexion springs, a zero stiffness turns off a spring.  Mass of the cloth points.  The force of gravity is supplied as vector.  Wind vector is a viscous fluid modeling how the cloth behaves as it moves through the air. A value of zero essentially means there is no wind or gravity present.

Under Objects the user can modify objects in the scene by changing their position and orientation and adding or deleting objects.  Currently there is support for only one object which is a box.

At the bottom of the main window are buttons for controlling the animation.

Play allows the user to start the animation. Next draws the next frame in the animation.

For detail on how the cloth simulation works read my paper below:

# Project Title :       Physically Based Model of Cloth Draping
 

# Author:        Pardeep Chahal
 

# Introduction

 

The goal of this project is to simulate the animation of a cloth object using a physically based model.  Motivations for this project come not only from cloth fabric hanging from fixed points like flags, or draping around tables but complex simulation of garments on actors in computer generated films.  Cloth behavior is determined by collisions between the cloth and the body and self collisions within the cloth itself. Many different kinds of models have been used in animation of cloth and similar deformable surfaces.  This simulation we will be using a physical model based on Newton’s motion equation applied to a particle system.  This model allows us to handle each element of the cloth separately for manipulation of position, speed and direction.  The simulation will involve a cloth suspended in air with an initial position.  Where the user provides properties of the cloth such as structural, bending and shear which in essence models different types of cloth fabrics.  As well as providing external properties which affect the behavior of the cloth such as gravity and wind forces.  Objects can also be placed in the scene by the user such as boxes which the cloth can interact with.  As the animation proceeds the cloth will behave according to its internal physical properties, the external properties of the environment and the how it responds to objects in the scene.  A typical scenario could have a cloth suspended in air falling and draping around a box placed appropriately in the scene.

 

# How it Works

 

# Modeling the Cloth:

 

The cloth object can be described by its properties and how it behaves in the real world.  We can describe the cloth as have certain properties such as tension, shearing and bending.   These properties model the internal stresses and strains of the cloth and can be controlled to model different types of cloth from ones that are soft to rigid, or can bend to some degree.  There are also external forces that an be modeled for the cloth, such as gravity and wind resistance.  The cloth is suspended by holding points on the cloth at various points, this determines the orientation and shape of the cloth in space. Threads in the cloth may be stretched or relaxed.  The points on the cloth are affected by the stress and strain rules which deform and stretch the cloth.  The points on the cloth can be treated as a system of particles each with a 3D position in space, direction and a velocity.  Each particle has a trajectory which can be calculated from all the forces acting on the particle.  The particles form sets of vertices and triangles.  The sets of vertices and triangles form the shape of the cloth.  The strains and tension between the triangles are the basis for modeling the cloth in the animation. This rules along with the external forces acting on the cloth allow it to deform and change shape.

 

Fabrics such as cloth have been modeled in different ways to describe their draping behavior.  This simulation will be based on a physically based elastically deformable model to represent the behavior of the cloth object.  This model is based on the Dynamic laws of physics which describe how objects behave when they are acted on by forces.  Some of these forces affecting our cloth object are the gravitational force acting on the falling cloth, the air or wind resistance which offsets the full effect of gravity and the frictional forces such as a cloth sliding off a box.  The basic laws controlling the cloth’s behavior are based on the Newton’s laws of motion.  We will primarily be using Newton’s second law of motion that describes the acceleration of an object depends on the forces acting on the object and it’s mass.  Often several forces are acting on an object at one time the net force is the vector sum of all of them.  For each control point in our cloth we sum all the forces acting on the cloth to determine the acceleration including all the internal and external forces of the cloth.

 

The cloth model will be composed of masses and springs, where the cloth model is an array of  mxn masses which form the control points for our cloth.

 

          vertex/mass                                          


Each mass is linked to it’s neighbor by springs.  There are three different kinds of springs:

 

Structural springs handle compression and traction stresses .Structural springs connect adjacent horizontal and vertical vertices.

 

        structural

 

 

Shear springs  handle shear stresses.  Shear springs connect vertices diagonally

 

  shear


 

Flexion springs handle stresses from the cloth bending. Flexion springs connect every other vertex in the horizontal and vertical directions.

 

             Flexion


 

# The Formulas Involved

 

The main idea is to is to determine the position of each point vertex/mass of the cloth at a time t by integrating Newton’s second law of motion.  Where the time t for each frame is kept small since we want the animation to be smooth and if the time step between frames is large a point on the cloth at time t may not be intersecting an object, but at time t + Dt a collision may have occurred which we may have missed, i.e. the cloth may have passed through say a box, this could happen if particles are traveling at high velocities. 

 

(The formulas for the force equations can be found in the attached Xavier Provot’s paper “Deformation Constraints in a Mass-Spring Model to Describe Rigid Cloth Behavior” )

 

A point Pi,j  at time t + Dt is described by

 

Pi,j(t +Dt) = Pi,j(t) + Dtv i,j(t +Dt)          

- Dt is the time step

- v i,j is the velocity, this is a vector giving the speed and direction of this point.

 

The velocity is determined by

- v i,j(t +Dt) = v i,j(t) + Dta i,j(t +Dt)

- a i,j is the acceleration, this is a vector giving the acceleration of this point

 

The acceleration is determined by rewriting Newton’s motion equation in terms of a i,j

a i,j(t +Dt) = 1/mFi,j(t)

 

- F is the net force applied to the point which is the sum of all the force vectors 

   acting on this vertex point.

- m is the mass of the point, in this model each vertex will have the same mass for

   the cloth.

 

Now all we need is to determine F which is the sum of all the forces acting on the cloth.  We calculate each force separately and then add them to give a final force vector.

There are two types of forces in our model Internal and External forces.

 

# Internal Forces

These are the forces determined by the physical properties of the cloth, the structural, shearing and flexion or bending forces and are a result of the tensions of these springs linking neighboring points of the cloth.

 

F int(Pi,j) = S (k,l) in R  K i,j,k,l, [l i,j,k,l,  - l0 i,j,k,l   (li,j,k,l  / || li,j,k,l || )]

- li,j,k,l  is the vector from the point Pi,j  to the point P k,l,

- l0 i,j,k,l  is the the natural length length of the spring linking the point Pi,j  to the point

         P k,l,

      -K i,j,k,l,  is the stiffness of the spring linking the point Pi,j  to the point P k,l, this constant 

         is given by the user for each type of spring.

 

Each Point Pi,j  has a different number of springs depending where on the cloth the point is.  Points along the edges have fewer springs whereas internal points have all springs present.

For each spring linked to the point Pi,j we substitute it into the above equation with its length , direction and stiffness constant and determine the force this spring applies to the point.  We do this for every spring linked to the point and sum to give the final internal force vector acting on the point Pi,j. 

 

 

# External Forces

External forces that will be modeled will be a gravitational force, wind resistance and a damping force.

 

The force due to gravity is a force that acts on all objects.  Our cloth suspended in the air will fall due to the force of gravity pushing downwards to the earth.  Since this force depends on mass a cloth will a larger mass will fall faster than one with a smaller mass.

Fgr(Pi,j.) = mg

            - m is the mass of the cloth for point Pi,j

                    - g is the acceleration of gravity, this is usually 9.8 m/s2

 

The force of air resistance or wind is a vector exerting a force on a object depending on the normal to the surface.  This force is greatest when the normal and the wind vector are perpendicular since this gives the greatest cross sectional area and greater air resistance.

Wind or air are a specific case of a type of Viscous fluid which can also be water or an oil.  The viscous force for wind in our model is:

Fvi(Pi,j.) = Cvi[ni,j(ufluid  - vi,j)] ni,j

- The ufluid is a vector in our case for wind

- Cvi   is a a viscous constant provided by the user.  Different constants model  

  different types of viscous fluid from water to a thick oil, oil having a higher

  viscous coefficient.

- ni,j the normal to the surface at point Pi,j

 

The force due to viscous damping. This force models the loss of mechanical energy of the cloth.

Fdis(Pi,j.) = -Cdisvi,j

- Cdis is a damping coefficient given by the user

- vi,j  is the velocity of point Pi,j

 

Again summing up all the external forces gives a net external force vector.

The two internal and external force vectors are summed to give the final force acting on the point Pi,j, this force is used in Newton’s motion equation to find the acceleration of point Pi,j, which is substituted back into the velocity equation.  Now we know the velocity for Pi,j and we can find the displacement of Pi,j at time t +Dt.

 

# Collisions

 

A cloth should not penetrate another solid object.  To model this behavior a collision detection algorithm must detect when a collision has occurred and respond to the collision by correcting the new position or speed of the points in the collision.

Between each step or frame in the animation we check if the cloth has intersected or penetrated an object, a box in our case. If a collision is detected we adjust the locations, velocities and accelerations of the particles involved.

 

The collision algorithm needs to be efficient in order to minimize computation and get a realistic smooth animation.  In a complicated scene where there are hundreds of objects,  checking for collisions can become a bottleneck.  Bounding boxes can be used to minimize checks for collision. At each step of the simulation we calculate a bounding box for the cloth, the cloth is contained within this box. Then we only need to check if the bounding box intersects with other objects in the scene.  If there is no intersection with the box, neither is there one with the cloth.  If the box does intersect an object, we need to further check if it intersects the cloth. At this point we can subdivide the box further and reiterate or have another more precise collision check which checks for intersections of the points of the cloth with the objects in the scene.  The bounding box is constructed so it bounds the cloth a time t0 and time t0 + Dt.  Thus we are checking if a collision has occurred during a given time step.  For the collision detection to be accurate the time step must be small since if the object is traveling at high velocities a collision may be missed altogether.

 

Step1.) Collision Detection.

The objects in our scene are composed of triangles, so we can check for a collision between a point on the cloth and a triangle by using the values of Pi,j(t), Pà,A,B,C

if there is a collision then Pi,j(t) will be in the triangle ABC.

 

Step 2.) Collision Response.

Collisions are handled by applying laws of friction to objects in contact. In the case of a  point collision with a triangle the basic idea is the triangle applies an opposing force to the point.  Adding this force to Pi,j(t) gives a new velocity for this point after the collision.  Using laws of friction the point could have a sliding contact, where the point moves parallel to the surface, or  a non-sliding contact where the point remains still. A friction coefficient provided by the user gives different values for friction with the cloth.

 

 

 

# Future enhancements

The following list of features would be ideally implemented:

 

·       Self collisions of the cloth allowing the cloth to exhibit more complex deformations Self collisions happen when the cloth penetrates parts of itself. Checking for self collision requires a more complex and efficient collision algorithm since we need to test a greater number of intersecting polygons and we need to handle multiple collisions at a time. Our model handles only simple collisions between two objects one at a time.  In this simulation we will ignore self collisions with the cloth although it allows us to model more complex behavior such as crumpling of the cloth.

·       The ability to compose primitives such as boxes to build more complex objects like tables, the table would have a surface and four legs each being boxes.

·       Draping of more complex objects like people

·       The Modeling of friction, currently when the cloth vertex points collide with an object their velocity become zero

 

 

 

# References

1. Xavier Provot “Deformation Constraints in a Mass-Spring Model to Describe Rigid Cloth Behavior” Institut National de Recherche en Informmatique et Automatique (INRIA) pp 3-4,6-7

 

2. Xavier Provot “Collision and self-collision handling in cloth model dedicated to design garments”  Institut National de Recherche en Informmatique et Automatique (INRIA)

pp 2-5.

 

3. J.D. Foley, A. van Dam, S. k. Feiner, J. F. Hughes “Computer Graphics: Principles and Practice” pp 1039 - 1042, c. 1996 Addison-Wesley Publishing Company Inc.

 

4. B. Eberhardt, A. Weber, W. Strasser “A Fast, Flexible, Particle-System Model for Cloth Draping”  IEEE Computer Graphics and Applications 1996, Vol. 16, No.5: September 1996, pp. 52-59

 

5. P. Volino, M. Courchesne, N.M. Thalmann “Versatile and Efficient Techniques for simulating Cloth and Other Deformable Objects” MIRALab, University of Geneva
