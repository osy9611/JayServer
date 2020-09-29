#include "stdafx.h"

void Monster::Update(float dTime)
{
	if (Hp != 0)
	{
		if (!_AreaManager.InAreaCheck(AreaIndex, GetPosition()))
		{
			_AreaManager.SearchArea(GetPosition(), AreaIndex);
			//std::cout << "유저가 " << AreaIndex << " 번 배열로 이동" << std::endl;
		}		
		SetPosition(GetPosition() + GetVelocity() * (5 * dTime));
		CollisionCheck();
		MapRangeCheck();
		//std::cout << GetPosition().mX << " " << GetPosition().mY << " " << GetPosition().mZ << " " << std::endl;
	}
	else
	{
		if (respawnTime <= cntRespawnTime)
		{
			std::cout << "몬스터 재 생성 " <<cntRespawnTime << std::endl;
			cntRespawnTime = 0;
			Vector3 Pos;
			Pos.Set(RandomSet(-50, 50), -1, RandomSet(-50, 50));
			SetPosition(Pos);
			SetDie(false);
			Hp = 100;
		}
		else
		{
			cntRespawnTime += dTime;
		}
	}
}

void Monster::MapRangeCheck()
{
	if (GetPosition().mX <= -60|| GetPosition().mX >= 60)
	{
		Vector3 Dir;
		Dir.Set(GetVelocity().mX, 0, GetVelocity().mZ);
		Dir.mX = -Dir.mX;
		SetVelocity(Dir);
	}
	if (GetPosition().mZ <= -60 || GetPosition().mZ >= 60)
	{
		Vector3 Dir;
		Dir.Set(GetVelocity().mX, 0, GetVelocity().mZ);
		Dir.mZ = -Dir.mZ;
		SetVelocity(Dir);
	}
}

void Monster::CollisionCheck()
{
	MapData it = _AreaManager.GetCollisionObjects(AreaIndex);
	for (int i = 0; i < it.colData.size(); ++i)
	{
		Vector3 targetPosition(it.colData[i].GetPosition().mX, 0, it.colData[i].GetPosition().mZ);
		float targetRadius = it.colData[i].GetRadius();

		Vector3 delta = targetPosition - GetPosition();
		float distSq = delta.LengthSq();
		float collisionDist = (radius + targetRadius);
		if (distSq < (collisionDist * collisionDist))
		{
			Vector3 Dir;
			Dir.Set(-GetVelocity().mX, 0, -GetVelocity().mZ);
			SetVelocity(Dir);
		}
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