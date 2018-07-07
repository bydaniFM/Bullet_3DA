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
	class Door : public Entity
	{
		//std::clock_t time;

		bool active;

	public:

		Door() : Entity()
		{
			shared_ptr < Shape > shape(new Box_Shape(25.0f, 30.0f, 5.0f));
			shared_ptr<Rigid_Body> rb(new Dynamic_Rigid_Body(shape, 10.f));

			//Allow movement on one axis only
			rb->get()->setLinearFactor(btVector3(1, 0, 0));
			rb->get()->setAngularFactor(btVector3(0, 0, 0));

			Entity::physics_model = rb;
			Entity::graphics_model.reset(new Model_Obj("../../assets/Door.obj"));

			active = false;

			//time = std::clock();
		}

		void update() override
		{
			//time = std::clock();
			this->getRigidBody()->get()->setLinearVelocity(btVector3(glm::sin(std::clock() * 0.0005f) * 10.f, 0.f, 0.f));

			Entity::update();
		}

	};
}