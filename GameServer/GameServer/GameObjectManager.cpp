#include"stdafx.h"

void GameObjectManager::Init()
{
	monsterManager = new MonsterManager();
	monsterManager->Init();
	playerManager = new PlayerManager();
}

void GameObjectManager::Update()
{
	float time = 0;
	time = _FrameManager.GetTime();
	playerManager->Update(time);
	monsterManager->Update(time);
	dTime += time;
	if (dTime > 0.3)
	{
		SendToClientPacket();
		dTime = 0;
	}
}

void GameObjectManager::SendToClientPacket()
{
	OutputMemoryStream os;
	short type = USER_DATA;
	os.Write(type);

	playerManager->Write(os);

	monsterManager->Write(os);

	os.SetSize();
	_IOCP.SendAllPlayer(os.GetBufferPtr(), os.GetDataLength());
}

void GameObjectManager::SendToClientPacket(int nSessionID)
{
	OutputMemoryStream os;
	os.Write(USER_DATA);
	monsterManager->Write(os);

	os.SetSize();
	_IOCP.SendPlayer(nSessionID,os.GetBufferPtr(), os.GetDataLength());
}

void GameObjectManager::UpdatePlayerManager(InputMemoryStream& is)
{
	playerManager->UpdateRead(is);
}

void GameObjectManager::DeletePlayerManager(InputMemoryStream& is)
{
	playerManager->DeleteRead(is);
}