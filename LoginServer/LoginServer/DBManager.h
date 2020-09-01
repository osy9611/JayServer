#pragma once
#define DBPORT 8083

#define LOGIN_CHECK 7500
#define LOG_IN_RESULT 7501
#define SIGN_UP 7502
#define SIGN_UP_RESULT 7503
#define USERDATA 7502
class DBManager : public GlobalSingleton<DBManager>
{
public:
	void ConnectToDBServer();
	void Run();
	void Handle_Receive(const char * data,int size);
	void Send(OutputMemoryStream& os);

	//�α��� Ȯ���� DB ������ �����ֱ� ���� �Լ�
	void SetLoginPacket(InputMemoryStream& io, int nSessionID);
	void SetLoginResultPacket(InputMemoryStream& io);

	//ȸ�������� DB ������ �����ֱ� ���� �Լ�
	void SetSignUpPacket(InputMemoryStream& io, int nSessionID);
	void SetSignUpResultPacket(InputMemoryStream& io);
private:
	SOCKET m_socket;
	fd_set read;
	fd_set write;
	char cBuffer[MAX_BUF_SIZE];

	int mPacketBufferMark = 0;
	char mPacketBuffer[MAX_RECEIVE_BUFFER_LEN * 2];
};

#define _DBManager DBManager::Singleton()