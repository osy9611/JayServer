#pragma once
enum ColliderType
{
	Capsule,
	Box,
	Sphere
};

class ColliderData
{
public:
	//데이터를 셋팅
	void SetData(Vector3 _pos, float _radius, int _ct);

	//해당 콜라이더 타입을 확인 후 충돌 처리
	bool CheckCollider(Vector3 _playerPos,Vector3 _dir);

	const Vector3& GetPosition() const { return pos; }
	const float& GetRadius() const { return radius; }
private:

	bool SphereCollider(Vector3 _playerPos) { return false; }
	bool CircleCollider(Vector3 _playerPos,Vector3 _dir);
	bool BoxCollider(Vector3 _playerPos) { return false; }

	Vector3 pos;
	float radius;
	ColliderType CT;
};

