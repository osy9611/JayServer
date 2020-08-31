#include "stdfx.h"

DBManager::DBManager()
{
	::CoInitialize(NULL);

	if (!db.Open("", "", CnnStr))
	{
		db.GetErrorErrStr(ErrStr);
		std::cout << ErrStr << "\n";
	}
	else
	{
		std::cout << "Database Connect Success!!" << std::endl;
	}
	::CoUninitialize();
}

bool DBManager:: SearchAccount(InputMemoryStream& inInputStream, int nSessionID)
{
	std::string ID;
	std::string PW;
	short SessionID;

	inInputStream.Read(ID);
	inInputStream.Read(PW);
	inInputStream.Read(SessionID);

	std::string Query;

	OutputMemoryStream os;

	Query = "CALL SearchAccount('"
		+ ID + "','" + PW + "'," + "@ID)";
	if (db.Execute(Query.c_str(), tbl))
	{
		std::cout << "로그인 성공!" << std::endl;
		os.Write((short)LOG_IN_RESULT);
		os.Write((bool)true);
		os.Write(SessionID);
		os.SetSize();
		_IOCP.SendPlayer(nSessionID,os.GetBufferPtr(),os.GetDataLength());
		return true;
	}
	else
	{
		std::cout << "유저 데이터가 없습니다" << std::endl;
		os.Write((short)LOG_IN_RESULT);
		os.Write((bool)false);
		os.Write(SessionID);
		os.SetSize();
		_IOCP.SendPlayer(nSessionID, os.GetBufferPtr(), os.GetDataLength());
		return false;
	}

	return false;
}
