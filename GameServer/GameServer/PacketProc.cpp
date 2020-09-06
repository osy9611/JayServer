#include "stdafx.h"

void PacketProc::CheckPacket(InputMemoryStream& inInputStream, int nSessionID)
{
	short type;
	inInputStream.Read(type);

	switch(type)
	{
	case GIVE_DATA:
		_GameObjectManager.SendToClientPacket(nSessionID);
		break;
	case SET_COMPLETE:
		_IOCP.SetSessionSendOk(nSessionID);
		break;
	case USER_DATA:
		_GameObjectManager.UpdatePlayerManager(inInputStream);
		break;
	case USER_OUT:
		_GameObjectManager.DeletePlayerManager(inInputStream);
		break;
	case CHECK_MONSTERS:
		_GameObjectManager.CheckMonsterDamage(inInputStream);
		break;
	}
}

void PacketProc::CheckPacket(InputMemoryStream& inInputStream)
{
	short type;
	inInputStream.Read(type);

	switch (type)
	{
	case USER_DATA:
		break;
	}
}