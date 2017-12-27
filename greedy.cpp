#include "maze.h"
#include <queue>
#include <stack>
#include <math.h>
using namespace std;
void print(MyMaze &maze){
    for(int a=0; a<maze._height; a++){
        for(int b=0; b<maze._width; b++){
            cout<<maze.cells[a][b]._element;
        }
        cout<<endl;
    }

}

/*param: maze: the maze reference
        cost: the total cost in the trace as a number.
 *description: trace the path and cost for Astar() function.
 */
vector <std::pair<int, int>> trace(MyMaze &maze, int &cost){
    cost=0;
    MazeCell end = maze.cells[maze._end.second][maze._end.first];
    vector <std::pair<int, int>> ret;
    MazeCell cur = maze.cells[maze._end.second][maze._end.first];
    MazeCell start = maze.cells[maze._start.second][maze._start.first];
    while (cur.location.first!=start.location.first || cur.location.second!=start.location.second){
        cost++;
        ret.push_back(cur.parent->location);
        maze.cells[cur.location.second][cur.location.first]._element='.';
        cur=*cur.parent;
    }
    return ret;
}

/*param: Two MazeCell first and goal.
 *description: heuristic function for Astar() function.
 */
int _Manhattan(MazeCell &first, MazeCell &goal){
    pair<int,int> one=first.location;
    pair<int,int> final_=goal.location;

    int m1= abs(one.first - final_.first)+abs(one.second - final_.second);
    return m1;
}

/*param: /
 *description: compare function for priority_queue "frontier"
 */
struct Compare{
    bool operator()(MazeCell const& c1, MazeCell const& c2){
        return c1.Manhattan > c2.Manhattan;
    }
};

/*param: /
 *description: compare function for priority_queue "frontier" in Astar() function
 */
struct CompareAstar{
    bool operator()(MazeCell const& c1, MazeCell const& c2){
        return c1._f > c2._f;
    }
};

/*param: maze:the maze reference
         cost: actual cost from one point in the maze to goal.
         path: actual path from one point in the maze to goal.
         expand: number of node expand.
 *description: find the distanse and path between two point using greedy best-first search
 */

void greedy(MyMaze &maze, int &cost, vector <std::pair<int, int>> &path,int &expand){
    MazeCell start= MazeCell();
    MazeCell goal = MazeCell();
    start.location=maze._start;
    start.visited=true;
    goal .location=maze._end;
    goal .visited=false;
    bool reach=false;
    std::priority_queue<MazeCell, vector<MazeCell>, Compare> frontier;
    MazeCell* curr = &start;
    MazeCell** map =maze.cells;
    while(!reach){
        pair<int,int> cur_location= curr->location;
        if(cur_location.first < maze._width-1){
            pair<int,int> t1(cur_location.first+1,cur_location.second); //east
            MazeCell east=map[t1.second][t1.first];
            if (east._element!='%'&& east.visited==false){
                east.Manhattan = _Manhattan(east, goal);
                east.parent=&maze.cells[cur_location.second][cur_location.first];
                east.visited=true;
                map[t1.second][t1.first]=east;
                frontier.push(east);
            }
        }
        if(cur_location.first>0){
            pair<int,int> t2(cur_location.first-1,cur_location.second); //west
            MazeCell west=map[t2.second][t2.first];
            if (west._element!='%'&& west.visited==false){
                west.Manhattan = _Manhattan(west, goal);
                west.parent=&maze.cells[cur_location.second][cur_location.first];
                west.visited=true;
                map[t2.second][t2.first]=west;
                frontier.push(west);
            }
        }
        if(cur_location.second < maze._height-1){
            pair<int,int> t3(cur_location.first,cur_location.second+1); //north
            MazeCell north=map[t3.second][t3.first];
            if (north._element!='%'&& north.visited==false){
                north.Manhattan = _Manhattan(north, goal);
                north.parent=&maze.cells[cur_location.second][cur_location.first];
                north.visited=true;
                map[t3.second][t3.first]=north;
                frontier.push(north);
            }
        }
        if(cur_location.second>0){
            pair<int,int> t4(cur_location.first,cur_location.second-1); //sourth
            MazeCell sourth=map[t4.second][t4.first];
            if (sourth._element!='%'&& sourth.visited==false){
                sourth.Manhattan = _Manhattan(sourth, goal);
                sourth.parent=&maze.cells[cur_location.second][cur_location.first];
                sourth.visited=true;
                map[t4.second][t4.first]=sourth;
                frontier.push(sourth);
            }
        }
        MazeCell next=frontier.top();
        frontier.pop();
        expand++;
        if(next.location.first==goal.location.first &&next.location.second==goal.location.second)
            reach=true;
        curr=&next;
    }
    path=trace(maze,cost);

}

