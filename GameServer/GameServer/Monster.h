#pragma once

enum class MonsterState
{
	Idle,
	Roaming,
	Run,
	Attack,
	Die
};

class Player;

class Monster : public GameObject
{
public:
	Monster()
	{
		_AreaManager.SearchArea(GetPosition(), AreaIndex);
	}
	void Update(float dTime);
	void CalcDamage(float Damage,std::string _targetName);

	void Write(OutputMemoryStream &os);
	void Read(InputMemoryStream& is) {}

	float RandomSet(float min, float max);

	void MapRangeCheck();
private:
	void CollisionCheck();
	void Attack(float dTime);
	void RoamingMove(float dTime);
	void DelayDie(float dTime);
private:
	//몬스터 상태
	MonsterState MT = MonsterState::Roaming;

	float Speed;
	float Hp = 100;
	float Damage;
	
	//부활 시간
	float respawnTime = 20.0;
	float cntRespawnTime = 0;
	
	float radius = 1.2;
	
	//몬스터가 위치한 지역 배열 인덱스
	int AreaIndex = 0;

	//몬스터를 공격한 캐릭터 이름
	std::string targetName;
	Player* targetPlayer;
};

