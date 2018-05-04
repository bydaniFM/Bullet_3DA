/*
    Bullet Continuous Collision Detection and Physics Library
    Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it freely,
    subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
       If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    This is the official 'Hello, World' example cleaned up for additional simplicity and clarity.
*/

#include <memory>
#include <vector>
#include <iostream>
#include <btBulletDynamicsCommon.h>

using namespace std;

int main ()
{
    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                       PHYSISCS WORLD INITIALIZATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    // Collision configuration contains default setup for memory, collision setup.
    // Advanced users can create their own configuration.

    btDefaultCollisionConfiguration collisionConfiguration;

    // Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded).

    btCollisionDispatcher collisionDispatcher(&collisionConfiguration);

    // btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.

    btDbvtBroadphase overlappingPairCache;

    // The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded).

    btSequentialImpulseConstraintSolver constraintSolver;

    // Create and configure the physiscs world:

    btDiscreteDynamicsWorld dynamicsWorld
    (
        &collisionDispatcher,
        &overlappingPairCache,
        &constraintSolver,
        &collisionConfiguration
    );

    dynamicsWorld.setGravity (btVector3(0, -10, 0));

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                            RIGID BODIES SETUP
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    // Keep track of the shapes, states and rigid bodies.
    // Make sure to reuse collision shapes among rigid bodies whenever possible!

    vector< shared_ptr< btRigidBody          > > rigidBodies;
    vector< shared_ptr< btDefaultMotionState > > motionStates;
    vector< shared_ptr< btCollisionShape     > > collisionShapes;

    // GROUND
    {
        shared_ptr< btCollisionShape > shape(new btBoxShape(btVector3(50, 50, 50)));

        btTransform transform;
        transform.setIdentity ();
        transform.setOrigin (btVector3(0, -56, 0));

        // Using motionstate is optional for static objects.

        shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
        btRigidBody::btRigidBodyConstructionInfo info (0, state.get (), shape.get ());
        shared_ptr< btRigidBody >                body (new btRigidBody(info));

        // Add the body to the dynamics world.

        dynamicsWorld.addRigidBody (body.get ());

        // Save the smart pointers for automatic cleanup.

        rigidBodies    .push_back (body );
        motionStates   .push_back (state);
        collisionShapes.push_back (shape);
    }

    // DYNAMIC OBJECT
    {
        shared_ptr< btCollisionShape > shape(new btSphereShape(btScalar(1.)));

        // Create Dynamic Objects.

        btTransform transform;
        transform.setIdentity ();
        transform.setOrigin (btVector3(2, 10, 0));

        btScalar  mass = 1.f;
        btVector3 localInertia(0, 0, 0);

        shape->calculateLocalInertia (mass, localInertia);

        // Using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

        shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
        btRigidBody::btRigidBodyConstructionInfo info (mass, state.get (), shape.get (), localInertia);
        shared_ptr< btRigidBody >                body (new btRigidBody(info));

        dynamicsWorld.addRigidBody (body.get ());

        // Save the smart pointers for automatic cleanup.

        rigidBodies    .push_back (body );
        motionStates   .push_back (state);
        collisionShapes.push_back (shape);
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                                SIMULATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    for (int frame = 0; frame <= 60; frame++)
    {
        // Perform the simulation:

        dynamicsWorld.stepSimulation (1.f / 60.f);

        // Dump the physics world state:

        cout << "frame " << frame << ":" << endl;

        for (int objectIndex = 0, objectCount = dynamicsWorld.getNumCollisionObjects (); objectIndex < objectCount; objectIndex++)
        {
            btCollisionObject * object = dynamicsWorld.getCollisionObjectArray ()[objectIndex];
            btRigidBody       * body   = btRigidBody::upcast (object);
            btTransform         transform;

            transform = object->getWorldTransform ();

            cout << "  body " << objectIndex << " position = " << transform.getOrigin ().getX () << ", " << transform.getOrigin ().getY () << ", " << transform.getOrigin ().getZ () << endl;
        }
    }

    cin.get ();

    return 0;
}
