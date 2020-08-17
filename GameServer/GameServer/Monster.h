#pragma once
class Monster : public GameObject
{
public:
	void Update(float dTime);
	void CalcDamage(float Damage);

	void Write(OutputMemoryStream &os);
	void Read(InputMemoryStream& is) {}
private:
	float Speed;
	float Hp;
	float Attack;

	float dTime = 0;
};

