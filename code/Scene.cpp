/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#include <Scene.hpp>

namespace bullet_3da
{

	Scene::Scene()
	{
		// Se crean los elementos (nodos) y la escena a la que se añadirán:

		this->graphics_scene = make_shared<Render_Node>();
		

		//Se crea el mundo de físicas de la escena

		this->physics_world = make_shared<Physics_World>();
	}

	Scene::~Scene()
	{
		physics_world.reset();
	}
}