#pragma once
#include "reactphysics3d/reactphysics3d.h"//I DID NOT WRITE REACTPHYSICS3D PLZ DO NOT SUE ME
#include <vector>
#include <iostream>
#include "Meshes.h"


class Physics {
private:
	reactphysics3d::PhysicsCommon physicsCommon;
	reactphysics3d::PhysicsWorld* world;
	const reactphysics3d::decimal timeStep = 1.0f / 60.0f;
	std::vector<reactphysics3d::RigidBody*> bodies;
public:
	Physics();
	void Step();
	void GetMeshes();//TODO
	void MakeCube(reactphysics3d::Vector3 pos, reactphysics3d::Vector3 halfd);
};