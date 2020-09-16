#pragma once
class GameObjectManager:public GlobalSingleton<GameObjectManager>
{
public:
	void Init();
	void Update();
	void DeletePlayer();
	void SendToClientPacket();

	void CreatePlayerManager(InputMemoryStream& is);
	void SetPlayerManager(InputMemoryStream& is);
	void UpdatePlayerManager(InputMemoryStream& is);
	void DeletePlayerManager(InputMemoryStream& is);
	void SendToClientPacket(int nSessionID);

	void CheckMonsterDamage(InputMemoryStream& is);

	void Write(OutputMemoryStream os);
	void Read(InputMemoryStream& is);

	PlayerManager *playerManager;
	MonsterManager *monsterManager;
private:

	float dTime = 0;
	float SendTime = 0;
};

#define _GameObjectManager GameObjectManager::Singleton()