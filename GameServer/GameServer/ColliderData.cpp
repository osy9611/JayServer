#include "stdafx.h"

void ColliderData::SetData(Vector3 _pos, float _radius, int _ct)
{
	pos = _pos;
	radius = _radius;
	CT = static_cast<ColliderType>(_ct);
}

bool ColliderData::CheckCollider(Vector3 _playerPos)
{
	switch (CT)
	{
	case Capsule:
		return CircleCollider(_playerPos);
		break;
	case Box:
		return BoxCollider(_playerPos);
		break;
	case Sphere:
		return SphereCollider(_playerPos);
		break;
	}
}

bool ColliderData::CircleCollider(Vector3 _playerPos)
{
	float targetRadius = 1;
	Vector3 sourcePos(pos.mX, 0, pos.mZ);

	Vector3 delta = _playerPos - sourcePos;
	float distSq = delta.LengthSq();
	float collisionDist = (radius + targetRadius);
	if (distSq < (collisionDist * collisionDist))
	{
		return true;
	}
	return false;
}