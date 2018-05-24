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
			for (auto const & entity : entities)
			{
				entity.second->update();
			}
		}

		void render()
		{
			graphics_scene->render();
		}

		shared_ptr<Render_Node> get_graphics_scene()
		{
			return graphics_scene;
		}
		shared_ptr<Physics_World> get_physics_world()
		{
			return physics_world;
		}

		void add(string name, shared_ptr<Entity> entity)
		{
			entities[name] = entity;
			physics_world->add(entity->getRigidBody());
			graphics_scene->add(name, entity->getModel());
		}

	};
}
