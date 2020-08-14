#include "stdafx.h"

void Monster::Update()
{
	SetPosition(GetPosition() + GetVelocity() * (2*_FrameManager.GetTime()));
	
	dTime += _FrameManager.GetTime();
	if (dTime > 0.2)
	{
		std::cout <<GetNetworkId()<<"  "<<GetPosition().mX << "," << GetPosition().mY << "," << GetPosition().mZ << std::endl;
		OutputMemoryStream io;
		short size = sizeof(float) * 3 + sizeof(short) * 2 + sizeof(int);
		io.Write(size);
		short type = 1500;
		io.Write(type);
		io.Write(GetNetworkId());
		io.Write(GetPosition());
		_IOCP.SendAllPlayer(io.GetBufferPtr(), io.GetDataLength());
		dTime = 0;
	}
}

void Monster::CalcDamage(float Damage)
{
	if (Hp > 0.f)
	{
		Hp -= Damage;
	}
	else
	{
		SetDie(true);
	}
}