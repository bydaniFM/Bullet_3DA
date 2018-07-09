/*

Author: Daniel Fernández
Date:	07/07/2018

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
	/// Represents the key needed to unlock the Door.
	class Key : public Entity
	{
	public:

		/// Creates a new Key, which is a Static_Rigid_Body with collissions disabled, so in behaves like a trigger.
		/// The model currently used is one of a mill, but that doesn't affect its functionality.
		Key() : Entity()
		{
			shared_ptr < Shape > shape(new Box_Shape(12.0f, 25.0f, 12.0f));
			shared_ptr<Rigid_Body> rb(new Static_Rigid_Body(shape));

			// Trigger behaviour
			rb->get()->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
			rb->get()->setActivationState(DISABLE_DEACTIVATION);

			Entity::physics_model = rb;
			Entity::graphics_model.reset(new Model_Obj("../../assets/Mill.obj"));
		}


	};
}