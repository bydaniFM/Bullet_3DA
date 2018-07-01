/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#include <Entity.hpp>
#include <Scene.hpp>

namespace bullet_3da
{
	void Entity::add_constraints
	(
		Scene						      * scene,
		shared_ptr< btHingeConstraint >   & constraint,
		btRigidBody						  & body1,
		btRigidBody						  & body2,
		btVector3							pos_body1,
		btVector3							pos_body2,
		btVector3							rot_body1,
		btVector3							rot_body2,
		bool								ref_frame_A
	)
	{
		constraint.reset(new btHingeConstraint(body1, body2, pos_body1, pos_body2, rot_body1, rot_body2, ref_frame_A));
		constraint->enableAngularMotor(true, 0.f, 10.f);
		scene->get_physics_world()->addConstraints(constraint.get());
	}
}