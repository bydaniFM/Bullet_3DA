

#include <iostream>
/*
Author: Daniel Fernández
Date:	27/06/2018
*/

#include <MyScene.hpp>

namespace bullet_3da
{
	MyScene::MyScene()
		:
		Scene()
	{
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
	}

	void MyScene::update(float deltaTime)
	{
		Scene::update(deltaTime);


	}

	void MyScene::processInput(Input::InputData input_data)
	{
		if (input_data->at(Input::button_forward))
		{
			cout << "Pushing forward" << endl;
			tank->go_forward(2);
		}
		else if (input_data->at(Input::button_back))
		{
			cout << "Pushing backwards" << endl;
			tank->go_forward(-1);
		}
		else
		{
			tank->stop_engine();
		}

		if (input_data->at(Input::button_right) && input_data->at(Input::button_left))
		{
		}
		else
		{
			if (input_data->at(Input::button_right))
			{
				cout << "Turning right" << endl;
				//tank->turn(-30.f);
				tank->turn_right();
			}
			else if (input_data->at(Input::button_left))
			{
				cout << "Turning right" << endl;
				//tank->turn(30.f);
				tank->turn_left();
			}
			else
			{
				//tank->turn(0.f);
				tank->reset_turn();
			}
		}

		//cout << "Mouse pos: " << input_data->at(Input::axis_x) << " " << input_data->at(Input::axis_y) << endl;
		//cout << input_data->at(Input::button_pan) << endl;

		//float angle_delta_x = 0;
		//float angle_delta_y = 0;

		////Input transformation
		//if (input_data->at(Input::button_pan)) {
		//	if (input_data->at(Input::axis_x) || input_data->at(Input::axis_y))
		//	{
		//		//camera.rotate(glm::rotate(camera.get_model_view(), 1.f, glm::vec3(input_data->at(Input::axis_y), input_data->at(Input::axis_x), 0.f)));
		//		/*camera.rotate
		//		(
		//		glm::lookAt
		//		(
		//		glm::vec3(camera.get_location().x, camera.get_location().y, camera.get_location().z),
		//		glm::vec3(camera.get_target().x, camera.get_target().y, camera.get_target().z),
		//		glm::vec3(0, 1, 0)
		//		) + 0.001f
		//		);*/
		//		angle_delta_x = input_data->at(Input::axis_x).as_float() * 0.02f;
		//		angle_delta_y = input_data->at(Input::axis_y).as_float() * 0.02f;
		//	}
		//}

		//angle_around_x += angle_delta_x;
		//angle_around_y -= angle_delta_y;

		////Apply camera rotation
		//glm::mat4 camera_rotation;

		//camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_x), glm::vec3(0.f, 1.f, 0.f));
		//camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_y), glm::vec3(1.f, 0.f, 0.f));

		//camera.set_target(0, 0, -1);
		//camera.rotate(camera_rotation);

		////Camera movement

		//float movement = input_data->at(Input::button_forward).as_float() + input_data->at(Input::button_back).as_float();

		///*camera.move(glm::vec3
		//(
		//camera.get_target().x,
		//camera.get_target().y,
		//camera.get_target().z
		//) + glm::vec3(1,1,1) * movement);*/

		//camera.move(glm::vec3(0.f, 0.f, input_data->at(Input::button_forward).as_float()));
		//camera.move(glm::vec3(0.f, 0.f, -input_data->at(Input::button_back).as_float()));
	}
}