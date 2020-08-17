#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}

	virtual void Update(float dTime) {}

	virtual void HandleDying() {}

	void SetRotation(float inRotation)					  { rotation = inRotation; }
	float GetRotation()								const { return rotation; }

	const Vector3& GetPosition()					const { return position; }
	void SetPosition(const Vector3& inPosition)			  { position = inPosition; }

	const Vector3& GetVelocity()					const { return velocity; }
	void SetVelocity(const Vector3& inVelocity)			  { velocity = inVelocity; }
	Vector3 GetForwardVector();

	bool CheckDie()							const { return isDie; }
	void SetDie(bool Die) { isDie = Die; }

	int GetNetworkId()						const { return NetworkId; }
	void SetNetworkID(int inNetworkId) { NetworkId = inNetworkId; }

	virtual int Write(OutputMemoryStream& inOutputStream) const { (void)inOutputStream; return 0; }
	virtual void Read(InputMemoryStream &inInputStream)			{ (void)inInputStream; }
private:
	Vector3 position;
	Vector3 velocity;

	float rotation;
	float scale;

	bool isDie;
	int NetworkId;
};

typedef std::shared_ptr< GameObject >	GameObjectPtr;