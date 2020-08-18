#include "stdafx.h"

void PacketProc::CheckPacket(InputMemoryStream& inInputStream, int nSessionID)
{
	short type;
	inInputStream.Read(type);

	switch(type)
	{
	case USER_DATA:
		_GameObjectManager.UpdatePlayerManager(inInputStream);
		break;
	case USER_OUT:
		_GameObjectManager.DeletePlayerManager(inInputStream);
		break;
	}
}