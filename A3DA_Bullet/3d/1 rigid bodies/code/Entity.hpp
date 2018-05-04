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

		glt::Model graphics_model;
		Rigid_Body physics_model;

	public:
		Entity(Scene * scene);
		~Entity();

		void update()
		{
			//Copiar el transform de física a gráficos
		}

	};
}
