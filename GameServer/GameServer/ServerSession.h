#pragma once
class ServerSession
{
public:
	ServerSession(int m_index);
	~ServerSession();

	bool InitSocket();

	bool SendPacket();
	bool RecvPacket();

	void CloseSocket();

	void SetBuffer();

	int GetSessionID() { return m_index; }
public:
	SOCKET		m_Socket;

	Buffer		m_RecvBuffer;
	Buffer		m_SendBuffer;
private:
	int m_index;

	CriticalSection m_csSock;
};

