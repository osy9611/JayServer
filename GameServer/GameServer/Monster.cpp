#include "stdafx.h"

void Monster::Update(float dTime)
{
	if (Hp != 0)
	{
		MapRangeCheck();
		SetPosition(GetPosition() + GetVelocity() * (5 * dTime));
		//std::cout << GetPosition().mX << " " << GetPosition().mY << " " << GetPosition().mZ << " " << std::endl;
	}
}

void Monster::MapRangeCheck()
{
	if (GetPosition().mX <= -50|| GetPosition().mX >= 50)
	{
		Vector3 Dir;
		Dir.Set(GetVelocity().mX, 0, GetVelocity().mZ);
		Dir.mX = -Dir.mX;
		SetVelocity(Dir);
	}
	if (GetPosition().mZ <= -50 || GetPosition().mZ >= 50)
	{
		Vector3 Dir;
		Dir.Set(GetVelocity().mX, 0, GetVelocity().mZ);
		Dir.mZ = -Dir.mZ;
		SetVelocity(Dir);
	}
}

void Monster::CalcDamage(float Damage)
{
	if (Hp > 0)
	{
		Hp -= Damage;
		std::cout <<"아이디 : " <<GetNetworkId() << " 체력 : " <<Hp << std::endl;
	}
	else if (Hp <= 0.f)
	{
		Hp = 0;
		SetDie(true);
	}
}

void Monster::Write(OutputMemoryStream& os)
{
	os.Write(GetNetworkId());
	os.Write(GetPosition());
	os.Write(GetVelocity());
	os.Write(Hp);
}

float Monster::RandomSet(float min, float max)
{
	std::random_device randDevice;
	std::mt19937 mt(randDevice());
	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(randDevice);
}