#pragma once
class PlayerManager
{
public:
	void Update(float dTime);

	void SetData();

	void Write(OutputMemoryStream& os);
	void UpdateRead(InputMemoryStream& is);
	void DeleteRead(InputMemoryStream& is);

	const short GetUserCount() const { return PlayerList.size(); }
	std::unordered_map<std::string, Player*> PlayerList;
	std::deque<std::string> OutPlayerList;
};

