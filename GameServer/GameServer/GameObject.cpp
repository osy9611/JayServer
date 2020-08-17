#include "stdafx.h"

GameObject::GameObject()
	:scale(1.0f), rotation(0.f), isDie(false), NetworkId(0)
{
}

Vector3 GameObject::GetForwardVector()
{
	return Vector3(sinf(rotation), 0.f, -cosf(rotation));
}