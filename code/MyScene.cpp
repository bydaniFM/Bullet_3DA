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
		//light->set_intensity(0.5f);

		camera->translate(glt::Vector3(-100.f, 70.f, 00.f));
		camera->rotate_around_y(glm::radians(-80.f));
		camera->rotate_around_x(glm::radians(-10.f));

		graphics_scene->add("camera", camera);
		graphics_scene->add("light", light);


		Ground ground1 = Ground();
		ground1.translate(0, 0, 0);
		add("ground1", make_shared<Ground>(ground1));

		Ground ground2 = Ground();
		ground2.translate(0, 0, -150);
		add("ground2", make_shared<Ground>(ground2));

		Ground ground3 = Ground();
		ground3.translate(0, 0, -300);
		add("ground3", make_shared<Ground>(ground3));

		Platform moving_platform = Platform();
		moving_platform.translate(0, 20, -75);
		add("moving_platform", make_shared<Platform>(moving_platform));

		Wall wall;
		wall.translate(25, 55, -150);
		add("wall", make_shared<Wall>(wall));

		Door door;
		door.translate(-50, 55, -150);
		add("door", make_shared<Door>(door));

		tank.reset(new Tank(this, glt::Vector3(20, 35, -20)));
		//add("tank", make_shared<Tank>(tank));

		projectile_count = 0;
	}

	void MyScene::update(float deltaTime)
	{
		Scene::update(deltaTime);
	}

	void MyScene::processInput(Input::InputData input_data)
	{

		// "controls" is used to ensure we are not performing the same action consecutively,
		// in case the user keeps the button pressed

		//-----------Tank-Movement-------------//

		if (input_data->at(Input::button_forward))
		{
			controls.forward = !controls.forward;
			if (controls.forward)
			{
				cout << "Pushing forward" << endl;
				tank->go_forward(5.f);
			}
		}
		else if (input_data->at(Input::button_back))
		{
			controls.back = !controls.back;
			if (controls.back)
			{
				cout << "Pushing backwards" << endl;
				tank->go_forward(-2.f);
			}
		}

		if (input_data->at(Input::button_right))
		{
			controls.right = !controls.right;
			if (controls.right)
			{
				cout << "Turning right" << endl;
				tank->turn_right();
			}
		}
		else if (input_data->at(Input::button_left))
		{
			controls.left = !controls.left;
			if (controls.left)
			{
				cout << "Turning left" << endl;
				tank->turn_left();
			}
		}
		
		if(!controls.forward && !controls.back && !controls.right && !controls.left)
		{
			tank->stop_engine();
		}


		//-----------Cannon-Movement-------------//

		if (input_data->at(Input::button_up))
		{
			controls.up = !controls.up;
			if (controls.up)
			{
				cout << "Raising canonn" << endl;
				tank->move_cannon(1.f);
			}
		}
		else if (input_data->at(Input::button_down))
		{
			controls.down = !controls.down;
			if (controls.down)
			{
				cout << "Lowering canonn" << endl;
				tank->move_cannon(-1.f);
			}
		}

		if(controls.up)
			tank->check_cannon_rotation(1.f);
		else if (controls.down)
			tank->check_cannon_rotation(-1.f);
		else
			tank->move_cannon(0.f);
		

		//-----------Turret-Movement-------------//

		if (input_data->at(Input::button_right2))
		{
			controls.t_right = !controls.t_right;
			if (controls.t_right)
			{
				cout << "Rotating cannon right" << endl;
				tank->rotate_turret(1.f);
			}
		}
		else if (input_data->at(Input::button_left2))
		{
			controls.t_left = !controls.t_left;
			if (controls.t_left)
			{
				cout << "Rotating cannon left" << endl;
				tank->rotate_turret(-1.f);
			}
		}
		
		if(!controls.t_right && !controls.t_left)
		{
			tank->rotate_turret(0.f);
		}


		//-----------Tank-Shooting-------------//

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
		

		//-----------Camera-Movement-------------//

		float angle_delta_x = 0;
		float angle_delta_y = 0;
		glt::Vector3 displacement(0.f, 0.f, 0.f);

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