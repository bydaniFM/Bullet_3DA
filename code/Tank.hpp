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

		Tank(Scene * scene, glt::Vector3 position);

		shared_ptr < Rigid_Body > getRigidBody() override
		{
			return physics_model;
		}

		void go_forward(float speed)
		{
			wheel_r1_constraint->setMotorTargetVelocity(speed);
			wheel_r2_constraint->setMotorTargetVelocity(speed);
			wheel_l1_constraint->setMotorTargetVelocity(speed);
			wheel_l2_constraint->setMotorTargetVelocity(speed);
		}

		void stop_engine()
		{
			wheel_r1_constraint->setMotorTargetVelocity(0);
			wheel_r2_constraint->setMotorTargetVelocity(0);
			wheel_l1_constraint->setMotorTargetVelocity(0);
			wheel_l2_constraint->setMotorTargetVelocity(0);
		}

		void turn_right()
		{
			wheel_r1_constraint->setMotorTargetVelocity(0.f);
			wheel_r2_constraint->setMotorTargetVelocity(0.f);
			wheel_l1_constraint->setMotorTargetVelocity(+3.f);
			wheel_l2_constraint->setMotorTargetVelocity(+3.f);
		}

		void turn_left()
		{
			wheel_r1_constraint->setMotorTargetVelocity(+3.f);
			wheel_r2_constraint->setMotorTargetVelocity(+3.f);
			wheel_l1_constraint->setMotorTargetVelocity(0.f);
			wheel_l2_constraint->setMotorTargetVelocity(0.f);
		}

		void move_cannon(float speed)
		{
			//Check angle
			float angleX, angleY, angleZ;
			cannon_constraint->getRigidBodyA().getWorldTransform().getRotation().getEulerZYX(angleX, angleY, angleZ);

			float step = glm::radians(speed);

			if(angleZ- step < glm::radians(30.f) && angleZ- step > glm::radians(-30.f))
				cannon_constraint->setMotorTargetVelocity(speed);
			else
				cannon_constraint->setMotorTargetVelocity(0);
		}

		void fire(int count, float force)
		{
			float aX, aY, aZ;
			cannon_constraint->getRigidBodyA().getWorldTransform().getRotation().getEulerZYX(aZ, aY, aX);

			float length = 18.f;
			btVector3 pos = cannon_constraint->getRigidBodyA().getWorldTransform().getOrigin();
			btVector3 dir
			(
				glm::sin(aY) * glm::cos(aZ),
				-glm::sin(aX),
				glm::cos(aY) * glm::cos(aZ)
			);

			for (size_t i = 0; i < bullets.size(); ++i)
			{
				if (!bullets[i]->getActive())
				{
					bullets[i]->launch
					(
						pos + dir * length,
						dir * force
					);
					break;
				}
			}
		}

	};
}