#include "stdafx.h"


int main()
{
	std::cout << "메인 작동중" << std::endl;
	IOCP* server = new IOCP;

	server->Initialize();

	while (true)
	{
		//게임루프
	}

	return 0;
}