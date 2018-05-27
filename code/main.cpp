/*
    Author: Daniel Fernández
	Date:	18/05/2018
*/

#include <memory>
#include <vector>
#include <iostream>

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>

#include <View.hpp>
#include <Scene.hpp>
#include <Ground.hpp>
#include <Sphere.hpp>
#include <Tank.hpp>

using namespace std;
using namespace glt;

using namespace bullet_3da;

int main ()
{

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                                SIMULATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

	View view = View();

	Scene scene = Scene();

	Sphere sphere = Sphere(&scene);
	sphere.getRigidBody()->get()->getWorldTransform().setOrigin(btVector3(-50, 10, 0));
	//sphere.translate(-50, 10, 0);
	scene.add("sphere", make_shared<Sphere>(sphere));

	Ground ground1 = Ground(&scene);
	//ground1.getRigidBody()->get()->getWorldTransform().setOrigin(btVector3(0, -10, 0));
	ground1.translate(0, 0, 0);
	scene.add("ground1", make_shared<Ground>(ground1));

	Ground ground2 = Ground(&scene);
	ground2.translate(0, 0, -150);
	scene.add("ground2", make_shared<Ground>(ground2));

	Ground ground3 = Ground(&scene);
	ground3.translate(0, 0, -300);
	scene.add("ground3", make_shared<Ground>(ground3));

	Tank tank = Tank(&scene);
	//tank.translate(20, -100, -20);
	tank.getRigidBody()->get()->getWorldTransform().setOrigin(btVector3(20, 100, -20));
	scene.add("tank", make_shared<Tank>(tank));

    //configure_scene (*scene);

    //Node * sphere_model = scene->get ("sphere");

    // Se inicializan algunos elementos de OpenGL:

	view.reset_viewport(scene);

    glClearColor (0.2f, 0.2f, 0.2f, 1.f);

    bool running = true;
    int  frame   = 0;

    do
    {
		//cout << "x: " << sphere.getRigidBody()->get()->getWorldTransform().getOrigin().getX() << "  y: " << sphere.getRigidBody()->get()->getWorldTransform().getOrigin().getY() << endl;

        // Read the user input:

        sf::Event event;

        while (view.getWindow()->pollEvent (event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    running = false;
                    break;
                }

                case sf::Event::Resized:
                {
					view.reset_viewport(scene);
                    break;
                }
            }
        }

        //// Perform the simulation:

        //dynamicsWorld->stepSimulation (1.f / 60.f);

        //// Apply the physics transform to the graphics model:

        //btTransform physics_transform;

        //sphere_body->getMotionState ()->getWorldTransform (physics_transform);

        //glm::mat4 graphics_transform;

        //physics_transform.getOpenGLMatrix (glm::value_ptr(graphics_transform));

        ////sphere_model->set_transformation (graphics_transform);

        ////sphere_model->scale (0.5f);

        //// Render the scene:

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //sphere_model->rotate_around_y (0.01f);

		scene.update(1.f / 60.f);
        scene.render ();

        view.getWindow()->display ();
    }
    while (running);

    // Se debe destruir el mundo físico antes de que se destruyan los cuerpos rígidos:

	scene.get_physics_world()->getDynamicsWorld().reset();
    //dynamicsWorld.reset ();

    return EXIT_SUCCESS;
}
