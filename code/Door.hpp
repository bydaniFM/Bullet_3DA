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
	/// Represents the wall that blocks the target columns from the player.
	/// The player is to unlock the Door by getting the key that unlocks it.
	class Door : public Entity
	{
		/// The Door is set to active when it moves.
		bool active;

		/// Starting position of the Door, when it is still closed.
		btVector3 starting_pos;

	public:

		/// Creates a Door.
		/// A Door has a simple Dynamic_Rigid_Body constrained with no rotation and only vertical movement.
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

		/// Moves the Door upwards when in "active" state, and stops the movement when it's open.
		void update() override
		{
			if (active)
			{
				// The velocity is set in every frame so it doesn't fall because of gravity.
				this->getRigidBody()->get()->setLinearVelocity(btVector3(0.f, 20.f, 0.f));

				if (this->getRigidBody()->get()->getWorldTransform().getOrigin().distance(starting_pos) > 50.f)
				{
					this->getRigidBody()->get()->setLinearVelocity(btVector3(0.f, 0.f, 0.f));
					// The Door is set to kinematic so it remains still.
					this->getRigidBody()->get()->setCollisionFlags(this->getRigidBody()->get()->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);

					active = false;
				}
			}

			Entity::update();
		}

		/// Starts the Door's openning.
		void open()
		{
			active = true;

			starting_pos = this->getRigidBody()->get()->getWorldTransform().getOrigin();
		}

	};
}