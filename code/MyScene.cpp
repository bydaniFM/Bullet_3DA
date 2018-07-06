/*
Author: Daniel Fernández
Date:	27/06/2018
*/

#include <iostream>

#include <MyScene.hpp>

namespace bullet_3da
{
	MyScene::MyScene()
		:
		Scene()
	{
		camera.reset(new Camera(20.f, 1.f, 1000.f, 1.f));
		shared_ptr< Light       > light(new Light);

		light->translate(glt::Vector3(5.f, 5.f, 5.f));
		camera->translate(glt::Vector3(-50.f, 100.f, 00.f));

		camera->rotate_around_y(glm::radians(-80.f));
		camera->rotate_around_x(glm::radians(-20.f));

		graphics_scene->add("camera", camera);
		graphics_scene->add("light", light);


		Ground ground1 = Ground(this);
		//ground1.getRigidBody()->get()->getWorldTransform().setOrigin(btVector3(0, -10, 0));
		ground1.translate(0, 0, 0);
		add("ground1", make_shared<Ground>(ground1));

		Ground ground2 = Ground(this);
		ground2.translate(0, 0, -150);
		add("ground2", make_shared<Ground>(ground2));

		Ground ground3 = Ground(this);
		ground3.translate(0, 0, -300);
		add("ground3", make_shared<Ground>(ground3));

		tank.reset(new Tank(this, glt::Vector3(20, 60, -20)));
		//add("tank", make_shared<Tank>(tank));

		projectile_count = 0;
	}

	void MyScene::update(float deltaTime)
	{
		Scene::update(deltaTime);


	}

	void MyScene::processInput(Input::InputData input_data)
	{
		bool moving = false;

		if (input_data->at(Input::button_forward))
		{
			cout << "Pushing forward" << endl;
			tank->go_forward(5.f);
			moving = true;
		}
		else if (input_data->at(Input::button_back))
		{
			cout << "Pushing backwards" << endl;
			tank->go_forward(-2.f);
			moving = true;
		}

		if (input_data->at(Input::button_right))
		{
			cout << "Turning right" << endl;
			tank->turn_right();
			moving = true;
		}
		else if (input_data->at(Input::button_left))
		{
			cout << "Turning left" << endl;
			tank->turn_left();
			moving = true;
		}
		
		if (!moving)
		{
			tank->stop_engine();
		}


		if (input_data->at(Input::button_up))
		{
			cout << "Raising canonn" << endl;
			tank->move_cannon(1.f);
		}
		else if (input_data->at(Input::button_down))
		{
			cout << "Lowering canonn" << endl;
			tank->move_cannon(-1.f);
		}
		else
		{
			tank->move_cannon(0.f);
		}

		if (input_data->at(Input::button_right2))
		{
			cout << "Rotating cannon right" << endl;
			tank->rotate_turret(1.f);
		}
		else if (input_data->at(Input::button_left2))
		{
			cout << "Rotating cannon left" << endl;
			tank->rotate_turret(-1.f);
		}
		else
		{
			tank->rotate_turret(0.f);
		}


		if (input_data->at(Input::button_fire))
		{
			if (std::clock() - time_fire > 1.f * CLOCKS_PER_SEC)
			{
				cout << "Fire!" << endl;
				tank->fire(projectile_count, 200.f);
				projectile_count++;

				time_fire = std::clock();
			}
		}
		

		// Camera pan

		float angle_delta_x = 0;
		float angle_delta_y = 0;
		glt::Vector3 displacement(0.f, 0.f, 0.f);

		//Input transformation
		if (input_data->at(Input::button_rot)) {
			if (input_data->at(Input::axis_x) || input_data->at(Input::axis_y))
			{
				angle_delta_x = input_data->at(Input::axis_x).as_float() * 0.02f;
				angle_delta_y = input_data->at(Input::axis_y).as_float() * 0.02f;
			}
		}
		else if (input_data->at(Input::button_pan))
		{
			if (input_data->at(Input::axis_x) || input_data->at(Input::axis_y))
			{
				displacement.x = -input_data->at(Input::axis_x).as_float() * 2.0f;
				displacement.y = input_data->at(Input::axis_y).as_float() * 2.0f;
			}
		}

		camera->rotate_around_x(angle_delta_y);
		camera->rotate_around_y(angle_delta_x);
		camera->translate(displacement);
	}
}