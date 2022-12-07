/* Collisions.h file description:
* Defines the Collisions class, and states all of the functions that it will have as defined in "Collisions.cpp".
*/

#pragma once

#include<glm/glm.hpp>
#include<iostream>
#include<vector>
#include<array>
#include<math.h>
struct AABB {
	glm::vec3 min;
	glm::vec3 max;
	AABB(glm::vec3 mi, glm::vec3 ma)
	{
		min = mi;
		max = ma;
	}
};

struct halfDAABB {
	glm::vec3 centre;
	float halfdimension;
	halfDAABB(glm::vec3 c, float hd) {
		centre = c;
		halfdimension = hd;
	}
};

class Collisions
{
public:
	static glm::vec3 testAllColl(glm::vec3& Ppos, glm::vec3 Phead, std::vector<halfDAABB> halb, AABB Pexp);
private:	
	static int testColl(glm::vec3& Ppos, glm::vec3 Phead, halfDAABB halb, AABB Pexp);

};

		