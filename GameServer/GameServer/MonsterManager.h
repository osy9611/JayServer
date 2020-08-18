#pragma once
#define NORMAL_MONSTER_COUNT 6
class MonsterManager
{
public:
	void Init();
	void Update(float dTime);

	float RandomSet(float min, float max);

	float GetMonsterCount() { return monsterList.size(); }
	void Write(OutputMemoryStream& os);
	void Read(InputMemoryStream& is);
	std::vector<Monster*> monsterList;
};