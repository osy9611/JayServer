#pragma once
class Monster : public GameObject
{
public:
	Monster()
	{
		_AreaManager.SearchArea(GetPosition(), AreaIndex);
	}
	void Update(float dTime);
	void CalcDamage(float Damage);

	void Write(OutputMemoryStream &os);
	void Read(InputMemoryStream& is) {}

	float RandomSet(float min, float max);

	void MapRangeCheck();
private:
	void CollisionCheck();
private:
	float Speed;
	float Hp = 100;
	float Attack;

	float respawnTime = 20.0;
	float cntRespawnTime = 0;
	float radius = 1.2;
	int AreaIndex = 0;
};

