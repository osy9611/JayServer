#pragma once
class FrameManager:public GlobalSingleton<FrameManager>
{
public:
	float GetTime();
private:
	float dTime = 0;
};

#define _FrameManager FrameManager::Singleton()