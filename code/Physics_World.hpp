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

		vector < shared_ptr< Rigid_Body >>				bodies;
		vector < shared_ptr < btHingeConstraint > >		constraints;
		/*vector< shared_ptr< btDefaultMotionState > >	motionStates;
		vector< shared_ptr< btCollisionShape     > >	collisionShapes;*/

		btDefaultCollisionConfiguration 	collisionConfiguration;
		btCollisionDispatcher 				collisionDispatcher;
		btDbvtBroadphase 					overlappingPairCache;
		btSequentialImpulseConstraintSolver constraintSolver;

	public:

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

		void add(shared_ptr< Rigid_Body > & body)	//& body
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

		void addConstraints(btHingeConstraint * hinge)
		{
			constraints.push_back(shared_ptr<btHingeConstraint>(hinge));
			dynamicsWorld->addConstraint(hinge);
		}

	};
}
