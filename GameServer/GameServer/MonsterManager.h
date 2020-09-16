#pragma once
#define NORMAL_MONSTER_COUNT 50
class MonsterManager
{
public:
	void Init();
	void Update(float dTime);

	float RandomSet(float min, float max);
	float GetMonsterCount() { return monsterList.size(); }

	void CalcMonsterDamage(InputMemoryStream& is);

	void Write(OutputMemoryStream& os);
	void Read(InputMemoryStream& is);
	std::unordered_map<int,Monster*> monsterList;
};