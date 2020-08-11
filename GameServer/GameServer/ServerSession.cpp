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

bool ServerSession::SendPacket()
{
	CriticalSectionLock lock(m_csSock);

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
	std::cout << "데이터 들어옴" << std::endl;
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