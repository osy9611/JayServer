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
		SetCharactor(os, ID);
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
		+ _id + "','" + _pw + "'" + ")";
	if (db.Execute(Query.c_str(), tbl))
	{
		if (!tbl.ISEOF())
		{
			std::string id;
			tbl.Get((char*)"ID", id);
			if (id == "(null)")
			{
				std::cout << "로그인 실패!" << std::endl;
				return false;
			}
			else
			{
				std::cout << id <<" 로그인 성공!" << std::endl;
				return true;
			}

		}
	}
	return false;
}

void DBManager::SetCharactor(OutputMemoryStream &os, std::string _id)
{
	std::string query2;
	query2 = "call SetCharactorCount('"
		+ _id + "'"")";

	std::string query;
	query = "call SetCharactors('"
		+ _id + "'"")";
	int _userCount = 0;

	if (db.Execute(query2.c_str(), tbl))
	{

		tbl.Get((char*)"CharactorCount", _userCount);
		std::cout << _userCount << std::endl;
		os.Write((short)_userCount);
	}
	if (_userCount > 0)
	{
		if (db.Execute(query.c_str(), tbl))
		{
			while (!tbl.ISEOF())
			{
				std::string id;
				int _level;
				int _class;
				tbl.Get((char*)"CharactorName", id);
				os.Write(id);
				tbl.Get((char*)"CharactorLevel", _level);
				os.Write((short)_level);
				tbl.Get((char*)"Class", _class);
				os.Write((short)_class);
				tbl.MoveNext();
			}
		}

	}
	
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

bool DBManager::CreateCharactor(InputMemoryStream& inInputStream)
{
	std::string Id, Name, Query;
	short Class;
	inInputStream.Read(Id);
	inInputStream.Read(Name);
	inInputStream.Read(Class);
	Query = "CALL CreateCharactor('"
		+ Id + "','" + Name + "'," + std::to_string(Class) + ")";
	if (db.Execute(Query.c_str(), tbl))
	{
		std::cout << "캐릭터 기록 완료" << std::endl;
		return true;
	}
	else
	{
		std::cout << "캐릭터 기록 실패" << std::endl;
		return false;
	}
}

bool DBManager::SearchCharatorPos(InputMemoryStream& inInputStream,int nSessionID)
{
	std::string Name, Query;

	inInputStream.Read(Name);

	Query = "CALL SearchCharactorPos('" + Name + "',@x,@y,@z)";

	if (db.Execute(Query.c_str(), tbl))
	{
		if (db.Execute("SELECT @x,@y,@z",tbl))
		{
			std::cout << "캐릭터 데이터 가져옴" << std::endl;
			OutputMemoryStream os;
			float pos;
			os.Write((short)SEARCH_USER_DB);
			os.Write(Name);
			tbl.Get((char*)"@x", pos);
			os.Write(pos);
			tbl.Get((char*)"@y", pos);
			os.Write(pos);
			tbl.Get((char*)"@z", pos);
			os.Write(pos);
			os.SetSize();
			_IOCP.SendPlayer(nSessionID, os.GetBufferPtr(), os.GetDataLength());
		}
		return true;
	}
	else
	{
		std::cout << "캐릭터 데이터 못가져옴" << std::endl;
	}
	return false;
}