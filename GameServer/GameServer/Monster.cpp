#include "stdafx.h"

void Monster::Update(float dTime)
{
	MapRangeCheck();
	SetPosition(GetPosition() + GetVelocity() * (5 * dTime));
}

void Monster::MapRangeCheck()
{
	if (GetPosition().mX <= -25|| GetPosition().mX >= 25)
	{
		Vector3 Dir;
		Dir.Set(GetVelocity().mX, 0, GetVelocity().mZ);
		Dir.mX = -Dir.mX;
		SetVelocity(Dir);
	}
	if (GetPosition().mZ <= -25 || GetPosition().mZ >= 25)
	{
		Vector3 Dir;
		Dir.Set(GetVelocity().mX, 0, GetVelocity().mZ);
		Dir.mZ = -Dir.mZ;
		SetVelocity(Dir);
	}
}

void Monster::CalcDamage(float Damage)
{
	if (Hp > 0.f)
	{
		Hp -= Damage;
	}
	else
	{
		SetDie(true);
	}
}

void Monster::Write(OutputMemoryStream& os)
{
	os.Write(GetNetworkId());
	os.Write(GetPosition());
	os.Write(GetVelocity());
}

float Monster::RandomSet(float min, float max)
{
	std::random_device randDevice;
	std::mt19937 mt(randDevice());
	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(randDevice);
}