/*param: maze:the maze reference
         cost: actual cost from one point in the maze to goal.
         path: actual path from one point in the maze to goal.
         expand: number of node expand.
 *description: find the distanse and path between two point using bfs search
 */

void bfs(MyMaze &maze, int &cost, vector <std::pair<int, int>> &path,int &expand){
    MazeCell start= MazeCell();
    MazeCell goal = MazeCell();
    start.location=maze._start;
    start.visited=true;
    goal .location=maze._end;
    goal .visited=false;
    bool reach=false;
    std::queue<MazeCell> frontier;
    MazeCell* curr = &start;
    MazeCell** map =maze.cells;
    while(!reach){
        pair<int,int> cur_location= curr->location;
        if(cur_location.first < maze._width-1){
            pair<int,int> t1(cur_location.first+1,cur_location.second); //east
            MazeCell east=map[t1.second][t1.first];
            if (east._element!='%'&& east.visited==false){
                east.Manhattan = _Manhattan(east, goal);
                east.parent=&maze.cells[cur_location.second][cur_location.first];
                east.visited=true;
                map[t1.second][t1.first]=east;
                frontier.push(east);
            }
        }
        if(cur_location.first>0){
            pair<int,int> t2(cur_location.first-1,cur_location.second); //west
            MazeCell west=map[t2.second][t2.first];
            if (west._element!='%'&& west.visited==false){
                west.Manhattan = _Manhattan(west, goal);
                west.parent=&maze.cells[cur_location.second][cur_location.first];
                west.visited=true;
                map[t2.second][t2.first]=west;
                frontier.push(west);
            }
        }
        if(cur_location.second < maze._height-1){
            pair<int,int> t3(cur_location.first,cur_location.second+1); //north
            MazeCell north=map[t3.second][t3.first];
            if (north._element!='%'&& north.visited==false){
                north.Manhattan = _Manhattan(north, goal);
                north.parent=&maze.cells[cur_location.second][cur_location.first];
                north.visited=true;
                map[t3.second][t3.first]=north;
                frontier.push(north);
            }
        }
        if(cur_location.second>0){
            pair<int,int> t4(cur_location.first,cur_location.second-1); //sourth
            MazeCell sourth=map[t4.second][t4.first];
            if (sourth._element!='%'&& sourth.visited==false){
                sourth.Manhattan = _Manhattan(sourth, goal);
                sourth.parent=&maze.cells[cur_location.second][cur_location.first];
                sourth.visited=true;
                map[t4.second][t4.first]=sourth;
                frontier.push(sourth);
            }
        }
        MazeCell next=frontier.front();
        frontier.pop();
        expand++;
        if(next.location.first==goal.location.first &&next.location.second==goal.location.second)
            reach=true;
        curr=&next;
    }
    path=trace(maze,cost);

}

/*param: maze:the maze reference
         cost: actual cost from one point in the maze to goal.
         path: actual path from one point in the maze to goal.
         expand: number of node expand.
 *description: find the distanse and path between two point using dfs search
 */

void dfs(MyMaze &maze, int &cost, vector <std::pair<int, int>> &path,int &expand){
    MazeCell start= MazeCell();
    MazeCell goal = MazeCell();
    start.location=maze._start;
    start.visited=true;
    goal .location=maze._end;
    goal .visited=false;
    bool reach=false;
    std::stack<MazeCell> frontier;
    MazeCell* curr = &start;
    MazeCell** map =maze.cells;
    while(!reach){
        pair<int,int> cur_location= curr->location;
        if(cur_location.first < maze._width-1){
            pair<int,int> t1(cur_location.first+1,cur_location.second); //east
            MazeCell east=map[t1.second][t1.first];
            if (east._element!='%'&& east.visited==false){
                east.Manhattan = _Manhattan(east, goal);
                east.parent=&maze.cells[cur_location.second][cur_location.first];
                east.visited=true;
                map[t1.second][t1.first]=east;
                frontier.push(east);
            }
        }
        if(cur_location.first>0){
            pair<int,int> t2(cur_location.first-1,cur_location.second); //west
            MazeCell west=map[t2.second][t2.first];
            if (west._element!='%'&&west.visited == false){
                west.Manhattan = _Manhattan(west, goal);
                west.parent=&maze.cells[cur_location.second][cur_location.first];
                west.visited=true;
                map[t2.second][t2.first]=west;
                frontier.push(west);
            }
        }
        if(cur_location.second < maze._height-1){
            pair<int,int> t3(cur_location.first,cur_location.second+1); //north
            MazeCell north=map[t3.second][t3.first];
            if (north._element!='%'&&north.visited==false){
                north.Manhattan = _Manhattan(north, goal);
                north.parent=&maze.cells[cur_location.second][cur_location.first];
                north.visited=true;
                map[t3.second][t3.first]=north;
                frontier.push(north);
            }
        }
        if(cur_location.second>0){
            pair<int,int> t4(cur_location.first,cur_location.second-1); //sourth
            MazeCell sourth=map[t4.second][t4.first];
            if (sourth._element!='%'&&sourth.visited==false){
                sourth.Manhattan = _Manhattan(sourth, goal);
                sourth.parent=&maze.cells[cur_location.second][cur_location.first];
                sourth.visited=true;
                map[t4.second][t4.first]=sourth;
                frontier.push(sourth);
            }
        }
        MazeCell next=frontier.top();
        frontier.pop();
        expand++;
        if(next.location.first==goal.location.first &&next.location.second==goal.location.second)
            reach=true;
        curr=&next;
    }
    path=trace(maze,cost);

}

