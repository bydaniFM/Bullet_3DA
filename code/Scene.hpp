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

#include <Input.hpp>

using namespace std;
using namespace glt;

namespace bullet_3da
{
	/// Represents a base scene with graphics and physics simulaiton.
	class Scene
	{
		/// Entities, or objects composing the scene.
		map<string, shared_ptr<Entity>> entities;

	protected:

		/// Scene's rendering root.
		shared_ptr<Render_Node> graphics_scene;
		/// Physics world used for the simulaiton.
		shared_ptr<Physics_World> physics_world;

	public:

		///Creates a base scene
		Scene();
		~Scene();

		/// update is called in every frame.
		/// Performs the physics simulation step and updates the state of every entity.
		/// update needs to be called from children objects.
		/// @param deltaTime time since the last frame.
		virtual void update(float deltaTime)
		{
			physics_world->step(deltaTime);
			//Actualizar todas las entidades
			for (auto const & entity : entities)
			{
				entity.second->update();
			}
		}

		/// Renders all entities
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

		/// Adds an entity to the scene, by adding its rigid body to the physics_world and its model to the graphics_scene.
		/// @param name of the entity. Must be unique.
		/// @param entity to add.
		void add(string name, shared_ptr<Entity> entity)
		{
			entities[name] = entity;
			physics_world->add(entity->getRigidBody());
			graphics_scene->add(name, entity->getModel());
		}

		/// Returns an entity from its name.
		shared_ptr<Entity> get_entity(string name)
		{
			return entities[name];
		}

		/// To implement by children objecs. See MyScene.
		virtual void processInput(Input::InputData input_data)
		{
		}

	};
}
