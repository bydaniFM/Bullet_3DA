/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <vector>
#include <memory>

#include <btBulletDynamicsCommon.h>

#include <Rigid_Body.hpp>

using namespace std;

namespace bullet_3da
{
	/// Represents a physics world that uses Bullet 3D.
	class Physics_World
	{
		/// Bullet's world
		shared_ptr< btDiscreteDynamicsWorld >	dynamicsWorld;

		//Not in use right now
		vector < shared_ptr< Rigid_Body >>				bodies;
		vector < shared_ptr < btHingeConstraint > >		constraints;

		btDefaultCollisionConfiguration 	collisionConfiguration;
		btCollisionDispatcher 				collisionDispatcher;
		btDbvtBroadphase 					overlappingPairCache;
		btSequentialImpulseConstraintSolver constraintSolver;

	public:

		/// Creates a new Physics_World and sets its gravity to 10.
		Physics_World() : collisionDispatcher(&collisionConfiguration)
		{
			dynamicsWorld.reset
			(
				new btDiscreteDynamicsWorld
				(
					&collisionDispatcher,
					&overlappingPairCache,
					&constraintSolver,
					&collisionConfiguration
				)
			);

			dynamicsWorld->setGravity(btVector3(0, -10, 0));
		}
		~Physics_World()
		{
			dynamicsWorld.reset();
		}

		/// Adds a new body to the simulation world.
		/// @param the body to insert into the world.
		void add(shared_ptr< Rigid_Body > & body)
		{
			bodies.push_back(body);

			dynamicsWorld->addRigidBody(body->get());
		}

		/// Performs the physics simulation of a frame.
		/// @ param time since the last simulation.
		void step(float time)
		{
			dynamicsWorld->stepSimulation(time);
		}

		shared_ptr<btDiscreteDynamicsWorld> getDynamicsWorld()
		{
			return dynamicsWorld;
		}

		/// Adds a hinge constraint into the world.
		/// @param The btHingeConstraint to add into the world.
		void addConstraints(btHingeConstraint * hinge)
		{
			constraints.push_back(shared_ptr<btHingeConstraint>(hinge));
			dynamicsWorld->addConstraint(hinge);
		}

	};
}
