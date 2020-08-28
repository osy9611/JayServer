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

bool DBManager:: SearchAccount(const char* _id, const char* _pw)
{
	std::string ID = _id;
	std::string PW = _pw;
	std::string Query;

	Query = "CALL SearchAccount('"
		+ ID + "','" + PW + "'," + "@ID)";
	if (db.Execute(Query.c_str(), tbl))
	{
		std::cout << "로그인 성공!" << std::endl;
		if (db.Execute("SELECT @ID", tbl))
		{
			if (!tbl.ISEOF())
			{
				char id[60];
				tbl.Get((char*)"@ID", id);
				std::cout << id << std::endl;
			}
		}
		
		return true;
	}
	else
	{
		std::cout << "유저 데이터가 없습니다" << std::endl;
		return false;
	}

	return false;
}
