#ifndef CELL_H
#define CELL_H

#include <stdio.h>
#include <iostream>

class MazeCell{
public:
    MazeCell(){
    	_element = ' ';
    	cost = 0;
    	Manhattan = 0;
    	_f = 0;
    	parent = NULL;
    	location.first = -1;
        location.second = -2;
    	visited = false;
    };

    char _element;                  //check if accessable. Value 'y'=accessable. 'n'=not accessable.
    int cost;
    MazeCell* parent;
    std::pair <int,int> location;
    bool visited;                   //check if already visit
    int Manhattan;
    int _f;
};
#endif
