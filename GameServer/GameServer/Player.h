#pragma once

struct PlayerData
{
	std::string Name;
	float Speed;
	float Hp, Mp;
	float Attack;

	void Init(std::string _name, float _speed, float _hp, float _attack)
	{
		Name = _name;
		Speed = _speed;
		Hp = _hp;
		Mp = 100;
		Attack = _attack;
	}
};

//패킷 받기 이전의 데이터
struct PrevData
{
	Vector3 pos,dir;
	float rot;

	void SetData(Vector3 _pos, Vector3 _dir, float _rot)
	{
		pos = _pos;
		dir = _dir;
		rot = _rot;
	}
};

class Player : public GameObject
{
public:
	void SetData(PlayerData _data) { Data = _data; }

	void Update(float dTime);

	const char* GetName() { return Data.Name.c_str(); }

	float GetSpeed() { return Data.Speed; }
	void CalcDamage(float Damage);

	void SetVector(Vector3 _pos, Vector3 _dir,float _rot);

	void Write(OutputMemoryStream &os);
	void Read(InputMemoryStream& is);
private:
	PlayerData Data;

	PrevData prevData;

	float dTime = 0;
	float timeStamp = 0;

	bool isMove = true;
};

