#pragma once
class Monster : public GameObject
{
public:
	//Monster();
	//~Monster();

	void Update();

	void CalcDamage(float Damage);

private:
	float Speed;
	float Hp;
	float Attack;

	float dTime = 0;
};

