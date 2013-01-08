//
//  map.h
//  Game_engine
//
//  Created by Рашид on 06.01.13.
//  Copyright (c) 2013 KubSU. All rights reserved.
//

#ifndef __MAP_H__
#define __MAP_H__
#include <string>
#include "Model3d.h"

class CMap : public CModel3d
{
    char **_Map;
    int _Width;
    int _Height;
public:
    ~CMap();
    /*
    ** Following method loads map by name
    ** Exceptions: CFileNotFoundException
    */
    void LoadMap(string);
    /*
    ** Following properties return fields with same names
    */
    int Width()const { return _Width; }
    int Height()const { return _Height; }
    /*
    ** PrintMap returns map structure in string size width x height
    ** <width> <height>
    ** 0000000101010
    ** 1000200010200
    ** 0000000000001
    */
    std::string PrintMap()const;
    /*
    ** TODO: GetConvertedMap
    */
};

#endif /* defined(__map_h__) */