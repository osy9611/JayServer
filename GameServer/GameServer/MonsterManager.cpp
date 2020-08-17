#include"stdafx.h"

void MonsterManager::Init()
{
	for (int i = 0; i < NORMAL_MONSTER_COUNT; ++i)
	{
		Monster* monster = new Monster();
		Vector3 Pos,Dir;
		Pos.Set(RandomSet(-10, 10), 0, RandomSet(-10, 10));
		Dir.Set(RandomSet(-1, 1), 0, RandomSet(-1, 1));
		monster->SetPosition(Pos);
		monster->SetVelocity(Dir);
		monster->SetNetworkID(i);

		monsterList.push_back(monster);
	}
}

void MonsterManager::Update(float dTime)
{
	for (int i = 0; i < NORMAL_MONSTER_COUNT; ++i)
	{
		monsterList[i]->Update(dTime);
	}
}

float MonsterManager::RandomSet(float min, float max)
{
	std::random_device randDevice;
	std::mt19937 mt(randDevice());
	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(randDevice);
}

void MonsterManager::Write(OutputMemoryStream& os)
{
	for (int i = 0; i < NORMAL_MONSTER_COUNT; ++i)
	{
		monsterList[i]->Write(os);
	}
}