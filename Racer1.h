#ifndef RACER1_H_
#define RACER1_H_

#include "Racer.h"
#include <queue>
#include <stack>
#include <utility>

using namespace std;

struct edge;

struct pointR{
    int x = 0;
    int y = 0;
    vector<edge> e;
    bool v = false;
    bool path = false;
    bool start = false;
    bool finish = false;
    bool d = false;
    bool N = false;
    bool S = false;
    bool E = false;
    bool W = false;
    bool wall = false;

    //Dijkstras
    size_t shortestPath = 100000; //Arbitrarily large number for this
    pointR* pred;
};

struct edge{
    vector<DIRECTION> path;
    pointR a();
    pointR b();
};

static int runNum = 0;

const int SN = 10; //Sleep number

struct edge;
struct pointR;

static pointR graph[20][35];

class Racer1 : public Racer{
private:
    static queue<DIRECTION> q;

    struct Compare{
        bool operator()(pair<int,int> a, pair<int,int> b){
            return a.second > b.second;
        }
    };
public:

    Racer1(){
        runNum++;
    }

    bool legalMove(Uint32 u){return u != 0;}

    void run(SDL_Plotter& g){
        cout << runNum << endl;
        if(runNum == 1){
                    cout << "Starting Build Graph phase" << endl;

            buildG(g);

                    cout << "Ending Build Graph phase and returning results" << endl;



            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 35; j++) {
                    cout << graph[i][j].v << " ";
                }
                cout << endl;
            }

