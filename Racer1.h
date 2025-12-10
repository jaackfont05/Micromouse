//Team 1
//Authors
//Jack Fontenot
//Andrei Kuvshinikov
//Brandon Vowell
//Connor Griffin
//Diego Diaz

#ifndef RACER1_H_
#define RACER1_H_

#include "Racer.h"
#include "constants.h"
#include <queue>
#include <stack>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

//custom comparator for Djikstra's
struct Compare{
    bool operator()(pair<int,int> a, pair<int,int> b){
        return a.second > b.second;
    }
};

//data structure for a point
struct pointR{
    //visited marker
    bool v = false;

    //direction markers
    bool E = false;
    bool N = false;
    bool W = false;
    bool S = false;

    //direction of predecessor
    DIRECTION p;

    //character for displaying the type of point (wall, vertex, edge)
    char c = '*';

    //name of point (int)
    int name = -1;
};

//static arrays of pointRs to hold the maze info
static pointR graph[row*2+1][col*2+1];
static pointR graph1[row*2+1][col*2+1];

//used for position in first traversal
static int rowG = 1;
static int colG = 1;

//used for position in second traversal
static int rowG1 = 1;
static int colG1 = 1;

//used to determine which run
static int runNum = 1;

//data structures used for holding the graph after traversal 1 and 2
static vector<vector<pair<int,DIRECTION>>> adjMatrix;
static vector<vector<pair<int,DIRECTION>>> adjMatrix1;

//used to hold directions of shortest path to finish point
static queue<DIRECTION> path1;
static queue<DIRECTION> path2;

//used to mark when the graph should be built
static bool build = true;

class Racer1 : public Racer{
private:

    //checks what is in that direction
    //returns true if point in the direction is white
    //return false if point in the direction is a wall
    bool check(DIRECTION d, SDL_Plotter& g){
        return look(d, g) != 0;
    }

    //first traversal of graph (DFS)
    void traverse1(SDL_Plotter& g){



        //check east
        if(check(EAST, g) && graph[rowG][colG+2].c != 'v'){
            move(EAST);
            graph[rowG][colG].E = true;
            colG++;
            //mark adjacent point as edge
            graph[rowG][colG].c = 'e';
            colG++;
            //mark next point as a vertex
            graph[rowG][colG].c = 'v';
            graph[rowG][colG].p = WEST;
            return;
        }else if(!check(EAST, g)){
            graph[rowG][colG+1].c = 'w';
        }

        //check south
        if(check(SOUTH, g)  && graph[rowG+2][colG].c != 'v'){
            move(SOUTH);
            graph[rowG][colG].S = true;
            rowG++;
            //mark adjacent point as edge
            graph[rowG][colG].c = 'e';
            rowG++;
            //mark next point as a vertex
            graph[rowG][colG].c = 'v';
            graph[rowG][colG].p = NORTH;
            return;
        }else if(!check(SOUTH, g)){
            graph[rowG+1][colG].c = 'w';
        }

        //check west
        if(check(WEST, g) && graph[rowG][colG-2].c != 'v'){
            move(WEST);
            graph[rowG][colG].W = true;
            colG--;
            //mark adjacent point as edge
            graph[rowG][colG].c = 'e';
            colG--;
            //mark next point as a vertex
            graph[rowG][colG].c = 'v';
            graph[rowG][colG].p = EAST;
            return;
        }else if(!check(WEST, g)){
            graph[rowG][colG-1].c = 'w';
        }

        //check north
        if(check(NORTH, g) && graph[rowG-2][colG].c != 'v'){
            move(NORTH);
            graph[rowG][colG].N = true;
            rowG--;
            //mark adjacent point as edge
            graph[rowG][colG].c = 'e';
            rowG--;
            //mark next point as a vertex
            graph[rowG][colG].c = 'v';
            graph[rowG][colG].p = SOUTH;
            return;
        }else if(!check(NORTH, g)){
            graph[rowG-1][colG].c = 'w';
        }

        //backtrack in direction of predecessor
        move(graph[rowG][colG].p);
        if(graph[rowG][colG].p == WEST){
            colG -= 2;
        }else if(graph[rowG][colG].p == EAST){
            colG += 2;
        }else if(graph[rowG][colG].p == NORTH){
            rowG -= 2;
        }else if(graph[rowG][colG].p == SOUTH){
            rowG += 2;
        }

    }

