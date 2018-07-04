/*
Author: Daniel Fernández
Date:	27/06/2018
*/

#include <Tank.hpp>

namespace bullet_3da
{
	Tank::Tank(Scene * scene, glt::Vector3 position)
		:
		Entity(/*scene*/)
	{
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
		scene->add("wheel_r1", wheel_r1);
		scene->add("wheel_r2", wheel_r2);
		scene->add("wheel_l1", wheel_l1);
		scene->add("wheel_l2", wheel_l2);

		//add_constraints(scene, turret_constraint, *turret_rb->get(), *body_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(0.f, 0.0f, 0.f), btVector3(0.f, -1.f, 0.f), btVector3(0.f, 0.f, 0.f), true);

		turret_constraint = new btHingeConstraint(*turret_rb->get(), *body_rb->get(), btVector3(0.f, -2.25f, 0.f), btVector3(0.f, 4.f, 0.f), btVector3(0.f, -1.f, 0.f), btVector3(0.f, 0.f, 0.f));//-6.5
		turret_constraint->enableAngularMotor(true, 0.f, 10.f);
		scene->get_physics_world()->addConstraints(turret_constraint);


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

		wheel_rb_r1->get()->setIgnoreCollisionCheck(body_rb->get(), true);
		wheel_rb_r2->get()->setIgnoreCollisionCheck(body_rb->get(), true);
		wheel_rb_l1->get()->setIgnoreCollisionCheck(body_rb->get(), true);
		wheel_rb_l2->get()->setIgnoreCollisionCheck(body_rb->get(), true);

		wheel_rb_r1->get()->setIgnoreCollisionCheck(turret_rb->get(), true);
		wheel_rb_r2->get()->setIgnoreCollisionCheck(turret_rb->get(), true);
		wheel_rb_l1->get()->setIgnoreCollisionCheck(turret_rb->get(), true);
		wheel_rb_l2->get()->setIgnoreCollisionCheck(turret_rb->get(), true);
		
	}
}