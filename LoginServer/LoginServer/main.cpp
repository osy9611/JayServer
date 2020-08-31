#include "stdafx.h"


int main()
{
	std::cout << "Login Server" << std::endl;
	_IOCP.Initialize();

	_DBManager.ConnectToDBServer();

	return 0;
}