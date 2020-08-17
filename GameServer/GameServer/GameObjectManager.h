#pragma once
class GameObjectManager:public GlobalSingleton<GameObjectManager>
{
public:
	void Init();
	void Update();
	void DeletePlayer();
	void SendToClientPacket();

	void SendToClientPacket(int nSessionID);
	void Write(OutputMemoryStream os);
	void Read(InputMemoryStream& is);

private:
	MonsterManager *monsterManager;
	float dTime = 0;
	float SendTime = 0;
};

#define _GameObjectManager GameObjectManager::Singleton()