/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <ctime>
#include <memory>

#include <Entity.hpp>

namespace bullet_3da
{
	class Sphere : public Entity
	{
		bool active;

		std::clock_t time;

		//shared_ptr < Rigid_Body > this->getRigidBody();

		int flags;


	public:

		Sphere(/*Scene * scene, btVector3 position, btVector3 force*/) : Entity()
		{
			shared_ptr < Shape > shape(new Sphere_Shape(1.5f));
			shared_ptr < Rigid_Body > rb(new Dynamic_Rigid_Body(shape, 2.f));
			rb->get()->setRestitution(0.f);
			rb->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);

			physics_model = rb;
			graphics_model.reset(new glt::Model_Obj("../../assets/Ball.obj"));

			flags = this->getRigidBody()->get()->getCollisionFlags();
			this->getRigidBody()->get()->setCollisionFlags(flags | btCollisionObject::CF_KINEMATIC_OBJECT);

			active = false;

		}

		void update() override
		{
			if (active)
			{
				//The rigid body "deactivates" after 5 seconds
				if (std::clock() - time > 5.f * CLOCKS_PER_SEC)
				{
					active = false;

					//The rigid body is stopped and set to kinematic to save resources
					this->getRigidBody()->get()->setLinearVelocity(btVector3(0.f, 0.f, 0.f));
					this->getRigidBody()->get()->setAngularVelocity(btVector3(0.f, 0.f, 0.f));
					this->getRigidBody()->get()->setCollisionFlags(flags | btCollisionObject::CF_KINEMATIC_OBJECT);

					this->getModel()->set_visible(false);
				}
			}

			Entity::update();
		}

		void launch(btVector3 position, btVector3 force)
		{
			active = true;

			//The rigidbody is set back to non-kinematic
			this->getRigidBody()->get()->setCollisionFlags(flags);

			this->getRigidBody()->get()->getWorldTransform().setOrigin(position);
			this->getRigidBody()->get()->applyCentralImpulse(force);

			this->getModel()->set_visible(true);
			
			time = std::clock();
		}

		bool getActive()
		{
			return active;
		}

	};
}