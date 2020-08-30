#pragma once

class PacketProc : public GlobalSingleton<PacketProc>
{
public:
	//void AddQueue(InputMemoryStream data);
	void CheckPacket(InputMemoryStream& inInputStream, int nSessionID);

};

#define _PacketProc PacketProc::Singleton()
