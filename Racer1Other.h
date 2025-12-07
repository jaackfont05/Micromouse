#ifndef RACER1_H_INCLUDED
#define RACER1_H_INCLUDED

#include "Racer.h"
#include "SDL_Plotter.h"
#include <stack>
#include <vector>
#include <utility>
#include <cmath>

static int runNum = 0;
static vector<vector<pair<int,DIRECTION>>> data;



class Racer1: public Racer{
private:
    int maze[20][35];

    struct Compare{
        bool operator()(pair<int,int> a, pair<int,int> b){
            return a.second > b.second;
        }
    };
public:

    run(SDL_Plotter& g){
        int r = 0, c = 0;
        if(runNum == 0){
            data.resize(700);
            for(int i = 0; i < 700; i++){
                data[i].resize(700);
            }
            for(int i = 0; i < 20; i++){
                for(int j = 0; j < 35; j++){
                    maze[i][j] = 0;
                }
            }
            maze[0][0] = 1;
            buildGraph(r,c,g);
        }
        else if(runNum == 1){
            //Djikstras();
        }
        else{
            //followPath();
        }
    }

    void buildGraph(int& r,int& c,SDL_Plotter& g, int prevR, int prevC){
        //cout << "HERE" << endl;
        g.Sleep(1000);
        draw(g);
        g.update();
        
        int count = 0;
        
        if(look(EAST, g) != 0){count++;}
        if(look(SOUTH, g) != 0){count++;}
        if(look(WEST, g) != 0){count++;}
        if(look(NORTH, g) != 0){count++;}
        
        if(count > 1){
            maze[r][c] = count;
        }
        
        if(look(EAST,g) != 0 && maze[r][c+1] != 1){
            maze[r][c+1] = 1;
            move(EAST);
            c++;
            return buildGraph(r,c,g);
        }
        else if(look(SOUTH,g) != 0 && maze[r+1][c] != 1){
            maze[r+1][c] = 1;
            move(SOUTH);
            r++;
            return buildGraph(r,c,g);
        }
        else if(look(WEST,g) != 0 && maze[r][c-1] != 1){
            maze[r][c-1] = 1;
            move(WEST);
            c--;
            return buildGraph(r,c,g);
        }
        else if(look(NORTH,g) != 0 && maze[r-1][c] != 1){
            maze[r-1][c] = 1;
            move(NORTH);
            r--;
            return buildGraph(r,c,g);
        }else{
            if(prevR > r){
                
            }
        }
        
        return;
    }

    queue<DIRECTION> Djikstras(int s,int endpoint){
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
    }

    void followPath(queue<DIRECTION> path){
        move(path.front());
        path.pop();
    }
};

#endif // RACER1_H_INCLUDED
