/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <Rigid_Body.hpp>
#include <Model_Obj.hpp>

using namespace glm;

namespace bullet_3da
{
	/// Scene pre-declaration
	class Scene;

	/// Represents a game object inside the scene.
	class Entity
	{

	protected:

		/// Visual component of the Entity.
		shared_ptr<glt::Model> graphics_model;

		/// Physics component of the Entity.
		shared_ptr < Rigid_Body > physics_model;

	public:

		Entity()
		{
		}

		/// Creates a new base Entity given a route of the model and a Rigid_Body.
		/// @param model_path route to the 3D model in OBJ.
		/// @param physics_model rigid body to be used for the physics symulation of this entity.
		Entity(const string & model_path, shared_ptr< Rigid_Body > & physics_model)
			:
			physics_model(physics_model)
		{
			graphics_model.reset(new glt::Model_Obj(model_path));
		}

		~Entity()
		{
		}

		/// Gets the transformation of the physics_model and applies it to the graphics_model.
		virtual void update()
		{
			btTransform physics_transform;
			physics_model->get()->getMotionState()->getWorldTransform(physics_transform);
			glm::mat4 graphics_transform;
			physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));
			graphics_model->set_transformation(graphics_transform);
			//graphics_model->scale(graphics_scale.x, graphics_scale.y, graphics_scale.z);
		}

		/// Translates the Entity to a new opsition given its 3D coordinates.
		void translate(float x, float y, float z)
		{
			btTransform transform;
			physics_model->get()->getMotionState()->getWorldTransform(transform);
			transform.setOrigin(btVector3(x, y, z));
			physics_model->get()->getMotionState()->setWorldTransform(transform);
			physics_model->get()->getWorldTransform().setOrigin(btVector3(x, y, z));
		}

		virtual shared_ptr < Rigid_Body > getRigidBody()
		{
			return physics_model;
		}

		virtual shared_ptr<glt::Model> getModel()
		{
			return graphics_model;
		}
	};
}
