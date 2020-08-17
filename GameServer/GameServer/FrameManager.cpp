#include "stdafx.h"

float FrameManager::GetTime()
{
	static int dB = GetTickCount();
	int dE = timeGetTime();

	dTime = (dE - dB)*0.001f;
	dB = dE;

	return dTime;
}

void FrameManager::Timer()
{
	dTime += GetTime();
	if (dTime > 0.1)
	{
		_GameObjectManager.SendToClientPacket();
		dTime = 0;
	}
}