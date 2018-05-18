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

		glt::Model graphics_model;
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

			btTransform t;
			t = this->physics_model->get()->getWorldTransform();

			btQuaternion rotation = t.getRotation();
			btVector3 transform = t.getOrigin();

			glm::mat4 RotationMatrix = rotate(mat4(), rotation.getAngle(), vec3(rotation.getAxis().getX(), rotation.getAxis().getY(), rotation.getAxis().getZ()));
			glm::mat4 TranslationMatrix = translate(mat4(), vec3(transform.getX(), transform.getY(), transform.getZ()));

			this->graphics_model.set_transformation(TranslationMatrix);
		}

		shared_ptr < Rigid_Body > getRigidBody()
		{
			return physics_model;
		}

	};
}