/*param: maze:the maze reference
         cost: actual cost from one point in the maze to goal.
         path: actual path from one point in the maze to goal.
         expand: number of node expand.
 *description: find the distanse and path between two point using AStar search
 */

void Astar(MyMaze &maze, int &cost, vector <std::pair<int, int>> &path,int &expand){
    MazeCell start= MazeCell();
    MazeCell goal = MazeCell();
    start.location=maze._start;
    start.visited=true;
    goal .location=maze._end;
    goal .visited=false;
    bool reach=false;
    std::priority_queue<MazeCell, vector<MazeCell>, CompareAstar> frontier;
    MazeCell* curr = &start;
    MazeCell** map =maze.cells;
    while(!reach){
        pair<int,int> cur_location= curr->location;
        if(cur_location.first < maze._width-1){
            pair<int,int> t1(cur_location.first+1,cur_location.second); //east
            MazeCell east=map[t1.second][t1.first];
            if (east._element!='%' && east.visited == false){
                east.Manhattan = _Manhattan(east, goal);
                east.cost = curr->cost +1;
                east.parent = &maze.cells[cur_location.second][cur_location.first];
                east._f = east.Manhattan + east.cost;
                frontier.push(east);
            }



        }
        if(cur_location.first>0){
            pair<int,int> t2(cur_location.first-1,cur_location.second); //west
            MazeCell west=map[t2.second][t2.first];
            if (west._element!='%'&& west.visited == false){
                west.Manhattan = _Manhattan(west, goal);
                west.cost = curr->cost +1;
                west.parent = &maze.cells[cur_location.second][cur_location.first];
                west._f = west.Manhattan + west.cost;
                frontier.push(west);
            }
        }
        if(cur_location.second < maze._height-1){
            pair<int,int> t3(cur_location.first,cur_location.second+1); //north
            MazeCell north=map[t3.second][t3.first];
            if (north._element!='%' && north.visited == false){
                north.Manhattan = _Manhattan(north, goal);
                north.cost = curr->cost +1;
                north.parent = &maze.cells[cur_location.second][cur_location.first];
                north._f = north.Manhattan + north.cost;
                frontier.push(north);
            }

        }
        if(cur_location.second>0){
            pair<int,int> t4(cur_location.first,cur_location.second-1); //sourth
            MazeCell sourth=map[t4.second][t4.first];
            if (sourth._element!='%' && sourth.visited == false){
                sourth.Manhattan = _Manhattan(sourth, goal);
                sourth.cost = curr->cost +1;
                sourth.parent = &maze.cells[cur_location.second][cur_location.first];
                sourth._f = sourth.Manhattan + sourth.cost;
                frontier.push(sourth);
            }
        }
        MazeCell next=frontier.top();
        while(maze.cells[next.location.second][next.location.first].visited == true){
            frontier.pop();
            next = frontier.top();
        }
        next.visited = true;
        maze.cells[next.location.second][next.location.first] = next;
        frontier.pop();
        expand++;
        if(next.location.first==goal.location.first &&next.location.second==goal.location.second)
            reach=true;
        curr=&next;
    }
    path=trace(maze,cost);

}

void print_result (MyMaze &maze, int &cost, int &expand){
    for(int a=0; a<maze._height; a++){
        for(int b=0; b<maze._width; b++){
            cout<<maze.cells[a][b]._element;
        }
        cout<<endl;
    }

    cout<<"solution cost: "<<cost<<endl;
    cout<<"number of expanded nodes: "<<expand<<endl;
}


int main(){
    MyMaze* maze = new MyMaze;
    maze->createMaze();
    vector<std::pair<int, int>> path;
    int cost = 0;
    int expand=0;
    Astar(*maze,cost,path,expand);
    print_result(*maze,cost,expand);
    delete maze;
    return 0;
}
