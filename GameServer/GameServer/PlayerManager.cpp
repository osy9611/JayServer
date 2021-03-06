#include"stdafx.h"

void PlayerManager::Update(float dTime)
{
	for (auto i = PlayerList.begin(); i != PlayerList.end(); ++i)
	{
		if (i->second == nullptr)
			break;
		i->second->Update(dTime);
	}
}

void PlayerManager::Write(OutputMemoryStream& os)
{
	short playerCount = GetUserCount() + OutPlayerList.size();
	os.Write(playerCount);
	if (GetUserCount() == 1 && OutPlayerList.size() == 1)
	{
		return;
	}
	else
	{
		if (playerCount != 0)
		{
			for (auto i = PlayerList.begin(); i != PlayerList.end(); ++i)
			{
				i->second->Write(os);
			}
		}

		if (OutPlayerList.size() != 0)
		{
			short type = USER_OUT;
			std::string _name;
			for (int i = 0; i < OutPlayerList.size(); ++i)
			{
				_name = OutPlayerList.front();
				std::cout << _name << std::endl;
				os.Write(_name);
				os.Write(type);
				OutPlayerList.pop_front();
			}
		}
	}
}

void PlayerManager::CreateRead(InputMemoryStream& is)
{
	std::string _name;
	Vector3 pos;
	is.Read(_name);
	is.Read(pos.mX);
	is.Read(pos.mY);
	is.Read(pos.mZ);
	//플레이어 리스트에 없으면 리스트에 삽입함
	auto FindName = PlayerList.find(_name);

	if (PlayerList.end() == FindName)
	{
		std::cout << "캐릭터 없음" << std::endl;
		Player* _player = new Player();
		PlayerData data;
		data.Init(_name, 10, 100, 1);
		_player->SetData(data,pos);
		PlayerList.insert(std::make_pair(_name, _player));
		PlayerList[_name]->Read(is);
	}
}

void PlayerManager::UpdateRead(InputMemoryStream& is)
{
	std::string _name;
	is.Read(_name);

	//플레이어 리스트에 없으면 리스트에 삽입함
	auto FindName = PlayerList.find(_name);
	if (PlayerList.end() != FindName)
	{
		PlayerList[_name]->Read(is);
	}
}

void PlayerManager::CreateWrite(InputMemoryStream& is)
{
	std::string _name;
	is.Read(_name);

	OutputMemoryStream os;
	os.Write((short)SEARCH_USER_DB);
	os.Write(_name);
	os.SetSize();
	_DBManager.Send(os);
}

void PlayerManager::DeleteRead(InputMemoryStream& is)
{
	std::string _name;
	is.Read(_name);

	auto FindName = PlayerList.find(_name);
	if (PlayerList.end() != FindName)
	{
		OutPlayerList.push_back(_name);
		PlayerList.erase(_name);
		std::cout << _name << " 접속종료" << std::endl;		
	}
}

Player* PlayerManager :: SearchPlayer(std::string name)
{
	return PlayerList[name];
}