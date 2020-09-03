#pragma once
class DBManager : public GlobalSingleton<DBManager>
{
public:
	DBManager();

	//계정 검색
	bool SearchAccount(InputMemoryStream& inInputStream,int nSessionID);
	bool SignAccount(InputMemoryStream& inInputStream, int nSessionID);
	bool a(std::string _id, std::string _pw);
	bool a1(std::string _id, std::string _pw);
private:
	bool SearchAcountResult(std::string _id, std::string _pw);
	
	bool SignAccountReseult(std::string _id, std::string _pw);
private:
	Database db;
	Table tbl;

	//에러 검출
	char ErrStr[200];

	//ODBC를 연결하기 위한 문자열
	char CnnStr[200] = "DRIVER={MySQL ODBC 8.0 ANSI Driver};\
				   SERVER=localhost;\
				   DATABASE=iocpserver;\
				   USER=root;\
				   PASSWORD=@ppgk38629;";
};

#define _DBManager DBManager::Singleton()