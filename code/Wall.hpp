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
	class Wall : public Entity
	{
	public:

		Wall() : Entity()
		{
			shared_ptr < Shape > shape(new Box_Shape(50.0f, 30.0f, 10.0f));
			shared_ptr<Rigid_Body> rb(new Static_Rigid_Body(shape));
			Entity::physics_model = rb;

			Entity::graphics_model.reset(new Model_Obj("../../assets/Wall.obj"));
		}


	};
}