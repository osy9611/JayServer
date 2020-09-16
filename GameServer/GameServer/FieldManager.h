#pragma once

struct Node
{
	std::vector<float> x;
	std::vector<float> z;

	void SetPos(float _x, float _z)
	{
		x.push_back(_x);
		z.push_back(_z);
	}
};

struct FieldData
{
	std::string MapName;
	float **map;
	Node mapNode;
	void SetSize(int sizeX, int sizeZ)
	{
		map = new float*[sizeX];
		for (int i = 0; i < sizeX; ++i)
		{
			for (int j = 0; j < sizeZ; ++j)
			{
				map[i] = new float[sizeZ];
			}
		}
	}
};

class FieldManager : public GlobalSingleton<FieldManager>
{
public:
	void SetField();
private:
	void SetMapSize(int sizeX, int sizeZ);
private:
	FieldData fieldData;
	char **map;
};

#define _FieldManager FieldManager::Singleton()