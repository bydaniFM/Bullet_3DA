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
		std::clock_t time;

	public:

		Sphere(Scene * scene, btVector3 position, btVector3 force) : Entity()
		{
			shared_ptr < Shape > shape(new Sphere_Shape(1.5f));
			shared_ptr<Rigid_Body> rb(new Dynamic_Rigid_Body(shape, 2.f));
			rb->get()->getWorldTransform().setOrigin(position);
			rb->get()->setRestitution(0.f);
			rb->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);

			physics_model = rb;
			graphics_model.reset(new glt::Model_Obj("../../assets/Ball.obj"));

			rb->get()->applyCentralImpulse(force);

			time = std::clock();
		}

		void update() override
		{
			if (std::clock() - time > 2.f * CLOCKS_PER_SEC)
			{
				delete this;
			}

			Entity::update();
		}

	};
}