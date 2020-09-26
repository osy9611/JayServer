#include "stdafx.h"

void ColliderData::SetData(Vector3 _pos, float _radius, int _ct)
{
	pos = _pos;
	radius = _radius;
	CT = static_cast<ColliderType>(_ct);
}

bool ColliderData::CheckCollider(Vector3 _playerPos,Vector3 _dir)
{
	switch (CT)
	{
	case Capsule:
		return CircleCollider(_playerPos,_dir);
		break;
	case Box:
		return BoxCollider(_playerPos);
		break;
	case Sphere:
		return SphereCollider(_playerPos);
		break;
	}

	return false;
}

bool ColliderData::CircleCollider(Vector3 _playerPos,Vector3 _dir)
{
	float targetRadius = 1;
	Vector3 sourcePos(pos.mX, 0, pos.mZ);

	Vector3 delta = _playerPos - sourcePos;
	float distSq = delta.Length();
	float collisionDist = (radius + targetRadius);
	if (distSq <= collisionDist)
	{
		//sourcePos.Normaize();
		delta.Normaize();
		float angle = Dot(_dir, delta);
		std::cout << angle << std::endl;
		if (angle >0.f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}