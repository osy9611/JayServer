#pragma once
class DBManager : public GlobalSingleton<DBManager>
{
public:
	DBManager();

	//계정 검색
	bool SearchAccount(InputMemoryStream& inInputStream,int nSessionID);
	//회원가입
	bool SignAccount(InputMemoryStream& inInputStream, int nSessionID);
	//캐릭터 생성
	bool CreateCharactor(InputMemoryStream& inInputStream);

	//캐릭터 위치값 생성
	bool SearchCharatorPos(InputMemoryStream& inInputStream,int nSessionID);
private:
	bool SearchAcountResult(std::string _id, std::string _pw);
	void SetCharactor(OutputMemoryStream &os,std::string _id);
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
				   PASSWORD=1111;";
};

#define _DBManager DBManager::Singleton()