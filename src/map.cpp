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
    fs.open(map_name.insert(0, "maps/"), ifstream::in);
    if (!fs.is_open()) throw CFileNotFoundException(1, map_name.append(" doesn't exists"));
    char width_height[15];
    fs.getline(width_height, 15);//getting width and height
    _Width = atoi(width_height);//first number is width
    string w_h = width_height;// to slice first number
    int a = w_h.find_first_of(" ");
    _Height = atoi(&width_height[a]);
    
    _Map = new char*[_Height];
    
    for (int i = 0; i < _Height; i++)
    {
        _Map[i] = new char[_Width];
        for (int j = 0; j < _Width; j++)
        {
            char ch[2];
            ch[0] = fs.get();
            ch[1] = '\0';
            
            _Map[i][j] = atoi(ch);
        }
    }
    fs.close();
}