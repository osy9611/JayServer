#include "stdafx.h"


int main()
{
	std::cout << "메인 작동중" << std::endl;
	_IOCP.Initialize();

	Monster monster;

	Vector3 dir;
	dir.Set(0, 0, 1);
	monster.SetVelocity(dir);
	while (true)
	{
		//게임루프
		float a = 0;
		a = _FrameManager.GetTime();

		monster.Update();
	}

	return 0;
}