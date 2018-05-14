/*

	Author: Daniel Fernández
	Date:	04/05/2018

*/

#pragma once

#include <map>
#include <string>
#include <memory>

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <Entity.hpp>
#include <Physics_World.hpp>

using namespace std;
using namespace glt;

namespace bullet_3da
{
	class Scene
	{
		map<string, shared_ptr<Entity>> entities;

		shared_ptr<Render_Node> graphics_scene;	//glt::Scene graphics_scene;
		shared_ptr<Physics_World> physics_world;

	public:
		Scene();
		~Scene();

		//void configure_scene();

		void update(float deltaTime)
		{
			physics_world->step(deltaTime);
			//Actualizar todas las entidades
		}

		void render()
		{
			//llama al render de graphics scene
		}

		//Hacer getter

	};
}
