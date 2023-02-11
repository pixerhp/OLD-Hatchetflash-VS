#include "Physics.h"

Physics::Physics() {
	world = physicsCommon.createPhysicsWorld();
}

void Physics::Step() {
	world->update(timeStep);
	// Get the updated position of the body 
	const reactphysics3d::Transform& transform = bodies[0]->getTransform();
	const reactphysics3d::Vector3& position = transform.getPosition();

	// Display the position of the body 
	std::cout << "Body Position: (" << position.x << ", " <<
		position.y << ", " << position.z << ")" << std::endl;
}

void Physics::MakeCube(reactphysics3d::Vector3 pos, reactphysics3d::Vector3 halfd) {
	bodies.push_back(world->createRigidBody(reactphysics3d::Transform(pos, reactphysics3d::Quaternion::identity())));
	bodies[bodies.size()-1]->addCollider(physicsCommon.createBoxShape(halfd), reactphysics3d::Transform(reactphysics3d::Vector3(0,0,0), reactphysics3d::Quaternion::identity()));
}