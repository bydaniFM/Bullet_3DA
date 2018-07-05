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
			float dirX, dirY, dirZ;
			cannon_constraint->getRigidBodyA().getWorldTransform().getRotation().getEulerZYX(dirX, dirY, dirZ);
			btVector3 vec_force(dirX, dirY, dirZ);
			vec_force.normalize();
			vec_force.absolute();
			vec_force *= force;

			btVector3 pos = cannon_constraint->getRigidBodyA().getWorldTransform().getOrigin();
			btVector3 offset
			(
				18.f * glm::cos(dirY) * glm::sin(dirZ),
				18.f * glm::cos(dirY),
				-18.f * glm::sin(dirY) * glm::sin(dirZ)
			);
			//pos += offset;

			shared_ptr <Sphere> projectile (new  Sphere
			(
				scene,
				pos,
				cannon_constraint->getRigidBodyA().getWorldTransform().getRotation(),
				vec_force
			));
			
			std::string name = "projectile" + count;
			scene->add(name, projectile);
		}

		void fire(int count, float force)
		{
			float dirX, dirY, dirZ;
			cannon_constraint->getRigidBodyA().getWorldTransform().getRotation().getEulerZYX(dirX, dirY, dirZ);
			btVector3 vec_force(dirX, dirY, dirZ);
			vec_force.normalize();
			vec_force.absolute();
			vec_force *= force;

			btVector3 pos = cannon_constraint->getRigidBodyA().getWorldTransform().getOrigin();
			btVector3 offset
			(
				18.f * glm::cos(dirY) * glm::sin(dirZ),
				18.f * glm::cos(dirY),
				-18.f * glm::sin(dirY) * glm::sin(dirZ)
			);
			//pos += offset;

			shared_ptr <Sphere> projectile (new  Sphere
			(
				scene,
				pos,
				cannon_constraint->getRigidBodyA().getWorldTransform().getRotation(),
				vec_force
			));
			
			std::string name = "projectile" + count;
			scene->add(name, projectile);
		}

	};
}