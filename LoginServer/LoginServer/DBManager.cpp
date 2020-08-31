#include "stdafx.h"


void DBManager::ConnectToDBServer()
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "소캣 생성 실패" << std::endl;
	}

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(DBPORT);
	int ret = connect(m_socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (ret == SOCKET_ERROR)
	{
		std::cout << "연결 실패" << std::endl;
	}

	FD_ZERO(&read);
	FD_ZERO(&write);
	FD_SET(m_socket, &read);
	Run();
}

void DBManager::Run()
{
	while (true)
	{

		int ret = select(m_socket +1, &read, &write, NULL, NULL);
		if (ret == SOCKET_ERROR)
		{
			std::cout << "Select 에러" << std::endl;
			break;
		}

		if (FD_ISSET(m_socket, &read))
		{
			//데이터 받기
			ret = recv(m_socket, (char*)&cBuffer, MAX_BUF_SIZE, 0);

			if (ret == 0 || ret == SOCKET_ERROR)
			{
				continue;
			}
			
			Handle_Receive(cBuffer, ret);
		}
	}

}

void DBManager::Send(OutputMemoryStream& os)
{
	int ret = send(m_socket, (char*)os.GetBufferPtr(), os.GetDataLength(), 0);
}

void DBManager::SetLoginPacket(InputMemoryStream& io, int nSessionID)
{
	std::string id;
	std::string pw;
	io.Read(id);
	io.Read(pw);

	OutputMemoryStream os;
	os.Write((short)LOGIN_CHECK);
	os.Write(id);
	os.Write(pw);
	os.Write((short)nSessionID);
	os.SetSize();
	Send(os);
}

void DBManager::SetLoginResultPacket(InputMemoryStream& io)
{
	bool result;
	short SessionID;
	io.Read(result);
	io.Read(SessionID);

	OutputMemoryStream os;
	os.Write((short)LOG_IN_RESULT);
	os.Write(result);
	os.SetSize();
	_IOCP.SendPlayer(SessionID, os.GetBufferPtr(), os.GetDataLength());
}

void DBManager::Handle_Receive(const char * data, int size)
{
	/*
	네트워크 특성상 클라이언트에서 서버로 데이터를 보내기 요청을 동시에 여러 번 하면, 서버에서는 클라이언트에서 보내는 단위대로 받지 않는다.
	한꺼번에 모두 받을 수도 있고 여러번 나눠서 받을 수 있다.(즉, 클라이언트는 Send를 두 번 했는데, 서버에서는 Receive가 한 번만 발생한다.)
	이런, 경우를 처리하기 위해서 먼저 받은 데이터 mPacketBuffer에 저장한 후 클라이언트에 동시에 여러번 요청하면서 서버는 한 번에 다 받으므로,
	각 요청별로 나누어 처리한다. 그리고 클라이언트가 보낸 데이터중 일부 도착한 경우, 우선은 처리하지 않고 남겨놓았다가 다음에 받은 데이터와 연결하여
	처리한다.
	*/

	//받은 데이터를 패킷 버퍼에 저장
	memcpy(&mPacketBuffer[mPacketBufferMark], data, size);

	int nPacketData = mPacketBufferMark + size;
	int nReadData = 0;

	while (nPacketData > 0)	//받은 데이터를 모두 처리할 때까지 반복
	{
		//남은 데이터가 패킷 헤더보다 작으면 중단
		if (nPacketData < sizeof(PacketHeader))
		{
			break;
		}

		PacketHeader* pHeader = (PacketHeader*)&mPacketBuffer[nReadData];

		if (pHeader->size <= nPacketData)	//처리할 수 있는 만큼 데이터가 있다면 패킷을 처리
		{
			InputMemoryStream io((char*)data, pHeader->size);
			_PacketProc.CheckPacket(io);
			nPacketData -= pHeader->size;
			nReadData += pHeader->size;
		}
		else
		{
			break;	//패킷으로 처리할 수 없는 만큼이 아니면 중단
		}
	}

	if (nPacketData > 0)
	{
		char TempBuffer[MAX_RECEIVE_BUFFER_LEN * 2] = { 0, };
		memcpy(&TempBuffer[0], &mPacketBuffer[nReadData], nPacketData);
		memcpy(&mPacketBuffer[0], &TempBuffer[0], nPacketData);
	}

	//남은 데이터 양을 저장하고 데이터 받기 요청
	mPacketBufferMark = nPacketData;
}
