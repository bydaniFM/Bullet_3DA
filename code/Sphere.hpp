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
		Sphere(Scene * scene) : Entity(scene)
		{
			//Entity::graphics_model

			shared_ptr < Sphere_Shape > shape(new Sphere_Shape(1.0f));
			Entity::physics_model.reset(new Dynamic_Rigid_Body(dynamic_cast<Shape*>(shape.get), 1.0f)); //Rigid_Body(shape);
		}


	};
}