/*
Author: Daniel Fern�ndez
Date:	27/06/2018
*/

#include <Scene.hpp>

#include <Ground.hpp>
#include <Tank.hpp>

namespace bullet_3da
{
	class MyScene : public Scene
	{

	public:

		MyScene();

		void update(float deltaTime) override;
	};
}