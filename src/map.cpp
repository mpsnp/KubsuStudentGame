//
//  map.cpp
//  Game_engine
//
//  Created by Рашид on 06.01.13.
//  Copyright (c) 2013 KubSU. All rights reserved.
//

#include "map.h"

CMap::CMap(int width, int height)
{
    _Width = width;
    _Height = height;
    
    _Map = new char*[_Height];
    for (int i = 0; i < _Height; i++)
        _Map[i] = new char[_Width];
    /*
    ** TODO: Generate map
    */
    srand(time(NULL));
}

CMap::~CMap()
{
    for (int i = 0; i < _Height; i++)
        delete[] _Map[i];
    delete[] _Map;
}