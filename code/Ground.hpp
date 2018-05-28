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
	class Ground: public Entity
	{
	public:

		Ground(Scene * scene): Entity(scene)
		{
			shared_ptr < Shape > shape(new Box_Shape(150.0f, 50.0f, 100.0f));
			shared_ptr<Rigid_Body> rb(new Static_Rigid_Body(shape));
			//rb->get()->getWorldTransform().setOrigin(btVector3(0, 10.f, 0));
			Entity::physics_model = rb; //Rigid_Body(shape);

			Entity::graphics_model.reset(new Model_Obj("../../assets/Ground1.obj"));
		}


	};
}