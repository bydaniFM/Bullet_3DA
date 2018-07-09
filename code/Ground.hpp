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
	/// Represents big platform in which other entities can stand.
	class Ground: public Entity
	{
	public:

		/// Creates a new ground, consisting of a Static_Rigid_Body.
		Ground(): Entity()
		{
			shared_ptr < Shape > shape(new Box_Shape(75.0f, 25.0f, 50.0f));
			shared_ptr<Rigid_Body> rb(new Static_Rigid_Body(shape));
			Entity::physics_model = rb;

			Entity::graphics_model.reset(new Model_Obj("../../assets/Ground1.obj"));
		}


	};
}