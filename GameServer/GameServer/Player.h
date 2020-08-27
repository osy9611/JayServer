#pragma once

class Monster;

enum PlayerState
{
	Idle,
	Move,
	Attack
};

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
	Player() {}
	~Player() {}
	void SetData(PlayerData _data) { Data = _data; }

	void Update(float dTime);

	const char* GetName() { return Data.Name.c_str(); }

	float GetSpeed() { return Data.Speed; }
	void CalcDamage(float Damage);

	void SetData(Vector3 _pos, Vector3 _dir,short _playerState);

	void Write(OutputMemoryStream &os);
	void Read(InputMemoryStream& is);

private:
	//플레이어 데이터
	PlayerData Data;
	//플레이어의 이전 데이터
	PrevData prevData;

	PlayerState PT = Attack;

	float rotDir = 0;
	float dTime = 0;
	float timeStamp = 0;
	float latency = 0;
};

typedef std::shared_ptr<Player> PlayerPtr;