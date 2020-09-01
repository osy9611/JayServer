#include "stdafx.h"

void PacketProc::CheckPacket(InputMemoryStream& inInputStream, int nSessionID)
{
	short type;
	inInputStream.Read(type);

	switch (type)
	{
	case LOGIN_CHECK:
		_DBManager.SetLoginPacket(inInputStream, nSessionID);
		break;
	case SIGN_UP:
		_DBManager.SetSignUpPacket(inInputStream, nSessionID);
		break;
	}
}

void PacketProc::CheckPacket(InputMemoryStream& inInputStream)
{
	short type;
	inInputStream.Read(type);

	switch (type)
	{
	case LOG_IN_RESULT:
		_DBManager.SetLoginResultPacket(inInputStream);
		break;
	case SIGN_UP_RESULT:
		_DBManager.SetSignUpResultPacket(inInputStream);
		break;
	}
}