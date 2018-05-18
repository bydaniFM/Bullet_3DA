/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <memory>

//#include <btBulletDynamicsCommon.h>

#include <Entity.hpp>

namespace bullet_3da
{
	class Sphere : public Entity
	{
	public:

		Sphere(Scene * scene) : Entity(scene)
		{
			//Entity::graphics_model

			shared_ptr < Shape > shape(new Sphere_Shape(1.0f));
			shared_ptr<Rigid_Body> rb(new Dynamic_Rigid_Body(shape, 10.f));
			Entity::physics_model = rb; //Rigid_Body(shape);

		}


	};
}