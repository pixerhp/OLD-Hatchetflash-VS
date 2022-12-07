/* Collisions.cpp file description:
* (The functions here are also stated in "Collisions.h".)
*/

#include "Collisions.h"

int sgn(float n) {
	return n > 0?1:-1;
}

glm::vec3 Collisions::testAllColl(glm::vec3& Ppos, glm::vec3 Phead, std::vector<halfDAABB> halb, AABB Pexp) {
	std::vector<halfDAABB> halbd;
	for (const halfDAABB& h : halb) {
		if (abs(h.centre.x - Ppos.x) < 3.0f) {
			halbd.push_back(h);
			continue;
		}
		if (abs(h.centre.y - Ppos.y) < 3.0f) {
			halbd.push_back(h);
			continue;
		}
		if (abs(h.centre.z - Ppos.z) < 3.0f) {
			halbd.push_back(h);
			continue;
		}
	}
	glm::vec3 NewPos = Ppos;
	glm::vec3 NewHead=Phead;
	int w;
	for (const halfDAABB& h : halb) {
		
		w = testColl(NewPos, NewHead, h, Pexp);
		switch (w)
		{
		case 0:
			NewHead.x = 0.0f;
			break;
		case 1:
			NewHead.y = 0.0f;
			break;
		case 2:
			NewHead.z = 0.0f;
			break;
		default:
			break;
		}
	}
	Ppos = NewPos;
	return NewHead;
}

int Collisions::testColl(glm::vec3& Ppos, glm::vec3 Phead, halfDAABB halb, AABB Pexp)
{

	// Smal boy box (useful)
	AABB SmalBox(glm::vec3(Ppos + Pexp.max+Phead), glm::vec3(Ppos + Pexp.min + Phead));

	glm::vec3 intersect,collvec=glm::vec3(0,0,0);

	// some basic AABB on AABB action
	if (!(SmalBox.min.x <= halb.centre.x + halb.halfdimension &&
		  SmalBox.max.x >= halb.centre.x - halb.halfdimension &&
		  SmalBox.min.y <= halb.centre.y + halb.halfdimension &&
		  SmalBox.max.y >= halb.centre.y - halb.halfdimension &&
		  SmalBox.min.z <= halb.centre.z + halb.halfdimension &&
		  SmalBox.max.z >= halb.centre.z - halb.halfdimension))
	{return -1;}	

	intersect.x = abs(halb.centre.x + halb.halfdimension - SmalBox.min.x) < abs(halb.centre.x - halb.halfdimension - SmalBox.max.x) ? halb.centre.x + halb.halfdimension - SmalBox.min.x : halb.centre.x - halb.halfdimension - SmalBox.max.x;
	intersect.y = abs(halb.centre.y + halb.halfdimension - SmalBox.min.y) < abs(halb.centre.y - halb.halfdimension - SmalBox.max.y) ? halb.centre.y + halb.halfdimension - SmalBox.min.y : halb.centre.y - halb.halfdimension - SmalBox.max.y;
	intersect.z = abs(halb.centre.z + halb.halfdimension - SmalBox.min.z) < abs(halb.centre.z - halb.halfdimension - SmalBox.max.z) ? halb.centre.z + halb.halfdimension - SmalBox.min.z : halb.centre.z - halb.halfdimension - SmalBox.max.z;
	


	if (abs(intersect.x) < abs(intersect.y)) {
		if (abs(intersect.x) < abs(intersect.z))
			collvec.x = sgn(intersect.x);
		else
			collvec.z = sgn(intersect.z);
	}
	else {
		if (abs(intersect.y) < abs(intersect.z))
			collvec.y = sgn(intersect.y);
		else
			collvec.z = sgn(intersect.z);
	}
	if (collvec.x != 0) {
		if (collvec.x > 0) {
			Ppos.x = halb.centre.x + halb.halfdimension + Pexp.min.x;
		}
		else {
			Ppos.x = halb.centre.x - halb.halfdimension + Pexp.max.x;
		}
		return 0;
	}
	if (collvec.y != 0) {
		if (collvec.y > 0) {
			Ppos.y = halb.centre.y + halb.halfdimension + Pexp.min.y;
		}
		else {
			Ppos.y = halb.centre.y - halb.halfdimension + Pexp.max.y;
		}
		return 1;
	}
	if (collvec.z != 0) {
		if (collvec.z > 0) {
			Ppos.z = halb.centre.z + halb.halfdimension + Pexp.min.z;
		}
		else {
			Ppos.z = halb.centre.z - halb.halfdimension + Pexp.max.z;
		}
		return 2;
	}

	return -1;
}

