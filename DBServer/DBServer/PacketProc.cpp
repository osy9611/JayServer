#include "stdfx.h"

void PacketProc::CheckPacket(InputMemoryStream& inInputStream, int nSessionID)
{
	std::cout << "패킷 들어옴" << std::endl;
	short type;
	inInputStream.Read(type);

	switch (type)
	{
	case LOGIN_CHECK:
		std::cout << "로그인 채크 확인중" << std::endl;
		_DBManager.SearchAccount(inInputStream, nSessionID);
		break;
	case SIGN_UP:
		std::cout << "회원가입 확인중" << std::endl;
		_DBManager.SignAccount(inInputStream, nSessionID);
		break;
	}
}