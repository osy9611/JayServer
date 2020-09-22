#include "stdafx.h"


int main()
{
	std::cout << "메인 작동중" << std::endl;
	_IOCP.Initialize();
	_DBManager.ConnectToDBServer();
	_AreaManager.CreateMapText("../Map/World.txt");
	_GameObjectManager.Init();

	while (true)
	{
		_GameObjectManager.Update();
	}

	return 0;
}