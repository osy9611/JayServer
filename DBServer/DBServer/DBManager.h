#pragma once
class DBManager
{
public:
	DBManager();

	//계정 검색
	bool SearchAccount(const char* ID, const char* PW);
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

