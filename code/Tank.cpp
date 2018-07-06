/*
Author: Daniel Fern�ndez
Date:	27/06/2018
*/

#include <Tank.hpp>

namespace bullet_3da
{
	Tank::Tank(Scene * scene, glt::Vector3 position)
		:
		Entity(),
		scene(scene)
	{
		// Bullets

		for (int i = 0; i < 10; i++)
		{
			bullets.push_back(make_shared<Sphere>());
			std::string name = "projectile" + std::to_string(i);
			scene->add(name, bullets[i]);
		}

		// Body
		shared_ptr < Shape > body_shape(new Box_Shape(15.0f, 4.0f, 7.5f));
		shared_ptr<Rigid_Body> body_rb(new Dynamic_Rigid_Body(body_shape, 10.f));
		body_rb->get()->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
		body_rb->get()->setRestitution(0.f);
		body_rb->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);
		shared_ptr<Entity> body(new Entity(/*scene, */"../../assets/Body.obj", body_rb));
		
		// Turret
		shared_ptr < Shape > turret_shape(new Box_Shape(7.5f, 2.25f, 5.0f));
		shared_ptr<Rigid_Body> turret_rb(new Dynamic_Rigid_Body(turret_shape, 10.f));
		turret_rb->get()->getWorldTransform().setOrigin(btVector3(position.x, position.y + 6.5f, position.z));
		turret_rb->get()->setRestitution(0.f);
		turret_rb->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);
		shared_ptr<Entity> turret(new Entity(/*scene, */"../../assets/Turret.obj", turret_rb));

		//Cannon
		shared_ptr < Shape > cannon_shape(new Box_Shape(8.35f, 0.8f, 1.5f));
		shared_ptr<Rigid_Body> cannon_rb(new Dynamic_Rigid_Body(cannon_shape, 3.f));
		cannon_rb->get()->getWorldTransform().setOrigin(btVector3(position.x, position.y + 6.7f, position.z + 7.14f));
		cannon_rb->get()->setRestitution(0.f);
		cannon_rb->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);
		shared_ptr<Entity> cannon(new Entity(/*scene, */"../../assets/Cannon.obj", cannon_rb));


		// Wheels

		shared_ptr < Shape > wheel_shape(new Cylinder_Shape(3.75f, 1.3f, 3.75f));
		btQuaternion wheel_rotation = btQuaternion(0.707f, 0.707f, 0.f, 0.f);
		float wheel_friction = 1000000.f;

		// wheel r1
		shared_ptr<Rigid_Body> wheel_rb_r1(new Dynamic_Rigid_Body(wheel_shape, 10.f));
		wheel_rb_r1->get()->getWorldTransform().setOrigin(btVector3(position.x - 7.f, position.y - 3.f, position.z + 9));
		wheel_rb_r1->get()->getWorldTransform().setRotation(wheel_rotation);
		wheel_rb_r1->get()->setRestitution(0.f);
		//wheel_rb_r1->get()->setFriction(wheel_friction);
		wheel_rb_r1->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);
		shared_ptr<Entity> wheel_r1(new Entity(/*scene, */"../../assets/Wheel.obj", wheel_rb_r1));

		// wheel r2
		shared_ptr<Rigid_Body> wheel_rb_r2(new Dynamic_Rigid_Body(wheel_shape, 10.f));
		wheel_rb_r2->get()->getWorldTransform().setOrigin(btVector3(position.x - 7.f, position.y - 3.f, position.z - 9.5f));
		wheel_rb_r2->get()->getWorldTransform().setRotation(wheel_rotation);
		wheel_rb_r2->get()->setRestitution(0.f);
		//wheel_rb_r1->get()->setFriction(wheel_friction);
		wheel_rb_r2->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);
		shared_ptr<Entity> wheel_r2(new Entity(/*scene, */"../../assets/Wheel.obj", wheel_rb_r2));

		// wheel l1
		shared_ptr<Rigid_Body> wheel_rb_l1(new Dynamic_Rigid_Body(wheel_shape, 10.f));
		wheel_rb_l1->get()->getWorldTransform().setOrigin(btVector3(position.x + 7.f, position.y - 3.f, position.z + 9));
		wheel_rb_l1->get()->getWorldTransform().setRotation(wheel_rotation);
		wheel_rb_l1->get()->setRestitution(0.f);
		//wheel_rb_r1->get()->setFriction(wheel_friction);
		wheel_rb_l1->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);
		shared_ptr<Entity> wheel_l1(new Entity(/*scene, */"../../assets/Wheel.obj", wheel_rb_l1));

		// wheel l2
		shared_ptr<Rigid_Body> wheel_rb_l2(new Dynamic_Rigid_Body(wheel_shape, 10.f));
		wheel_rb_l2->get()->getWorldTransform().setOrigin(btVector3(position.x + 7.f, position.y - 3.f, position.z - 9.5f));
		wheel_rb_l2->get()->getWorldTransform().setRotation(wheel_rotation);
		wheel_rb_l2->get()->setRestitution(0.f);
		//wheel_rb_r1->get()->setFriction(wheel_friction);
		wheel_rb_l2->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);
		shared_ptr<Entity> wheel_l2(new Entity(/*scene, */"../../assets/Wheel.obj", wheel_rb_l2));

		

		scene->add("body", body);
		scene->add("turret", turret);
		scene->add("cannon", cannon);
		scene->add("wheel_r1", wheel_r1);
		scene->add("wheel_r2", wheel_r2);
		scene->add("wheel_l1", wheel_l1);
		scene->add("wheel_l2", wheel_l2);

		//add_constraints(scene, turret_constraint, *turret_rb->get(), *body_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(0.f, 0.0f, 0.f), btVector3(0.f, -1.f, 0.f), btVector3(0.f, 0.f, 0.f), true);

		turret_constraint = new btHingeConstraint(*turret_rb->get(), *body_rb->get(), btVector3(0.f, -2.25f, 0.f), btVector3(0.f, 4.f, 0.f), btVector3(0.f, -1.f, 0.f), btVector3(0.f, 0.f, 0.f));//-6.5
		turret_constraint->enableAngularMotor(true, 0.f, 10.f);
		scene->get_physics_world()->addConstraints(turret_constraint);

		cannon_constraint = new btHingeConstraint(*cannon_rb->get(), *turret_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(0.f, 0.f, 7.14f), btVector3(-1.f, 0.f, 0.f), btVector3(0.f, 0.f, 0.f));//-6.5
		/*double min = -0.174533, max = 0.872665;
		cannon_constraint->setLimit(min, max);*/
		cannon_constraint->enableAngularMotor(true, 0.f, 10.f);
		scene->get_physics_world()->addConstraints(cannon_constraint);


		wheel_r1_constraint = new btHingeConstraint(*wheel_rb_r1->get(), *body_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(-7.f, -3.f, 9.f), btVector3(0.f, 1.f, 0.f), btVector3(0.f, 0.f, 0.f));
		wheel_r1_constraint->enableAngularMotor(true, 0.f, 10.f);
		scene->get_physics_world()->addConstraints(wheel_r1_constraint);

		wheel_r2_constraint = new btHingeConstraint(*wheel_rb_r2->get(), *body_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(-7.f, -3.f, -9.5f), btVector3(0.f, 1.f, 0.f), btVector3(0.f, 0.f, 0.f));
		wheel_r2_constraint->enableAngularMotor(true, 0.f, 10.f);
		scene->get_physics_world()->addConstraints(wheel_r2_constraint);

		wheel_l1_constraint = new btHingeConstraint(*wheel_rb_l1->get(), *body_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(7.f, -3.f, 9.f), btVector3(0.f, 1.f, 0.f), btVector3(0.f, 0.f, 0.f));
		wheel_l1_constraint->enableAngularMotor(true, 0.f, 10.f);
		scene->get_physics_world()->addConstraints(wheel_l1_constraint);

		wheel_l2_constraint = new btHingeConstraint(*wheel_rb_l2->get(), *body_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(7.f, -3.f, -9.5f), btVector3(0.f, 1.f, 0.f), btVector3(0.f, 0.f, 0.f));
		wheel_l2_constraint->enableAngularMotor(true, 0.f, 10.f);
		scene->get_physics_world()->addConstraints(wheel_l2_constraint);


		/*cannon_rb->get()->setIgnoreCollisionCheck(turret_rb->get(), true);
		cannon_rb->get()->setIgnoreCollisionCheck(body_rb->get(), true);*/

		wheel_rb_r1->get()->setIgnoreCollisionCheck(body_rb->get(), true);
		wheel_rb_r2->get()->setIgnoreCollisionCheck(body_rb->get(), true);
		wheel_rb_l1->get()->setIgnoreCollisionCheck(body_rb->get(), true);
		wheel_rb_l2->get()->setIgnoreCollisionCheck(body_rb->get(), true);

		wheel_rb_r1->get()->setIgnoreCollisionCheck(turret_rb->get(), true);
		wheel_rb_r2->get()->setIgnoreCollisionCheck(turret_rb->get(), true);
		wheel_rb_l1->get()->setIgnoreCollisionCheck(turret_rb->get(), true);
		wheel_rb_l2->get()->setIgnoreCollisionCheck(turret_rb->get(), true);
		
	}

	void Tank::go_forward(float speed)
	{
		wheel_r1_constraint->setMotorTargetVelocity(speed);
		wheel_r2_constraint->setMotorTargetVelocity(speed);
		wheel_l1_constraint->setMotorTargetVelocity(speed);
		wheel_l2_constraint->setMotorTargetVelocity(speed);
	}

	void Tank::stop_engine()
	{
		wheel_r1_constraint->setMotorTargetVelocity(0);
		wheel_r2_constraint->setMotorTargetVelocity(0);
		wheel_l1_constraint->setMotorTargetVelocity(0);
		wheel_l2_constraint->setMotorTargetVelocity(0);
	}

	void Tank::turn_right()
	{
		wheel_r1_constraint->setMotorTargetVelocity(0.f);
		wheel_r2_constraint->setMotorTargetVelocity(0.f);
		wheel_l1_constraint->setMotorTargetVelocity(+3.f);
		wheel_l2_constraint->setMotorTargetVelocity(+3.f);
	}

	void Tank::turn_left()
	{
		wheel_r1_constraint->setMotorTargetVelocity(+3.f);
		wheel_r2_constraint->setMotorTargetVelocity(+3.f);
		wheel_l1_constraint->setMotorTargetVelocity(0.f);
		wheel_l2_constraint->setMotorTargetVelocity(0.f);
	}

	void Tank::rotate_turret(float speed)
	{
		turret_constraint->setMotorTargetVelocity(speed);
	}

	void Tank::move_cannon(float speed)
	{
		//Check angle
		float angleX, angleY, angleZ;
		cannon_constraint->getRigidBodyA().getWorldTransform().getRotation().getEulerZYX(angleX, angleY, angleZ);

		float step = glm::radians(speed);

		if (angleZ - step < glm::radians(30.f) && angleZ - step > glm::radians(-30.f))
			cannon_constraint->setMotorTargetVelocity(speed);
		else
			cannon_constraint->setMotorTargetVelocity(0);
	}

	void Tank::fire(int count, float force)
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

}