    //second traversal of graph (DFS)
    void traverse2(SDL_Plotter& g){


        //check south
        if(check(SOUTH, g) && graph1[rowG1+2][colG1].c != 'v'){
            move(SOUTH);
            graph1[rowG1][colG1].S = true;
            rowG1++;
            //mark adjacent point as edge
            graph1[rowG1][colG1].c = 'e';
            rowG1++;
            //mark next point as a vertex
            graph1[rowG1][colG1].c = 'v';
            graph1[rowG1][colG1].p = NORTH;
            return;
        }else if(!check(SOUTH, g)){
            graph1[rowG1+1][colG1].c = 'w';
        }

        //check east
        if(check(EAST, g) && graph1[rowG1][colG1+2].c != 'v'){
            move(EAST);
            graph1[rowG1][colG1].E = true;
            colG1++;
            //mark adjacent point as edge
            graph1[rowG1][colG1].c = 'e';
            colG1++;
            //mark next point as a vertex
            graph1[rowG1][colG1].c = 'v';
            graph1[rowG1][colG1].p = WEST;
            return;
        }else if(!check(EAST, g)){
            graph1[rowG1][colG1+1].c = 'w';
        }

        //check west
        if(check(WEST, g) && graph1[rowG1][colG1-2].c != 'v'){
            move(WEST);
            graph1[rowG1][colG1].W = true;
            colG1--;
            //mark adjacent point as edge
            graph1[rowG1][colG1].c = 'e';
            colG1--;
            //mark next point as a vertex
            graph1[rowG1][colG1].c = 'v';
            graph1[rowG1][colG1].p = EAST;
            return;
        }else if(!check(WEST, g)){
            graph1[rowG1][colG1-1].c = 'w';
        }

        //check north
        if(check(NORTH, g) && graph1[rowG1-2][colG1].c != 'v'){
            move(NORTH);
            graph1[rowG1][colG1].N = true;
            rowG1--;
            //mark adjacent point as edge
            graph1[rowG1][colG1].c = 'e';
            rowG1--;
            //mark next point as a vertex
            graph1[rowG1][colG1].c = 'v';
            graph1[rowG1][colG1].p = SOUTH;
            return;
        }else if(!check(NORTH, g)){
            graph1[rowG1-1][colG1].c = 'w';
        }

        //backtrack in direction of predecessor
        move(graph1[rowG1][colG1].p);
        if(graph1[rowG1][colG1].p == WEST){
            colG1 -= 2;
        }else if(graph1[rowG1][colG1].p == EAST){
            colG1 += 2;
        }else if(graph1[rowG1][colG1].p == NORTH){
            rowG1 -= 2;
        }else if(graph1[rowG1][colG1].p == SOUTH){
            rowG1 += 2;
        }

    }
public:
    //determines what phase the mouse is currently in
    void run(SDL_Plotter& g){

        //first traversal
        if(runNum == 1 && graph[row*2-1][col*2-1].c != 'v'){
            graph[1][1].c = 'v';
            if(graph[row*2-1][col*2-1].c != 'v'){
                traverse1(g);
            }
            //enters this if at finish point
            if(graph[row*2-1][col*2-1].c == 'v'){
                runNum++;
            }
        }

        //second traversal
        if(runNum == 2 && graph1[row*2-1][col*2-1].c != 'v'){
            graph1[1][1].c = 'v';
            if(graph1[row*2-1][col*2-1].c != 'v'){
                traverse2(g);
            }
            //enters if at finish point
            if(graph1[row*2-1][col*2-1].c == 'v'){
                runNum++;
                //builds graphs and runs Djikstras
                if(build){
                    buildAdjMatrix();
                    buildAdjMatrix1();
                    path1 = Djikstras1(0,adjMatrix.size()-1);
                    path2 = Djikstras2(0,adjMatrix1.size()-1);
                    build = false;
                }
            }
        }

        //last traversal (follows shortest path)
        if(runNum == 3 && graph[row*2-1][col*2-1].c == 'v' && graph1[row*2-1][col*2-1].c == 'v'){
            followPath();
        }


    }

