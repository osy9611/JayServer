#include "stdafx.h"

AreaManager::AreaManager()
{
	
}

void AreaManager::CreateMapText(const char* filename)
{
	std::ifstream ifs(filename);
	if (ifs.fail())
	{
		std::cout << "저장된 정보가 없거나 파일 오류입니다" << std::endl;
		std::cout << filename << std::endl;
		return;
	}

	MapData _data;
	Vector3 _pos;
	int _ct;
	float _radius;
	int nodeCount, colCount;
	std::string line;

	//첫 줄에는 공간 분할한 노드의 갯수가 기입되어 있다.
	getline(ifs, line);
	sscanf(line.data(), "%d;", &nodeCount);

	//노드의 갯수만 큼 for문을 돌려 데이터를 읽어온다.
	for (int i = 0; i < nodeCount; ++i)
	{
		ColliderData _colData;
		//맵의 첫 좌표랑 끝 좌표
		getline(ifs, line);
		sscanf(line.data(), "%f;%f;%f;%f;", &_data.sx, &_data.sy, &_data.ex, &_data.ey);
		//맵에 있는 오브젝트 들의 데이터
		getline(ifs, line);
		sscanf(line.data(), "%d;", &colCount);

		//만약 맵에 있는 오브젝트들의 갯수가 0이 아니면 오브젝트를 읽어온다
		if (colCount > 0)
		{
			for (int j = 0; j < colCount; ++j)
			{
				getline(ifs, line);
				sscanf(line.data(), "%f;%f;%f;%d;%f;", &_pos.mX, &_pos.mY, &_pos.mZ, &_ct, &_radius);
				_colData.SetData(_pos, _radius, _ct);
				_data.PushColData(_colData);
			}
		}
		data.push_back(_data);
		_data.Reset();
	}

	std::cout << "방 데이터 로드 완료" << std::endl;
}

bool AreaManager::SearchArea(Vector3 _pos, int&index)
{
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i].sx <= _pos.mX && _pos.mX  <= data[i].ex&&
			data[i].ey <= _pos.mZ && _pos.mZ <= data[i].sy)
		{
			index = i;
			break;
		}
	}

	return false;
}

bool AreaManager::InAreaCheck(int index, Vector3 _pos)
{
	if (data[index].sx <= _pos.mX && _pos.mX <= data[index].ex&&
		data[index].ey <= _pos.mZ && _pos.mZ <= data[index].sy)
	{
		return true;
	}
	else
	{
		return false;
	}
}