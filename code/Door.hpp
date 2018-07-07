/*

Author: Daniel Fernández
Date:	07/07/2018

*/

#pragma once

#include <vector>
#include <memory>

#include <btBulletDynamicsCommon.h>

#include <Scene.hpp>
#include <Entity.hpp>
#include <Rigid_Body.hpp>

using namespace std;

namespace bullet_3da
{
	class Door : public Entity
	{
		bool active;

		btVector3 starting_pos;

	public:

		Door() : Entity()
		{
			shared_ptr < Shape > shape(new Box_Shape(25.0f, 30.0f, 5.0f));
			shared_ptr<Rigid_Body> rb(new Dynamic_Rigid_Body(shape, 10.f));

			rb->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);

			//Allow movement on one axis only
			rb->get()->setLinearFactor(btVector3(0, 1, 0));
			rb->get()->setAngularFactor(btVector3(0, 0, 0));

			Entity::physics_model = rb;
			Entity::graphics_model.reset(new Model_Obj("../../assets/Door.obj"));

			active = false;
		}

		void update() override
		{
			if (active)
			{
				this->getRigidBody()->get()->setLinearVelocity(btVector3(0.f, 20.f, 0.f));

				if (this->getRigidBody()->get()->getWorldTransform().getOrigin().distance(starting_pos) > 50.f)
				{
					this->getRigidBody()->get()->setLinearVelocity(btVector3(0.f, 0.f, 0.f));
					this->getRigidBody()->get()->setCollisionFlags(this->getRigidBody()->get()->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);

					active = false;
				}
			}

			Entity::update();
		}

		void open()
		{
			active = true;

			starting_pos = this->getRigidBody()->get()->getWorldTransform().getOrigin();
		}

	};
}