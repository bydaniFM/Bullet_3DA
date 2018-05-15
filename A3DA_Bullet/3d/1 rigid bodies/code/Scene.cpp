

#include <Scene.hpp>

namespace bullet_3da
{

	Scene::Scene()
	{
		// Se crean los elementos (nodos) y la escena a la que se añadirán:

		//shared_ptr< Render_Node > scene(new Render_Node);
		this->graphics_scene = make_shared<Render_Node>();
		shared_ptr< Model       > model(new Model_Obj("../../../../assets/sphere.obj"));
		shared_ptr< Camera      > camera(new Camera(20.f, 1.f, 50.f, 1.f));
		shared_ptr< Light       > light(new Light);

		// Se añaden los nodos a la escena:

		graphics_scene->add("sphere", model);
		graphics_scene->add("camera", camera);
		graphics_scene->add("light", light);

		light->translate(Vector3(10.f, 10.f, 10.f));
		camera->translate(Vector3(0.f, 0.f, 5.f));
	}

	Scene::~Scene()
	{

	}

	/*void Scene::configure_scene()
	{
		graphics_scene.get["light"]->translate(Vector3(10.f, 10.f, 10.f));
		graphics_scene.get["camera"]->translate(Vector3(0.f, 0.f, 5.f));
	}*/
}