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
#include <MyScene.hpp>
#include <Ground.hpp>
#include <Sphere.hpp>
#include <Tank.hpp>

#include <Input.hpp>

using namespace std;
using namespace glt;

using namespace bullet_3da;

int main ()
{

	View view = View();

	MyScene scene = MyScene();

	float tank_spd = 100.f;
	float tank_rot = glm::radians(10.f);
	
	view.reset_viewport(scene);

    glClearColor (0.2f, 0.2f, 0.2f, 1.f);

    bool running = true;
    int  frame   = 0;

	Input input(view.getWindow());

    do
    {
		/// Read the user input

    //    sf::Event event;

    //    while (view.getWindow()->pollEvent (event))
    //    {
    //        switch (event.type)
    //        {
    //            case sf::Event::Closed:
    //            {
    //                running = false;
    //                break;
    //            }

    //            case sf::Event::Resized:
    //            {
				//	view.reset_viewport(scene);
    //                break;
    //            }

				//case sf::Event::KeyPressed:
				//{
				//	if (event.key.code == sf::Keyboard::W)
				//	{
				//		cout << "Presed W" << endl;
				//		
				//	}
				//	else if (event.key.code == sf::Keyboard::S)
				//	{
				//		cout << "Presed S" << endl;
				//		scene.find("tank")->getRigidBody()->get()->setLinearVelocity(btVector3(-tank_spd, 0, 0));
				//	}
				//	else if (event.key.code == sf::Keyboard::D)
				//	{
				//		cout << "Presed D" << endl;
				//		//tank.getRigidBody()->get()->setAngularVelocity(btVector3(0, tank_rot, 0));
				//	}
				//	else if (event.key.code == sf::Keyboard::A)
				//	{
				//		cout << "Presed A" << endl;
				//		//tank.getRigidBody()->get()->setAngularVelocity(btVector3(0, -tank_rot, 0));
				//	}
				//}

				//case sf::Event::KeyReleased:
				//{
				//	if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
				//	{
				//		scene.find("tank")->getRigidBody()->get()->setLinearVelocity(btVector3(0, 0, 0));
				//	}
				//	else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::A)
				//	{
				//		//tank.getRigidBody()->get()->setAngularVelocity(btVector3(0, 0, 0));
				//	}
				//}
    //        }
    //    }

		Input::InputData input_data = input.check();

		if (input_data->at(Input::close))
		{
			running = false;
		}

		if (input_data->at(Input::resize).as_bool())
		{
			view.reset_viewport(scene);
		}

		scene.processInput(input_data);

        /// Render the scene:

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //sphere_model->rotate_around_y (0.01f);

		scene.update(1.f / 60.f);
        scene.render ();

		//scene.get_physics_world()->getDynamicsWorld()->debugDrawWorld();
        view.getWindow()->display ();
    }
    while (running);

    // Se debe destruir el mundo físico antes de que se destruyan los cuerpos rígidos:

	scene.get_physics_world()->getDynamicsWorld().reset();
    //dynamicsWorld.reset ();

    return EXIT_SUCCESS;
}
