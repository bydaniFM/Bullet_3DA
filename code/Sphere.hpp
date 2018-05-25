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
			shared_ptr < Shape > shape(new Sphere_Shape(1.0f));
			shared_ptr<Rigid_Body> rb(new Dynamic_Rigid_Body(shape, 10.f));
			//rb->get()->getWorldTransform().setOrigin(btVector3(0, 10.f, 0));
			Entity::physics_model = rb; //Rigid_Body(shape);

			Entity::graphics_model.reset(new Model_Obj("../../assets/Ball.obj"));
		}


	};
}