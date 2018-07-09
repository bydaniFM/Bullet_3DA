//
//
//#include <Physics_World.hpp>
//
//namespace bullet_3da
//{
//	//Physics_World::Physics_World()
//	//{
//	//	// Collision configuration contains default setup for memory, collision setup.
//	//	// Advanced users can create their own configuration.
//
//	//	btDefaultCollisionConfiguration collisionConfiguration;
//
//	//	// Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded).
//
//	//	btCollisionDispatcher collisionDispatcher(&collisionConfiguration);
//
//	//	// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
//
//	//	btDbvtBroadphase overlappingPairCache;
//
//	//	// The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded).
//
//	//	btSequentialImpulseConstraintSolver constraintSolver;
//
//	//	// Create and configure the physiscs world:
//
//	//	this->dynamicsWorld = make_shared<btDiscreteDynamicsWorld>
//	//	(
//	//		new btDiscreteDynamicsWorld
//	//		(
//	//			&collisionDispatcher,
//	//			&overlappingPairCache,
//	//			&constraintSolver,
//	//			&collisionConfiguration
//	//		)
//
//	//	);
//
//	//	dynamicsWorld->setGravity(btVector3(0, -10, 0));
//	//}
//}