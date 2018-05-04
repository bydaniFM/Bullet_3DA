

#include <Rigid_Body.hpp>

namespace bullet_3da
{

	Rigid_Body::Rigid_Body()
	{
		this->body = make_shared< btRigidBody > ();

		{
			shared_ptr< btCollisionShape > shape(new btSphereShape(btScalar(1.)));

			// Create Dynamic Objects.

			btTransform transform;
			transform.setIdentity();
			transform.setOrigin(btVector3(0, 10, 0));

			btScalar  mass = 1.f;
			btVector3 localInertia(0, 0, 0);

			shape->calculateLocalInertia(mass, localInertia);

			// Using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

			shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
			btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get(), localInertia);

			sphere_body.reset(new btRigidBody(info));

			sphere_body->setRestitution(1.0);

			dynamicsWorld->addRigidBody(sphere_body.get());

			// Save the smart pointers for automatic cleanup.

			rigidBodies.push_back(sphere_body);
			motionStates.push_back(state);
			collisionShapes.push_back(shape);
		}
	}

	//Para hacer que sea un trigger

	//body.reset(new btColl

	//body->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

}
