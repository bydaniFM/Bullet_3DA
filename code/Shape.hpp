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
	/// Encapsulates a btCollisionShape, acting as a collider for the entities of the game.
	/// Shape can't be initialized, as it's an abstract class.
	class Shape
	{
		/// Bullet's shape.
		std::shared_ptr<btCollisionShape> shape;

	public:

		virtual ~Shape() = default;

	public:

		/// Default constructor.
		Shape(std::shared_ptr<btCollisionShape> & shape) :shape(shape)
		{
		}

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

	/// Shape specialization for the representation of a sphere collider.
	class Sphere_Shape : public Shape
	{
	public:
		/// Creates a btSphereShape.
		/// @param Radius of the sphere.
		Sphere_Shape(float radius)
			:
			Shape(std::shared_ptr< btCollisionShape >(new btSphereShape(btScalar(radius))))
		{
		}

	};

	/// Shape specialization for the representation of a box collider.
	class Box_Shape : public Shape
	{
	public:
		/// Creates a btBoxShape.
		/// @param Box's distance from center to X side. Must be the half of the actual width.
		/// @param Box's distance from center to Y side. Must be the half of the actual height.
		/// @param Box's distance from center to Z side. Must be the half of the actual depth.
		Box_Shape(float width, float height, float depth)
			:
			Shape(std::shared_ptr< btCollisionShape >(new btBoxShape(btVector3(width, height, depth))))
		{
		}

	};

	/// Shape specialization for the representation of a cylinder collider.
	class Cylinder_Shape : public Shape
	{
	public:
		/// Creates a btCylinderShape. The cylinder is created standing on one of its bases.
		/// @param Cylinders's first radius.
		/// @param distance from center to Y side. Must be the half of the actual height.
		/// @param Cylinders's first radius.
		Cylinder_Shape(float width, float height, float depth)
			:
			Shape(std::shared_ptr< btCollisionShape >(new btCylinderShape(btVector3(width, height, depth))))
		{
		}
	};
}
