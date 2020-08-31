#pragma once
#define LOGIN_CHECK 7500
#define LOG_IN_RESULT 7501
class PacketProc : public GlobalSingleton<PacketProc>
{
public:
	//void AddQueue(InputMemoryStream data);
	void CheckPacket(InputMemoryStream& inInputStream, int nSessionID);
	void CheckPacket(InputMemoryStream& inInputStream);
};

#define _PacketProc PacketProc::Singleton()
