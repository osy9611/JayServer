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
	bool isSend = 0;
	time = _FrameManager.GetTime();
	playerManager->Update(time);
	monsterManager->Update(time);
	isSend = _FrameManager.TickCount();
	if (isSend)
	{
		SendToClientPacket();
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
	short type = USER_DATA;
	os.Write(type);

	playerManager->Write(os);
	monsterManager->Write(os);
	os.SetSize();

	_IOCP.SendPlayer(nSessionID,os.GetBufferPtr(), os.GetDataLength());
}

void GameObjectManager::CreatePlayerManager(InputMemoryStream& is)
{
	playerManager->CreateRead(is);
}

void GameObjectManager::UpdatePlayerManager(InputMemoryStream& is)
{
	playerManager->UpdateRead(is);
}

void GameObjectManager::DeletePlayerManager(InputMemoryStream& is)
{
	CSLOCK(m_csObjManager)
	{
		playerManager->DeleteRead(is);
	}
}

void GameObjectManager::SetPlayerManager(InputMemoryStream& is)
{
	playerManager->CreateWrite(is);
}

void GameObjectManager::CheckMonsterDamage(InputMemoryStream& is)
{
	monsterManager->CalcMonsterDamage(is);
}