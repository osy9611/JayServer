#pragma once
#define LOGIN_CHECK 7500
#define LOG_IN_RESULT 7501
#define SIGN_UP 7502
#define SIGN_UP_RESULT 7503
class PacketProc : public GlobalSingleton<PacketProc>
{
public:
	//void AddQueue(InputMemoryStream data);
	void CheckPacket(InputMemoryStream& inInputStream, int nSessionID);
	void CheckPacket(InputMemoryStream& inInputStream);
};

#define _PacketProc PacketProc::Singleton()
