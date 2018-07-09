/*

Author: Daniel Fernández
Date:	07/07/2018

*/

#pragma once

#include <ctime>
#include <vector>
#include <memory>

#include <btBulletDynamicsCommon.h>

#include <Scene.hpp>
#include <Entity.hpp>
#include <Rigid_Body.hpp>

using namespace std;

namespace bullet_3da
{
	/// Represents a moving platform in which the tank or other objects can stand.
	class Platform : public Entity
	{

	public:

		/// Creates a new Platform.
		/// It consists in a Dynamic_Rigid_Body constrained to move in only one axis.
		Platform() : Entity()
		{
			shared_ptr < Shape > shape(new Box_Shape(30.0f, 5.0f, 25.0f));
			shared_ptr<Rigid_Body> rb(new Dynamic_Rigid_Body(shape, 5.f));

			rb->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);

			//Allow movement on one axis only
			rb->get()->setLinearFactor(btVector3(1, 0, 0));
			rb->get()->setAngularFactor(btVector3(0, 0, 0));

			//rb->get()->setFriction(2.f);

			Entity::physics_model = rb;
			Entity::graphics_model.reset(new Model_Obj("../../assets/Platform.obj"));
		}

		/// Moves the platform constantly using a sine funciton.
		void update() override
		{
			//time = std::clock();
			this->getRigidBody()->get()->setLinearVelocity(btVector3(glm::sin(std::clock() * 0.0005f) * 10.f, 0.f, 0.f));

			Entity::update();
		}

	};
}