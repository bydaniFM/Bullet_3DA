/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <vector>
#include <memory>

#include <btBulletDynamicsCommon.h>

#include <Scene.hpp>
#include <Entity.hpp>
#include <Rigid_Body.hpp>

using namespace std;

namespace bullet_3da
{
	class Ground: public Entity
	{
	public:

		Ground(Scene * scene): Entity(scene)
		{
			//Entity::physics_model = Static_Rigid_Body();
		}


	};
}