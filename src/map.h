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

class CMap
{
    char **_Map;
    int _Width;
    int _Height;
public:
    /*
    ** Constructor takes width and height and immediately generates the map
    */
    CMap(int, int);
    ~CMap();
    /*
    ** Following properties return fields with same names
    */
    int Width()const;
    int Height()const;
    /*
    ** PrintMap returns map structure in string size width x height
    ** <width> <height>
    ** 0000000101010
    ** 1000200010200
    ** 0000000000001
    */
    std::string PrintMap()const;
};

#endif /* defined(__map_h__) */
