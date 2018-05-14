/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <memory>

#include <btBulletDynamicsCommon.h>

#include <Shape.hpp>

using namespace std;

namespace bullet_3da
{
	class Rigid_Body
	{
	protected:
		std::shared_ptr< btRigidBody 		  > body;
		std::shared_ptr< btDefaultMotionState > state;
		std::shared_ptr< Shape   			  > shape;

	public:

		///DEPRECATED
		Rigid_Body();

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

	class Static_Rigid_Body : public Rigid_Body
	{

	public:

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

	class Dynamic_Rigid_Body : public Rigid_Body
	{

		btScalar mass;

	public:

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
