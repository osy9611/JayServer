#include "stdafx.h"

void PacketProc::CheckPacket(InputMemoryStream& inInputStream, int nSessionID)
{
	short type;
	inInputStream.Read(type);

	switch (type)
	{
		break;
	}
}