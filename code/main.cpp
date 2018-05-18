/*
    Bullet Continuous Collision Detection and Physics Library
    Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it freely,
    subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
       If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    This is the official 'Hello, World' example cleaned up for additional simplicity and clarity.
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

using namespace std;
using namespace glt;

//namespace bullet_3da
//{
//
//    shared_ptr< Render_Node > create_scene ()
//    {
//        // Se crean los elementos (nodos) y la escena a la que se añadirán:
//
//        shared_ptr< Render_Node > scene (new Render_Node);
//        shared_ptr< Model       > model (new Model_Obj("../../../../assets/sphere.obj"));
//        shared_ptr< Camera      > camera(new Camera(20.f, 1.f, 50.f, 1.f));
//        shared_ptr< Light       > light (new Light);
//
//        // Se añaden los nodos a la escena:
//
//        scene->add ("sphere", model );
//        scene->add ("camera", camera);
//        scene->add ("light" , light );
//
//        return scene;
//    }
//
//    void configure_scene (Render_Node & scene)
//    {
//        scene["light" ]->translate (Vector3(10.f, 10.f, 10.f));
//        scene["camera"]->translate (Vector3( 0.f,  0.f,  5.f));
//    }
//
//    void reset_viewport (const sf::Window & window, Render_Node & scene)
//    {
//        GLsizei width  = GLsizei(window.getSize ().x);
//        GLsizei height = GLsizei(window.getSize ().y);
//
//        scene.get_active_camera ()->set_aspect_ratio (float(width) / height);
//
//        glViewport (0, 0, width, height);
//    }
//
//}

using namespace bullet_3da;

int main ()
{

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                                SIMULATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

	View view = View();

	Scene scene = Scene();


    //configure_scene (*scene);

    //Node * sphere_model = scene->get ("sphere");

    // Se inicializan algunos elementos de OpenGL:

	view.reset_viewport(scene);

    glClearColor (0.2f, 0.2f, 0.2f, 1.f);

    bool running = true;
    int  frame   = 0;

    do
    {
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
