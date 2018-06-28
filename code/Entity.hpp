/*

Author: Daniel Fernández
Date:	04/05/2018

*/

#pragma once

#include <Model_Obj.hpp>

//#include <Scene.hpp>
#include <Rigid_Body.hpp>

using namespace glm;

namespace bullet_3da
{
	class Scene;

	class Entity
	{
	/*protected:

		Scene & scene;*/

	protected:

		shared_ptr<glt::Model> graphics_model;
		shared_ptr < Rigid_Body > physics_model;

	public:

		Entity(/*Scene * scene*/)
			/*:
			scene(*scene)*/
		{
		}

		Entity(/*Scene * scene, */const string & model_path, shared_ptr< Rigid_Body > & physics_model)
			:
			/*scene(*scene),*/
			physics_model(physics_model)
		{
			graphics_model.reset(new glt::Model_Obj(model_path));
		}

		~Entity()
		{
		}


		void update()
		{
			btTransform physics_transform;
			physics_model->get()->getMotionState()->getWorldTransform(physics_transform);
			glm::mat4 graphics_transform;
			physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));
			graphics_model->set_transformation(graphics_transform);
			//graphics_model->scale(graphics_scale.x, graphics_scale.y, graphics_scale.z);
		}

		void translate(float x, float y, float z)
		{
			btTransform transform;
			physics_model->get()->getMotionState()->getWorldTransform(transform);
			transform.setOrigin(btVector3(x, y, z));
			physics_model->get()->getMotionState()->setWorldTransform(transform);
		}

		virtual shared_ptr < Rigid_Body > getRigidBody()
		{
			return physics_model;
		}

		virtual shared_ptr<glt::Model> getModel()
		{
			return graphics_model;
		}

	protected:

		void add_constraints(Scene * scene, shared_ptr< btHingeConstraint > & constraint, btRigidBody &body1, btRigidBody &body2, btVector3 pos_body1, btVector3 pos_body2, btVector3 rot_body1, btVector3 rot_body2, bool ref_frame_A)
		{
			constraint.reset(new btHingeConstraint(body1, body2, pos_body1, pos_body2, rot_body1, rot_body2, ref_frame_A));
			constraint->enableAngularMotor(true, 0.f, 10.f);
			scene->get_physics_world()->addConstraints(constraint.get());
		}

	};
}
