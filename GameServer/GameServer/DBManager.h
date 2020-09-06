#pragma once
#define DBPORT 8083

class DBManager : public GlobalSingleton<DBManager>
{
public:
	~DBManager()
	{
		CloseHandle(m_DBServerThread);
	}
	void ConnectToDBServer();
	void Run();
	void Handle_Receive(const char* data, int size);
	void Send(OutputMemoryStream &os);

private:
	

	bool CreateDBServerThread();
private:
	SOCKET m_socket;
	fd_set read;
	fd_set write;

	HANDLE m_DBServerThread = NULL;

	char cBuffer[MAX_BUF_SIZE];

	int mPacketBufferMark = 0;
	char mPacketBuffer[MAX_RECEIVE_BUFFER_LEN * 2];

	char* ANSIToUTF8(const char* pszCode);
	char* UTF8ToANSI(const char* pszCode);
};

#define _DBManager DBManager::Singleton()