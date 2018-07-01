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

		//shared_ptr< Render_Node > scene(new Render_Node);
		this->graphics_scene = make_shared<Render_Node>();
		//shared_ptr< Model       > model(new Model_Obj("../../../../assets/sphere.obj"));
		shared_ptr< Camera      > camera(new Camera(20.f, 1.f, 5000.f, /*16.f/9.f*/1.f));
		shared_ptr< Light       > light(new Light);

		// Se añaden los nodos a la escena:

		//graphics_scene->add("sphere", model);
		graphics_scene->add("camera", camera);
		graphics_scene->add("light", light);

		light->translate(Vector3(5.f, 5.f, 5.f));
		camera->translate(Vector3(-50.f, 100.f, 00.f));

		camera->rotate_around_y(glm::radians(-80.f));
		camera->rotate_around_x(glm::radians(-20.f));

		//Se crea el mundo de físicas de la escena

		this->physics_world = make_shared<Physics_World>();
	}

	Scene::~Scene()
	{
		physics_world.reset();
	}

	/*void Scene::configure_scene()
	{
		graphics_scene.get["light"]->translate(Vector3(10.f, 10.f, 10.f));
		graphics_scene.get["camera"]->translate(Vector3(0.f, 0.f, 5.f));
	}*/
}