

#include <MyScene.hpp>

namespace bullet_3da
{
	MyScene::MyScene()
		:
		Scene()
	{
		Ground ground1 = Ground(this);
		//ground1.getRigidBody()->get()->getWorldTransform().setOrigin(btVector3(0, -10, 0));
		ground1.translate(0, 0, 0);
		add("ground1", make_shared<Ground>(ground1));

		Ground ground2 = Ground(this);
		ground2.translate(0, 0, -150);
		add("ground2", make_shared<Ground>(ground2));

		Ground ground3 = Ground(this);
		ground3.translate(0, 0, -300);
		add("ground3", make_shared<Ground>(ground3));

		Tank tank = Tank(this);
		//tank.translate(20, -100, -20);
		tank.getRigidBody()->get()->getWorldTransform().setOrigin(btVector3(20, 100, -20));
		add("tank", make_shared<Tank>(tank));
	}
}