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
	class Physics_World
	{

		shared_ptr< btDiscreteDynamicsWorld >	dynamicsWorld;

		vector< shared_ptr< Rigid_Body >>				bodies;
		vector< shared_ptr< btDefaultMotionState > >	motionStates;
		vector< shared_ptr< btCollisionShape     > >	collisionShapes;

	public:

		Physics_World()
		{
			btDefaultCollisionConfiguration 	collisionConfiguration;
			btCollisionDispatcher 				collisionDispatcher(&collisionConfiguration);
			btDbvtBroadphase 					overlappingPairCache;
			btSequentialImpulseConstraintSolver constraintSolver;

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

		void add(shared_ptr< Rigid_Body > & body)
		{
			bodies.push_back(body);

			dynamicsWorld->addRigidBody(body->get());
		}

		void step(float time)
		{
			dynamicsWorld->stepSimulation(time);
		}

		shared_ptr<btDiscreteDynamicsWorld> getDynamicsWorld()
		{
			return dynamicsWorld;
		}

	};
}
