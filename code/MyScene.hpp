/*
Author: Daniel Fernández
Date:	27/06/2018
*/

#include <Scene.hpp>

#include <Ground.hpp>
#include <Tank.hpp>

namespace bullet_3da
{
	class MyScene : public Scene
	{

		unique_ptr < Tank > tank;

	public:

		MyScene();

		void update(float deltaTime) override;

		void processInput(Input::InputData input_data) override;
	};
}