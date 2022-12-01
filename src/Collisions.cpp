/* Collisions.cpp file description:
* (The functions here are also stated in "Collisions.h".)
*/

#include "Collisions.h"

int sgn(float n) {
	return (n > 0)?1:-1;
}

void Collisions::testPColl(glm::vec3& Ppos, glm::vec3 Phead, halfDAABB halb, AABB Pexp)
{
	// Smal boy box (useful)
	AABB SmalBox(glm::vec3(Ppos + Pexp.min+Phead), glm::vec3(Ppos + Pexp.max + Phead));

	glm::vec3 intersect, collvec=glm::vec3(0,0,0), newHead;

	// some basic AABB on AABB action
	if (!(SmalBox.min.x <= halb.centre.x + halb.halfdimension &&
		  SmalBox.max.x >= halb.centre.x - halb.halfdimension &&
		  SmalBox.min.y <= halb.centre.y + halb.halfdimension &&
		  SmalBox.max.y >= halb.centre.y - halb.halfdimension &&
		  SmalBox.min.z <= halb.centre.z + halb.halfdimension &&
		  SmalBox.max.z >= halb.centre.z - halb.halfdimension))
	{Ppos += Phead; return;}	
	

	intersect.x = abs(halb.centre.x + halb.halfdimension - SmalBox.min.x) < abs(halb.centre.x - halb.halfdimension - SmalBox.max.x) ? halb.centre.x + halb.halfdimension - SmalBox.min.x : halb.centre.x - halb.halfdimension - SmalBox.max.x;
	intersect.y = abs(halb.centre.y + halb.halfdimension - SmalBox.min.y) < abs(halb.centre.y - halb.halfdimension - SmalBox.max.y) ? halb.centre.y + halb.halfdimension - SmalBox.min.y : halb.centre.y - halb.halfdimension - SmalBox.max.y;
	intersect.z = abs(halb.centre.z + halb.halfdimension - SmalBox.min.z) < abs(halb.centre.z - halb.halfdimension - SmalBox.max.z) ? halb.centre.z + halb.halfdimension - SmalBox.min.z : halb.centre.z - halb.halfdimension - SmalBox.max.z;
	
	if (abs(intersect.x) < abs(intersect.y)){
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
	std::cout << intersect.x << " " << intersect.y << " " << intersect.z << "\n";
	std::cout << collvec.x << " " << collvec.y <<" " << collvec.z<<"\n";
	newHead = Phead;
	if (collvec.x != 0) {
		if (collvec.x > 0) {
			newHead.x = 0;
			Ppos += newHead;
			Ppos.x = halb.centre.x + halb.halfdimension+Pexp.max.x;
		}
		else {
			newHead.x = 0;
			Ppos += newHead;
			Ppos.x = halb.centre.x - halb.halfdimension-Pexp.max.x;
		}
		return;
	}
	if (collvec.y != 0) {
		if (collvec.y > 0) {
			newHead.y = 0;
			Ppos += newHead;
			Ppos.y = halb.centre.y + halb.halfdimension + Pexp.max.y;
		}
		else {
			newHead.y = 0;
			Ppos += newHead;
			Ppos.y = halb.centre.y - halb.halfdimension - Pexp.max.y;
		}
		return;
	}
	if (collvec.z != 0) {
		if (collvec.z > 0) {
			newHead.z = 0;
			Ppos += newHead;
			Ppos.z = halb.centre.z + halb.halfdimension + Pexp.max.z;
		}
		else {
			newHead.z = 0;
			Ppos += newHead;
			Ppos.z = halb.centre.z - halb.halfdimension - Pexp.max.z;
		}
		return;
	}
	
	return;
}

