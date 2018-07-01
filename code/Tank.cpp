/*
Author: Daniel Fernández
Date:	27/06/2018
*/

#include <Tank.hpp>

namespace bullet_3da
{
	Tank::Tank(Scene * scene, Vector3 position)
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
		turret_rb->get()->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
		turret_rb->get()->setRestitution(0.f);
		turret_rb->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);
		shared_ptr<Entity> turret(new Entity(/*scene, */"../../assets/Turret.obj", turret_rb));

		

		scene->add("body", body);
		scene->add("turret", turret);

		//add_constraints(scene, turret_constraint, *turret_rb->get(), *body_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(0.f, 0.0f, 0.f), btVector3(0.f, 0.f, 0.f), btVector3(0.f, 0.f, 0.f), true);

		btHingeConstraint * _turret_constraint = new btHingeConstraint(*turret_rb->get(), *body_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(0.f, 0.0f, 0.f), btVector3(0.f, -1.f, 0.f), btVector3(0.f, 0.f, 0.f));
		//turret_constraint = _turret_constraint;

		//turret_constraint.reset(new btHingeConstraint(*turret_rb->get(), *body_rb->get(), btVector3(0.f, 0.f, 0.f), btVector3(0.f, 0.0f, 0.f), btVector3(0.f, 0.f, 0.f), btVector3(0.f, 0.f, 0.f)));
		_turret_constraint->enableAngularMotor(true, 0.f, 10.f);
		scene->get_physics_world()->addConstraints(_turret_constraint);
		
	}
}