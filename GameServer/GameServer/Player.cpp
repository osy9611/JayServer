#include"stdafx.h"

void Player::Update(float dTime)
{
	SetPosition(GetPosition() + GetVelocity() * (Data.Speed * dTime));
}

void Player::CalcDamage(float Damage)
{

}

void Player::Write(OutputMemoryStream &os)
{
	os.Write(Data.Name);
	os.Write(GetPosition());
	os.Write(GetRotation());
}

void Player::Read(InputMemoryStream& is)
{
	isMove = false;
	//방향값,현재 위치,회전값을 읽음
	Vector3 dir, pos;
	float rot;
	is.Read(pos);
	is.Read(dir);
	is.Read(rot);
	SetVector(pos, dir, rot);
	isMove = true;
}

void Player::SetVector(Vector3 _pos, Vector3 _dir,float _rot)
{
	prevData.SetData(GetPosition(), GetVelocity(), GetRotation());
	SetPosition(_pos);
	SetVelocity(_dir);
	SetRotation(_rot);
}