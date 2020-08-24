#include"stdafx.h"

void Player::Update(float dTime)
{
	if (PT == Move)
	{
		SetPosition(GetPosition() + GetVelocity() * (Data.Speed * dTime));
	}
}

void Player::CalcDamage(float Damage)
{

}

void Player::Write(OutputMemoryStream &os)
{
	os.Write(Data.Name);
	os.Write(GetPosition());
	os.Write(GetVelocity());
	os.Write(static_cast<short>(PT));
}

void Player::Read(InputMemoryStream& is)
{
	//방향값,현재 위치,회전값을 읽음
	Vector3 dir, pos;
	short state;
	is.Read(pos);
	is.Read(dir);
	is.Read(state);
	SetData(pos, dir,state);
}

void Player::SetData(Vector3 _pos, Vector3 _dir,short _playerState)
{
	prevData.SetData(GetPosition(), GetVelocity(), GetRotation());
	//SetPosition(_pos);
	SetVelocity(_dir);
	PT = static_cast<PlayerState>(_playerState);
}