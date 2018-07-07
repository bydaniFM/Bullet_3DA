/*
Author: Daniel Fernández
Date:	27/06/2018
*/

#include <Scene.hpp>

#include <Platform.hpp>
#include <Ground.hpp>
#include <Tank.hpp>

namespace bullet_3da
{
	class MyScene : public Scene
	{
		shared_ptr < Camera > camera;

		unique_ptr < Tank > tank;

		int projectile_count;

		std::clock_t time_fire;

		Tank::Controls controls;

	public:

		MyScene();

		void update(float deltaTime) override;

		void processInput(Input::InputData input_data) override;
	};
}