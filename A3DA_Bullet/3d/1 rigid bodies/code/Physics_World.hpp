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

		std::unique_ptr< btDiscreteDynamicsWorld >	dynamicsWorld;
		std::vector< std::shared_ptr< Rigid_Body >> bodies;

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

	};
}
