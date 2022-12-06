//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Collisions.h file description:
* Defines the Collisions class, and states all of the functions that it will have as defined in "Collisions.cpp".
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include<glm/glm.hpp>


struct AABB
{
	glm::vec3 min;
	glm::vec3 max;
	AABB(glm::vec3 mi, glm::vec3 ma)
	{
		min = mi;
		max = ma;
	}
};


struct plane 
{
	glm::vec3 min;
	glm::vec3 max;
	int axis;
	plane(glm::vec3 mi, glm::vec3 ma,int ax)
	{
		min = mi;
		max = ma;
		axis = ax;
	}
};


class Collisions
{
	public:
		static void testPColl(glm::vec3& Ppos, glm::vec3 Phead, plane pl, AABB Pexp);
};

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 