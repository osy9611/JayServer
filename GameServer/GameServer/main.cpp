#include "stdafx.h"


int main()
{
	std::cout << "메인 작동중" << std::endl;
	_IOCP.Initialize();

	_GameObjectManager.Init();

	while (true)
	{
		_GameObjectManager.Update();
	}

	return 0;
}