#include "maze.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*  This function fill a maze with a txt file
 *  It sets width and height
 *  _start/_end<column, row>
 *  cells[row][column]
 *  index starts from 0: the upper left sell is cells[0][0]
 */
void MyMaze::createMaze(){
    char fileName[256];
    cout<<"Enter the name of the maze file: "<<endl;
    cin.get(fileName, 256);
    ifstream mazeFile(fileName);
    string* line;
    line = new string[50];
    getline (mazeFile, line[0]);
    _width = line[0].length();
    int k=1;
    while(getline(mazeFile, line[k])){
        k++;
    }
    _height = k;
    //read in the data
    cells = new MazeCell*[_height];
    for(int i=0; i<_height; i++){
        cells[i] = new MazeCell[_width];
        for(int j=0; j<_width; j++){
            cells[i][j]._element = line[i][j];
            cells[i][j].location.second = i;
            cells[i][j].location.first = j;
            if(line[i][j] == 'P'){
                _start.first = j;
                _start.second = i;
            }
            else if(line[i][j] == '.'){
                _end.first = j;
                _end.second = i;
            }
        }
    }
    //free line
    delete[] line;
//for test
/*
    for(int a=0; a<_height; a++){
        for(int b=0; b<_width; b++){
            cout<<cells[a][b].getElem();
        }
        cout<<endl;
    }
    cout<<endl;
    mazeFile.close();

*/
}

void MyMaze::destroyMaze(){
    for(int i=0; i<_height; i++){
        delete[] cells[i];
    }
    delete[] cells;
}

MyMaze::~MyMaze(){
    destroyMaze();
    return;
}