    //prints out graphs for testing
    void print(){
        cout << endl;

        if(runNum == 1){
            for(int i = 0; i < row*2+1; ++i){
                for(int j = 0; j < col*2+1; ++j){
                    cout << graph[i][j].c << " ";
                }
                cout << endl;
            }
        }else if(runNum == 2){
            for(int i = 0; i < row*2+1; ++i){
                for(int j = 0; j < col*2+1; ++j){
                    cout << graph1[i][j].c << " ";
                }
                cout << endl;
            }
        }
    }

    //builds the adjacency matrix based off first traversal
    void buildAdjMatrix(){
        int countV = 0;

        for(int i = 0; i < row*2+1; i++){
            for(int j = 0; j < col*2+1; j++){
                if(graph[i][j].c == 'v'){
                    graph[i][j].name = countV;
                    countV++;
                }
            }
        }

        adjMatrix.resize(countV);

        for(int i = 0; i < adjMatrix.size(); i++){
            adjMatrix[i].resize(countV);
        }

        for(int i = 0; i < row*2+1; i++){
            for(int j = 0; j < col*2+1; j++){
                if(graph[i][j].c == 'e' && (i > 0 && i < row*2) && (j > 0 && j < col*2)){
                    if(graph[i][j-1].c == 'v' && graph[i][j+1].c == 'v'){
                        adjMatrix[graph[i][j-1].name][graph[i][j+1].name].first = 1;
                        adjMatrix[graph[i][j-1].name][graph[i][j+1].name].second = EAST;
                        adjMatrix[graph[i][j+1].name][graph[i][j-1].name].first = 1;
                        adjMatrix[graph[i][j+1].name][graph[i][j-1].name].second = WEST;
                    }
                    if(graph[i-1][j].c == 'v' && graph[i+1][j].c == 'v'){
                        adjMatrix[graph[i-1][j].name][graph[i+1][j].name].first = 1;
                        adjMatrix[graph[i-1][j].name][graph[i+1][j].name].second = SOUTH;
                        adjMatrix[graph[i+1][j].name][graph[i-1][j].name].first = 1;
                        adjMatrix[graph[i+1][j].name][graph[i-1][j].name].second = NORTH;
                    }
                }
            }
        }
    }

    //builds the adjacency matrix based off second traversal
    void buildAdjMatrix1(){
        int countV = 0;

        for(int i = 0; i < row*2+1; i++){
            for(int j = 0; j < col*2+1; j++){
                if(graph1[i][j].c == 'v'){
                    graph1[i][j].name = countV;
                    countV++;
                }
            }
        }

        adjMatrix1.resize(countV);

        for(int i = 0; i < adjMatrix1.size(); i++){
            adjMatrix1[i].resize(countV);
        }

        for(int i = 0; i < row*2+1; i++){
            for(int j = 0; j < col*2+1; j++){
                if(graph1[i][j].c == 'e' && (i > 0 && i < row*2) && (j > 0 && j < col*2)){
                    if(graph1[i][j-1].c == 'v' && graph1[i][j+1].c == 'v'){
                        adjMatrix1[graph1[i][j-1].name][graph1[i][j+1].name].first = 1;
                        adjMatrix1[graph1[i][j-1].name][graph1[i][j+1].name].second = EAST;
                        adjMatrix1[graph1[i][j+1].name][graph1[i][j-1].name].first = 1;
                        adjMatrix1[graph1[i][j+1].name][graph1[i][j-1].name].second = WEST;
                    }
                    if(graph1[i-1][j].c == 'v' && graph1[i+1][j].c == 'v'){
                        adjMatrix1[graph1[i-1][j].name][graph1[i+1][j].name].first = 1;
                        adjMatrix1[graph1[i-1][j].name][graph1[i+1][j].name].second = SOUTH;
                        adjMatrix1[graph1[i+1][j].name][graph1[i-1][j].name].first = 1;
                        adjMatrix1[graph1[i+1][j].name][graph1[i-1][j].name].second = NORTH;
                    }
                }
            }
        }
    }

