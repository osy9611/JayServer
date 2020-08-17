#include "stdafx.h"

void Monster::Update(float dTime)
{
	SetPosition(GetPosition() + GetVelocity() * (2* dTime));
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