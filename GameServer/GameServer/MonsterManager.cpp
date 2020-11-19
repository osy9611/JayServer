#include"stdafx.h"

void MonsterManager::Init()
{
	for (int i = 0; i < NORMAL_MONSTER_COUNT; ++i)
	{
		Monster* monster = new Monster();
		Vector3 Pos,Dir;
		Pos.Set(RandomSet(-50, 50), -1, RandomSet(-50, 50));
		Dir.Set(RandomSet(-1, 1), 0, RandomSet(-1, 1));
		monster->SetPosition(Pos);
		monster->SetVelocity(Dir);
		monster->SetNetworkID(i);

		monsterList.insert(std::make_pair(i, monster));
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
	short monsterCount = GetMonsterCount();
	os.Write(monsterCount);
	if (monsterCount != 0)
	{
		for (int i = 0; i < NORMAL_MONSTER_COUNT; ++i)
		{
			monsterList[i]->Write(os);
		}
	}
}

void MonsterManager::CalcMonsterDamage(InputMemoryStream& is)
{
	std::string userName;
	is.Read(userName);
	Player* playerPos = _GameObjectManager.playerManager->PlayerList[userName];
	short monsterCount;
	is.Read(monsterCount);
	short id;
	if (monsterCount != 0)
	{
		for (size_t i = 0; i < monsterCount; ++i)
		{
			is.Read(id);
			float angle = Dot(playerPos->GetVelocity(), monsterList[i]->GetPosition());
			if (fabs(angle) <180)
			{
				monsterList[id]->CalcDamage(10,userName);
			}
		}
	}
}