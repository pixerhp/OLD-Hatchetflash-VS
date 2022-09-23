#include "Collisions.h"

void Collisions::testPColl(glm::vec3& Ppos, glm::vec3 Phead, plane pl, AABB Pexp)
{
	//Big boy box (useful)
	AABB BigBox(glm::vec3(Ppos + Pexp.min.x), glm::vec3(Ppos + Pexp.max + Phead));


	//some basic AABB on AABB action
	if (!(BigBox.min.x <= pl.max.x &&
		BigBox.max.x >= pl.min.x &&
		BigBox.min.y <= pl.max.y &&
		BigBox.max.y >= pl.min.y &&
		BigBox.min.z <= pl.max.z &&
		BigBox.max.z >= pl.min.z))
	{Ppos += Phead; return;}
		

	//switch statement (scary)
	switch (pl.axis) {
	case 0:
		if (Phead.x > 0)
			Ppos.x = pl.min.x + Pexp.min.x;
		else
			Ppos.x = pl.min.x + Pexp.max.x;

		Ppos += glm::vec3(0.0f,Phead.y,Phead.z);
		return;
	case 1:
		if (Phead.y > 0)
			Ppos.y = pl.min.y + Pexp.min.y;
		else
			Ppos.y = pl.min.y + Pexp.max.y;

		Ppos += glm::vec3(Phead.x, 0.0f, Phead.z);
		return;
	case 2:
		if (Phead.z > 0)
			Ppos.z = pl.min.z + Pexp.min.z;
		else
			Ppos.z = pl.min.z + Pexp.max.z;

		Ppos += glm::vec3(Phead.x, Phead.y, 0.0f);
		return;
	default:
		return;
	}
	return;
}
