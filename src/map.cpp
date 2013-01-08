//
//  map.cpp
//  Game_engine
//
//  Created by Рашид on 06.01.13.
//  Copyright (c) 2013 KubSU. All rights reserved.
//

#include "map.h"
#include <fstream>

CMap::~CMap()
{
    for (int i = 0; i < _Height; i++)
        delete[] _Map[i];
    delete[] _Map;
}

void CMap::LoadMap(string map_name)
{
    ifstream fs;
    fs.open(map_name.insert(0, "data/maps/").c_str(), ifstream::in);
    if (!fs.is_open()) throw new CFileNotFoundException(1, map_name);

    fs >> _Width >> _Height;

    _Map = new char*[_Height];

    for (int i = 0; i < _Height; i++)
    {
        _Map[i] = new char[_Width];
        string str;
        fs >> str;
        for (int j = 0; j < _Width; j++)
            _Map[i][j] = str[j] - 48;
    }
    fs.close();
}
