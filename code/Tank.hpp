/*

Author: Daniel Fern�ndez
Date:	04/05/2018

*/

#pragma once

#include <vector>
#include <memory>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <Scene.hpp>
#include <Entity.hpp>
#include <Rigid_Body.hpp>
#include <Sphere.hpp>

using namespace std;

namespace bullet_3da
{
	class Tank : public Entity
	{
		Scene * scene;

		btHingeConstraint * turret_constraint;
		btHingeConstraint * cannon_constraint;

		btHingeConstraint * wheel_r1_constraint;
		btHingeConstraint * wheel_r2_constraint;
		btHingeConstraint * wheel_l1_constraint;
		btHingeConstraint * wheel_l2_constraint;

		vector < shared_ptr < Sphere > > bullets;

	public:
		
		struct Controls
		{
			bool forward, back, right, left, up, down, t_right, t_left = false;

			Controls() { forward = back = right = left = up = down = t_right = t_left = false; }
		};

	public:

		Tank(Scene * scene, glt::Vector3 position);

		shared_ptr < Rigid_Body > getRigidBody() override
		{
			return physics_model;
		}

		void go_forward(float speed);

		void stop_engine();

		void turn_right();

		void turn_left();

		void rotate_turret(float speed);

		void move_cannon(float speed);

		void check_cannon_rotation(float speed);

		void fire(int count, float force);

	};
}