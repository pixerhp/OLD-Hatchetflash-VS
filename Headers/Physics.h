#pragma once
#include "reactphysics3d/reactphysics3d.h"//I DID NOT WRITE REACTPHYSICS3D PLZ DO NOT SUE ME
#include <vector>
#include <iostream>
#include "Meshes.h"


class Physics {
private:
	reactphysics3d::PhysicsCommon physicsCommon;
	reactphysics3d::PhysicsWorld* world;
	std::vector<reactphysics3d::RigidBody*> bodies;
	std::vector<reactphysics3d::BoxShape*> boxes;
public:
	const reactphysics3d::decimal timeStep = 1.0f / 60.0f;
	Physics();
	void Step();
	void GetNewMeshes(std::vector<Mesh>& m);
	void GetTransfrom(std::vector<glm::vec3>& t);
	void GetRotation(std::vector<glm::vec4>& r);
	void MakeCube(reactphysics3d::Vector3 pos, reactphysics3d::Vector3 halfd);
	void MakeFloor(reactphysics3d::Vector3 pos, reactphysics3d::Vector3 halfd);
};