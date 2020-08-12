#include "stdafx.h"



ServerSession::ServerSession(int m_index)
{
	this->m_index = m_index;
	ZeroMemory(&m_RecvBuffer, sizeof(Buffer));
	ZeroMemory(&m_SendBuffer, sizeof(Buffer));
	m_RecvBuffer.state = RECV;
	m_SendBuffer.state = SEND;
	m_Socket = INVALID_SOCKET;
	//InitSocket();
}


ServerSession::~ServerSession()
{
}

bool ServerSession::InitSocket()
{
	WSADATA wsaData;

	//! [WinSock 2.2] LOAD 
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != 0)
	{
		std::cout << "Failed WinSock2.2 DLL Load!\n";
		return false;
	}

	//! Create Socket 
	m_Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (m_Socket == INVALID_SOCKET)
	{
		std::cout << "소켓 생성 실패!\n";
		return false;
	}

	return true;
}

void ServerSession::SetBuffer()
{
	memset(&m_RecvBuffer, 0, sizeof(Buffer));
	memset(&m_SendBuffer, 0, sizeof(Buffer));
}

bool ServerSession::SendPacket(const char* data,int size)
{
	CriticalSectionLock lock(m_csSock);

	m_SendBuffer.wsaBuf.len = size;
	m_SendBuffer.wsaBuf.buf = (char*)data;
	DWORD dwRecvNumBytes = 0;

	//SendPacket
	WSASend(m_Socket,
		&(m_SendBuffer.wsaBuf),
		1,
		&dwRecvNumBytes,
		0,
		(LPWSAOVERLAPPED)&m_SendBuffer,
		NULL
	);

	return true;
}

bool ServerSession::RecvPacket()
{
	CriticalSection lock(m_csSock);
	DWORD dwFlag = 0;
	DWORD dwRecvNumByte = 0;

	m_RecvBuffer.wsaBuf.len = MAX_BUF_SIZE;
	m_RecvBuffer.wsaBuf.buf = m_RecvBuffer.cBuffer;
	m_RecvBuffer.state = RECV;

	int result = WSARecv(m_Socket,
		&(m_RecvBuffer.wsaBuf),
		1,
		&dwRecvNumByte,
		&dwFlag,
		(LPWSAOVERLAPPED)&(m_RecvBuffer),
		NULL);

	if (result == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING))
	{
		std::cout << "Recv 에러" << std::endl;
		return true;
	}
	return true;
}

void ServerSession::Handle_Receive(const char* data, int size)
{
	/*
	네트워크 특성상 클라이언트에서 서버로 데이터를보내기 요청을 동시에 여러 번 하면, 서버에서는 클라이언트에서 보내는 단위대로 받지 않는다.
	한꺼번에 모두 받을 수도 있고 여러 번 나눠서 받을 수 있다.(즉, 클라이언트는 Send를 두 번 했는데, 서버에서는 Receive가 한 번만 발생한다.)
	이런, 경우를 처리하기 위해서 먼저 받은 데이터 mPacketBuffeer에 저장한 후 클라이언트에 동시에 여러번 요청하면서 서버는 한 번에 다 받으므로,
	각 요청별로 나누어 처리한다. 그리고 클라이언트가 보낸 데이터중 일부 도착한 경우, 우선은 처리하지 않고 남겨놓았다가 다음에 받은 데이터와 연결하여
	처리한다.
	*/

	//받은 데이터를 패킷 버퍼에 저장
	memcpy(&mPacketBuffer[mPacketBufferMark], data, size);

	int nPacketData = mPacketBufferMark + size;
	int nReadData = 0;

	while (nPacketData > 0)	//받은 데이터를 모두 처리할 때까지 반복
	{
		//남은 데이터가 패킷 해더보다 작으면 중단
		if (nPacketData < sizeof(PacketHeader))
		{
			break;
		}

		PacketHeader* pHeader = (PacketHeader *)&mPacketBuffer[nReadData];

		if (pHeader->size <= nPacketData)	//처리할 수 있는 만큼 데이터가 있다면 패킷을 처리
		{
			InputMemoryStream io((char*)data, pHeader->size);
			_PacketProc.CheckPacket(io, GetSessionID());
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

void ServerSession::CloseSocket()
{
	CSLOCK(m_csSock)
	{
		if (m_Socket != INVALID_SOCKET)
		{
			shutdown(m_Socket, SD_BOTH);
			closesocket(m_Socket);
			m_Socket = INVALID_SOCKET;
		}
	}
}