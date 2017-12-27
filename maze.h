#ifndef MAZE_H
#define MAZE_H

#include "cell.h"


class MyMaze{
public:
    //MyMaze();
    void createMaze();
    void destroyMaze();
    ~MyMaze();


    int _width;
    int _height;
    std::pair<int, int> _start;
    std::pair<int, int> _end;
    MazeCell** cells;
};
#endif
