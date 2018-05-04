/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <memory>

#include <btBulletDynamicsCommon.h>

using namespace std;

namespace bullet_3da
{
	class Physics_World
	{
		shared_ptr< btDiscreteDynamicsWorld > world;

	public:
		Physics_World();
		~Physics_World() {}

		void step(...)
		{
			world->stepSimulation(1.f / 60.f);
		}

	};
}
