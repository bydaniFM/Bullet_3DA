/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <memory>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <Shape.hpp>

using namespace std;

namespace bullet_3da
{
	/// Encapsulates a Bullet's rigid body and it's components.
	/// Base class of a static or a dynamic object.
	class Rigid_Body
	{
	protected:
		/// Bullet's btRigidBody.
		std::shared_ptr< btRigidBody 		  > body;
		/// Bullet's btDefaultMotionState.
		std::shared_ptr< btDefaultMotionState > state;
		/// Shape of the Rigid_Body.
		std::shared_ptr< Shape   			  > shape;

	public:

		///DEPRECATED
		Rigid_Body();

		/// Creates a new Rigid_Body given a Shape.
		/// @param Rigid_Body's Shape.
		Rigid_Body(std::shared_ptr< Shape > & shape) : shape(shape)
		{
			btTransform transform;

			transform.setIdentity();

			state.reset(new btDefaultMotionState(transform));
		}

		virtual ~Rigid_Body() = default;

		btRigidBody * get()
		{
			//return body();
			return body.get();
		}

	};

	///////////////////////////////////////////////////////////////////////////////////////////////

	/// Rigid_Body with mass 0, so it can't be moved in the physics simulaiton.
	class Static_Rigid_Body : public Rigid_Body
	{

	public:

		/// Creates a new Static_Rigid_Body.
		/// Creates the btRigidBody with mass 0.
		/// @param Shape of the body.
		Static_Rigid_Body(std::shared_ptr< Shape > & shape) : Rigid_Body(shape)
		{
			btRigidBody::btRigidBodyConstructionInfo info
			(
				0, state.get(), shape.get()->get()
			);

			body.reset(new btRigidBody(info));
		}

	};

	///////////////////////////////////////////////////////////////////////////////////////////////

	/// Encapsulates a btRigidBody with mass.
	class Dynamic_Rigid_Body : public Rigid_Body
	{
		/// Mass of the body.
		btScalar mass;

	public:

		/// Creates a btRigidBody.
		/// @param shape of the body.
		/// @param mass of the body.
		Dynamic_Rigid_Body(std::shared_ptr< Shape > & shape, float mass)
			:
			Rigid_Body(shape), mass(btScalar(mass))
		{
			btVector3 localInertia(0, 0, 0);

			shape->get()->calculateLocalInertia(mass, localInertia);

			btRigidBody::btRigidBodyConstructionInfo info
			(
				mass, state.get(), shape.get()->get(), localInertia
			);

			body.reset(new btRigidBody(info));
		}
	};
}
