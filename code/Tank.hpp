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
	/// Represents a tank made from different rigid bodies.
	class Tank : public Entity
	{
		/// Scene in which the tank is in.
		Scene * scene;

		/// Constraint or joint between the turret and the main body of the tank.
		btHingeConstraint * turret_constraint;
		/// Constraint or joint between the cannon and the tank's turret.
		btHingeConstraint * cannon_constraint;

		/// Constraints between each of the wheels and the tank's main body
		btHingeConstraint * wheel_r1_constraint;
		btHingeConstraint * wheel_r2_constraint;
		btHingeConstraint * wheel_l1_constraint;
		btHingeConstraint * wheel_l2_constraint;

		/// Object pool for the tanks bullets (Sphere), so we don't need to initialize them in-game.
		vector < shared_ptr < Sphere > > bullets;

	public:
		/// Structure used to store the tank inputs.
		struct Controls
		{
			bool forward, back, right, left, up, down, t_right, t_left = false;

			Controls() { forward = back = right = left = up = down = t_right = t_left = false; }
		};

	public:

		/// Creates a new Tank.
		/// @param The Scene the tank will be in.
		/// @param Initial position of the tank.
		Tank(Scene * scene, glt::Vector3 position);

		shared_ptr < Rigid_Body > getRigidBody() override
		{
			return physics_model;
		}

		/// Starts the forward movement of the tank.
		void go_forward(float speed);

		/// Stops the tank movement.
		void stop_engine();

		/// Starts the tank movement to the right.
		void turn_right();

		/// Starts the tank movement to the left.
		void turn_left();

		/// Rotates the turret using its constraint motor.
		/// @param Speed of the rotation. Use negative for a left-hand rotation.
		void rotate_turret(float speed);

		/// Rises ro lowers the cannon.
		/// @param Positive to rise, negative to lower the cannon.
		void move_cannon(float speed);

		/// Checks if the cannon is still between it's constraints and stops its movement if not.
		void check_cannon_rotation(float speed);

		/// Activates an launches an available Sphere from the pool.
		/// The cannon position and orientation is calculated and used to launch the selected Sphere.
		/// @param Force to be applied to the Sphere's force vector.
		void fire(float force);

	};
}