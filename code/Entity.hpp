/*

Author: Daniel Fern�ndez
Date:	04/05/2018

*/

#pragma once

#include <Model.hpp>

//#include <Scene.hpp>
#include <Rigid_Body.hpp>

using namespace glm;

namespace bullet_3da
{
	class Scene;

	class Entity
	{
	protected:

		Scene & scene;

	protected:

		shared_ptr<glt::Model> graphics_model;
		shared_ptr < Rigid_Body > physics_model;

	public:

		Entity(Scene * scene)
			:
			scene(*scene)
		{
		}
		~Entity()
		{
		}

		void update()
		{
			//Copiar el transform de física a gráficos

			//btTransform t;
			//t = this->physics_model->get()->getWorldTransform();

			//btQuaternion rotation = t.getRotation();
			//btVector3 transform = t.getOrigin();

			//glm::mat4 RotationMatrix = rotate(mat4(), rotation.getAngle(), vec3(rotation.getAxis().getX(), rotation.getAxis().getY(), rotation.getAxis().getZ()));
			//glm::mat4 TranslationMatrix = translate(mat4(), vec3(transform.getX(), transform.getY(), transform.getZ()));

			//this->graphics_model->set_transformation(TranslationMatrix);

			btTransform physics_transform;
			physics_model->get()->getMotionState()->getWorldTransform(physics_transform);
			glm::mat4 graphics_transform;
			physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));
			graphics_model->set_transformation(graphics_transform);
			//graphics_model->scale(graphics_scale.x, graphics_scale.y, graphics_scale.z);
		}

		shared_ptr < Rigid_Body > getRigidBody()
		{
			return physics_model;
		}

		shared_ptr<glt::Model> getModel()
		{
			return graphics_model;
		}

	};
}
