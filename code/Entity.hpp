/*

Author: Daniel Fern�ndez
Date:	04/05/2018

*/

#pragma once

#include <Model.hpp>

//#include <Scene.hpp>
#include <Rigid_Body.hpp>

namespace bullet_3da
{
	class Scene;

	class Entity
	{
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
		~Entity();

		void update()
		{
			//Copiar el transform de física a gráficos
		}

		shared_ptr < Rigid_Body > getRigidBody()
		{
			return physics_model;
		}

	};
}
