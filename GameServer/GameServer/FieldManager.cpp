#include "stdafx.h"

void FieldManager::SetField()
{
	//FILE* stream = fopen("../Map/World.txt", "rt");	//필드 자료를 불러옴
	//int sizeX = 250, sizeZ = 250;
	//float z;
	//SetMapSize(sizeX + 1, sizeZ + 1);
	//
	//for (size_t i = 0; i < sizeX + 1; ++i)
	//{
	//	z = (sizeX / 2) - i;
	//	for (size_t j = 0; j < sizeZ + 1; ++j)
	//	{
	//		fscanf(stream, "%c", &map[i][j]);
	//		char dummy = map[i][j];
	//		fieldData.map[i][j] = atof(&dummy);
	//		fieldData.mapNode.SetPos(-(250 / 2) + j,z);			
	//	}
	//}
	//fclose(stream);
}

void FieldManager::SetMapSize(int sizeX, int sizeZ)
{
	map = new char*[sizeX];
	for (int i = 0; i < sizeX; ++i)
	{
		for (int j = 0; j < sizeZ; ++j)
		{
			map[i] = new char[sizeZ];
		}
	}
}
