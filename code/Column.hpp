/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <memory>

#include <Entity.hpp>

namespace bullet_3da
{
	/// Represents a column object.
	/// The player is to take down columns by hitting them with the tank projectiles.
	class Column : public Entity
	{

	public:

		/// Creates a new Column.
		/// A column consists in a Dynamic_Rigid_Body of mass 10.
		Column() : Entity()
		{
			shared_ptr < Shape > shape(new Box_Shape(5.f, 25.f, 5.f));
			shared_ptr < Rigid_Body > rb(new Dynamic_Rigid_Body(shape, 10.f));
			rb->get()->setRestitution(0.f);
			rb->get()->btCollisionObject::setActivationState(DISABLE_DEACTIVATION);

			physics_model = rb;
			graphics_model.reset(new glt::Model_Obj("../../assets/Column.obj"));
		}
	};
}