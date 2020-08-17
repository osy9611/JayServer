#pragma once
class FrameManager:public GlobalSingleton<FrameManager>
{
public:
	float GetTime();
	void Timer();
private:
	float dTime = 0;
};

#define _FrameManager FrameManager::Singleton()