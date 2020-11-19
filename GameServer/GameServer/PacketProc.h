#pragma once
#define SEARCH_USER_DB 1400
#define SET_CHARACTOR 1401
#define USER_DATA 1500
#define USER_OUT 1600
#define CHECK_MONSTERS 1700
#define GIVE_DATA 1800
#define SET_COMPLETE 1900
class PacketProc : public GlobalSingleton<PacketProc>
{
public:
	//void AddQueue(InputMemoryStream data);
	void CheckPacket(InputMemoryStream& inInputStream,int nSessionID);
	void CheckPacket(InputMemoryStream& inInputStream);

	CriticalSection m_csPacketObj;
};

#define _PacketProc PacketProc::Singleton()

