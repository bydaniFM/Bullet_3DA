/*

Author: Daniel Fernández
Date:	04/05/2018

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
	class Tank : public Entity
	{
	public:

		Tank(Scene * scene) : Entity(scene)
		{
			shared_ptr < Shape > shape(new Box_Shape(10.0f, 10.0f, 10.0f));
			shared_ptr<Rigid_Body> rb(new Dynamic_Rigid_Body(shape, 100.f));
			//rb->get()->getWorldTransform().setOrigin(btVector3(0, 10.f, 0));
			Entity::physics_model = rb; //Rigid_Body(shape);

			Entity::graphics_model.reset(new Model_Obj("../../assets/Tank.obj"));
		}


	};
}