    //finds shortest path from start to finish based off first traversal graph
    queue<DIRECTION> Djikstras1(int s,int endpoint){
        const int INF = pow(2,31)-1;
        stack<int> backtrack;
        queue<DIRECTION> path;
        vector<int> D;
        vector<int> P;
        int u,v,pos;
        priority_queue<pair<int,int>,vector<pair<int,int>>,Compare> Q;

        D.resize(adjMatrix.size());
        D[s] = 0;
        P.resize(adjMatrix.size());
        P[s] = -1;

        for(size_t i = 0; i < adjMatrix.size(); i++){
            if(static_cast<int>(i) != s){
                D[i] = INF;
            }
        }

        for(size_t i = 0; i < adjMatrix.size(); i++){
            Q.push(make_pair(i,D[i]));
        }

        while(!Q.empty()){
            u = Q.top().first;
            Q.pop();

            for(size_t i = 0; i < adjMatrix[u].size(); i++){
                if(adjMatrix[u][i].first != 0){
                    if(D[u]+adjMatrix[u][i].first < D[i]){
                        D[i] = D[u]+adjMatrix[u][i].first;
                        P[i] = u;
                        Q.push(make_pair(i,D[i]));
                    }
                }
            }
        }

        pos = endpoint;
        backtrack.push(endpoint);
        while(P[pos] != -1){
            backtrack.push(P[pos]);
            pos = P[pos];
        }

        u = backtrack.top();
        backtrack.pop();

        while(!backtrack.empty()){
            v = backtrack.top();
            backtrack.pop();

            path.push(adjMatrix[u][v].second);

            u = v;
        }

        return path;
    }

    //finds shortest path from start to finish based off second traversal graph
    queue<DIRECTION> Djikstras2(int s,int endpoint){
        const int INF = pow(2,31)-1;
        stack<int> backtrack;
        queue<DIRECTION> path;
        vector<int> D;
        vector<int> P;
        int u,v,pos;
        priority_queue<pair<int,int>,vector<pair<int,int>>,Compare> Q;

        D.resize(adjMatrix1.size());
        D[s] = 0;
        P.resize(adjMatrix1.size());
        P[s] = -1;

        for(size_t i = 0; i < adjMatrix1.size(); i++){
            if(static_cast<int>(i) != s){
                D[i] = INF;
            }
        }

        for(size_t i = 0; i < adjMatrix1.size(); i++){
            Q.push(make_pair(i,D[i]));
        }

        while(!Q.empty()){
            u = Q.top().first;
            Q.pop();

            for(size_t i = 0; i < adjMatrix1[u].size(); i++){
                if(adjMatrix1[u][i].first != 0){
                    if(D[u]+adjMatrix1[u][i].first < D[i]){
                        D[i] = D[u]+adjMatrix1[u][i].first;
                        P[i] = u;
                        Q.push(make_pair(i,D[i]));
                    }
                }
            }
        }

        pos = endpoint;
        backtrack.push(endpoint);
        while(P[pos] != -1){
            backtrack.push(P[pos]);
            pos = P[pos];
        }

        u = backtrack.top();
        backtrack.pop();

        while(!backtrack.empty()){
            v = backtrack.top();
            backtrack.pop();

            path.push(adjMatrix1[u][v].second);

            u = v;
        }

        return path;
    }

    //follows the shortest possible path
    void followPath(){
        if(path1.size() < path2.size()){
            move(path1.front());
            path1.pop();
        }
        else if(path1.size() > path2.size()){
            move(path2.front());
            path2.pop();
        }
        else{
            move(path1.front());
            path1.pop();
        }
    }

};


#endif // RACER1_H_
