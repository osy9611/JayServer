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

	OutputMemoryStream os;
	if (SearchAcountResult(ID, PW))
	{
		os.Write((short)LOG_IN_RESULT);
		os.Write((bool)true);
		os.Write(SessionID);
		os.SetSize();
		_IOCP.SendPlayer(nSessionID, os.GetBufferPtr(), os.GetDataLength());
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

bool DBManager::SearchAcountResult(std::string _id, std::string _pw)
{
	std::string Query;

	Query = "CALL SearchAccount('"
		+ _id + "','" + _pw + "'," + "@ID)";
	if (db.Execute(Query.c_str(), tbl))
	{
		if (db.Execute("SELECT @ID", tbl))
		{
			if (!tbl.ISEOF())
			{
				std::string id;
				tbl.Get((char*)"@ID", id);
				if (id == "(null)")
				{
					std::cout << "로그인 실패!" << std::endl;
					return false;
				}
				else
				{
					std::cout << "로그인 성공!" << std::endl;
					return true;
				}
				
			}
		}
	}

	return false;
}

bool DBManager::SignAccount(InputMemoryStream& inInputStream, int nSessionID)
{
	std::string ID;
	std::string PW;
	short SessionID;

	inInputStream.Read(ID);
	inInputStream.Read(PW);
	inInputStream.Read(SessionID);

	OutputMemoryStream os;
	if (SearchAcountResult(ID, PW))
	{
		os.Write((short)SIGN_UP_RESULT);
		os.Write((bool)false);
		os.Write(SessionID);
		os.SetSize();
		_IOCP.SendPlayer(nSessionID, os.GetBufferPtr(), os.GetDataLength());

		return false;
	}
	else
	{
		SignAccountReseult(ID, PW);
		os.Write((short)SIGN_UP_RESULT);
		os.Write((bool)true);
		os.Write(SessionID);
		os.SetSize();
		_IOCP.SendPlayer(nSessionID, os.GetBufferPtr(), os.GetDataLength());
		return true;
	}
	return false;
}

bool DBManager::SignAccountReseult(std::string _id, std::string _pw)
{
	std::string Query;
	Query = "CALL SignUp('"
		+ _id + "','" + _pw + "'" + ")";
	if (db.Execute(Query.c_str(), tbl))
	{
		std::cout << "회원가입 성공!" << std::endl;
		return true;
	}
	else
	{
		std::cout << "회원가입 실패!" << std::endl;
		return false;
	}
}