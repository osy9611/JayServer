#pragma once
class Monster : public GameObject
{
public:
	void Update(float dTime);
	void CalcDamage(float Damage);

	void Write(OutputMemoryStream &os);
	void Read(InputMemoryStream& is) {}

	float RandomSet(float min, float max);

	void MapRangeCheck();
private:
	float Speed;
	float Hp;
	float Attack;

	float dTime = 0;
};

