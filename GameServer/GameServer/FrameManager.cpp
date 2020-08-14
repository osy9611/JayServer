#include "stdafx.h"

float FrameManager::GetTime()
{
	static float dB = GetTickCount();
	float dE = timeGetTime();

	dTime = (dE - dB)*0.001f;
	dB = dE;

	return dTime;
}