            cout << endl;
            cout << "wall:" << endl;
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 35; j++) {
                    if(graph[i][j].wall){
                        cout << "W ";
                    }else{
                        cout << graph[i][j].v << " ";
                    }
                }
                cout << endl;
            }
        }
    }

    void buildG(SDL_Plotter& g){
        runNum++;

        pointR currP;
        pointR finP;

        currP.start = true;
        currP.v = true;
        //currP.path = true;//Path should be mainly at the end
        currP.x = 0; currP.y = 0;

        //finP.path = true;//Path should be mainly at the end
        finP.finish = true;

        graph[0][0] = currP;
        graph[19][34] = finP;

        graph[0][0].shortestPath = 0;

        traverse(currP, g);
    }

    void traverse(pointR start, SDL_Plotter& g){

        recTraverse(start, EAST, g);
        //recTraverse(start, DIRECTION.SOUTH, g);
    }

    bool recTraverse(pointR currP, DIRECTION d, SDL_Plotter& g){
        pointR newP;
        draw(g);
        g.update();
        graph[currP.y][currP.x].v = true;


        int count = 0;
        bool flag = false;

        if(look(NORTH, g) != 0){count++;}
        if(look(SOUTH, g) != 0){count++;}
        if(look(EAST, g) != 0){count++;}
        if(look(WEST, g) != 0){count++;}

        if(count > 1){
            currP.d = true;
        }



        g.Sleep(SN);

        //Check North
        //cout << "Look NORTH: " << look(NORTH,g) << endl;
        if (look(NORTH,g) != 0 && currP.y > 0 && !graph[currP.y-1][currP.x].v) {

            newP = currP;
            newP.y--;
            move(NORTH);

            recTraverse(newP, NORTH, g);
            currP.N = true;

            draw(g);
            g.update();
            g.Sleep(SN);
        }



        //Check South
        //cout << "Look SOUTH: " << look(SOUTH,g) << endl;
        if (look(SOUTH,g) != 0 && currP.y < 20 && !graph[currP.y+1][currP.x].v) {
            newP = currP;
            newP.y++;
            move(SOUTH);

            recTraverse(newP, SOUTH, g);
            currP.S = true;

            draw(g);
            g.update();
            g.Sleep(SN);
        }



        //Check West
        //cout << "Look WEST: " << look(WEST,g) << endl;
        if (look(WEST,g) != 0 && currP.x > 0 && !graph[currP.y][currP.x-1].v) {
            newP = currP;
            newP.x--;
            move(WEST);

            recTraverse(newP, WEST, g);
            currP.W = true;

            draw(g);
            g.update();
            g.Sleep(SN);
        }


        //Check East
        //cout << "Look EAST: " << look(EAST,g) << endl;
        if (look(EAST,g) != 0 && currP.x < 35 && !graph[currP.y][currP.x+1].v) {
            newP = currP;
            newP.x++;
            move(EAST);

            recTraverse(newP, EAST, g);
            currP.E = true;

            draw(g);
            g.update();
            g.Sleep(SN);
        }

        graph[currP.y][currP.x] = currP;



        //If you reach this point you hit a dead end
        //Make racer move backwards
        graph[currP.y][currP.x].wall = true;
        if (d == NORTH && look(SOUTH, g) != 0) {
            move(SOUTH);
        }
        else if (d == SOUTH && look(NORTH, g) != 0) {
            move(NORTH);
        }
        else if (d == EAST && look(WEST, g) != 0) {
            move (WEST);
        }
        else if (d == WEST && look(EAST, g) != 0) {
            move (EAST);
        }


        draw(g);
        g.update();
        g.Sleep(SN);


        return false;
    }

    queue<DIRECTION> Dijkstras() {
        const size_t INF = 100000;

        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 35; ++j) {
                graph[i][j].shortestPath = INF;
                graph[i][j].pred = nullptr;
            }
        }

        graph[0][0].shortestPath = 0;

        queue<pair<int,int>> q;

        q.push(make_pair(0,0));

        while (!q.empty()) {
            int x, y;
            x = q.front().first;
            y = q.front().second;

            q.pop();

            if (graph[x][y].N && y > 0) {

            }
        }
    }

    /*queue<DIRECTION> Dijkstras() {
        //Start at source node
        pointR currP = graph[0][0];

        //Check Up if up is true
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 35; j++){
                currP = graph[i][j];

                if (currP.N) {
                    if (graph[currP.y-1][currP.x].shortestPath > currP.shortestPath+1) {
                        graph[currP.y-1][currP.x].shortestPath = currP.shortestPath+1;
                        graph[currP.y-1][currP.x].pred = &currP;
                        //graph[currP.y-1][currP.x].y
                    }
                }

                //Check down if it true
                if (currP.S) {
                    if (graph[currP.y+1][currP.x].shortestPath > currP.shortestPath+1) {
                        graph[currP.y+1][currP.x].shortestPath = currP.shortestPath+1;
                        graph[currP.y+1][currP.x].pred = &currP;
                    }
                }


                //Check left if it is true
                if (currP.E) {
                    if (graph[currP.y][currP.x+1].shortestPath > currP.shortestPath+1) {
                        graph[currP.y][currP.x+1].shortestPath = currP.shortestPath+1;
                        graph[currP.y][currP.x+1].pred = &currP;
                    }
                }

                //Check right if it is true
                if (currP.W) {
                    if (graph[currP.y][currP.x-1].shortestPath > currP.shortestPath+1) {
                        graph[currP.y][currP.x-1].shortestPath = currP.shortestPath+1;
                        graph[currP.y][currP.x-1].pred = &currP;
                    }
                }
            }
        }

        currP = graph[19][34];
        queue<DIRECTION> path;
        /*
        while (!currP.start) {
            //Make direction
            //if (currP.y < )


            currP = currP.pred;
        }
    }*/

    /*queue<DIRECTION> Djikstras(vector<vector<pair<int,DIRECTION>>> data,int s,int endpoint){
        const int INF = pow(2,31)-1;
        stack<int> backtrack;
        queue<DIRECTION> path;
        vector<int> D;
        vector<int> P;
        int u,v,pos;
        priority_queue<pair<int,int>,vector<pair<int,int>>,Compare> Q;

        D.resize(data.size());
        D[s] = 0;
        P.resize(data.size());
        P[s] = -1;

        for(size_t i = 0; i < data.size(); i++){
            if(static_cast<int>(i) != s){
                D[i] = INF;
            }
        }

        for(size_t i = 0; i < data.size(); i++){
            Q.push(make_pair(i,D[i]));
        }

        while(!Q.empty()){
            u = Q.top().first;
            Q.pop();

            for(size_t i = 0; i < data[u].size(); i++){
                if(data[u][i].first != 0){
                    if(D[u]+data[u][i].first < D[i]){
                        D[i] = D[u]+data[u][i].first;
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

        while(!backtrack.empty()){
            backtrack.pop();
            v = backtrack.top();

            path.push(data[u][v].second);

            u = v;
        }

        return path;
    }*/

    void followPath(queue<DIRECTION> path){
        move(path.front());
        path.pop();
    }
};


#endif // RACER1_H_
