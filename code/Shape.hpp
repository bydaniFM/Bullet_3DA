/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <memory>

#include <Model.hpp>

#include <btBulletDynamicsCommon.h>

namespace bullet_3da
{
	class Shape
	{
		std::shared_ptr<btCollisionShape> shape;

	public:

		virtual ~Shape() = default;

	public:

		Shape(std::shared_ptr<btCollisionShape> & shape) :shape(shape)
		{
		}

		//Dos opciones para el get
		//Más polivalente:
		btCollisionShape * get()
		{
			return shape.get();
		}
		//Solo si sabemos que nunca va a ser null
		/*btCollisionShape & get()
		{
			return *shape;
		}*/
	};

	class Sphere_Shape : public Shape
	{
	public:
		Sphere_Shape(float radius)
			:
			Shape(std::shared_ptr< btCollisionShape >(new btSphereShape(btScalar(radius))))
		{
		}

	};

	class Box_Shape : public Shape
	{
	public:

		Box_Shape(float width, float height, float depth)
			:
			Shape(std::shared_ptr< btCollisionShape >(new btBoxShape(btVector3(width, height, depth))))
		{
		}

	};
}
