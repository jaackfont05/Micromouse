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

struct Compare{
    bool operator()(pair<int,int> a, pair<int,int> b){
        return a.second > b.second;
    }
};

struct pointR{
    bool v = false;
    bool E = false;
    bool N = false;
    bool W = false;
    bool S = false;
    DIRECTION p;
    char c = '*';
    int name = -1;
};

static pointR graph[row*2+1][col*2+1];
static pointR graph1[row*2+1][col*2+1];
static int rowG = 1;
static int colG = 1;
static int rowG1 = 1;
static int colG1 = 1;
static int runNum = 1;
static vector<vector<pair<int,DIRECTION>>> adjMatrix;
static vector<vector<pair<int,DIRECTION>>> adjMatrix1;
static queue<DIRECTION> path1;
static queue<DIRECTION> path2;
static bool build = true;

class Racer1 : public Racer{
private:

    bool check(DIRECTION d, SDL_Plotter& g){
        return look(d, g) != 0;
    }

    void traverse1(SDL_Plotter& g){



        //check east
        if(check(EAST, g) && graph[rowG][colG+2].c != 'v'){
            move(EAST);
            graph[rowG][colG].E = true;
            colG++;
            graph[rowG][colG].c = 'e';
            colG++;
            graph[rowG][colG].c='v';
            graph[rowG][colG].p=WEST;
            return;
        }else if(!check(EAST, g)){
            graph[rowG][colG+1].c = 'w';
        }

        //check south
        if(check(SOUTH, g)  && graph[rowG+2][colG].c != 'v'){
            move(SOUTH);
            graph[rowG][colG].S = true;
            rowG++;
            graph[rowG][colG].c = 'e';
            rowG++;
            graph[rowG][colG].c='v';
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
            graph[rowG][colG].c = 'e';
            colG--;
            graph[rowG][colG].c='v';
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
            graph[rowG][colG].c = 'e';
            rowG--;
            graph[rowG][colG].c='v';
            graph[rowG][colG].p = SOUTH;
            return;
        }else if(!check(NORTH, g)){
            graph[rowG-1][colG].c = 'w';
        }

        //backtrack

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

    void traverse2(SDL_Plotter& g){


        //check south
        if(check(SOUTH, g) && graph1[rowG1+2][colG1].c != 'v'){
            move(SOUTH);
            graph1[rowG1][colG1].S = true;
            rowG1++;
            graph1[rowG1][colG1].c = 'e';
            rowG1++;
            graph1[rowG1][colG1].c='v';
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
            graph1[rowG1][colG1].c = 'e';
            colG1++;
            graph1[rowG1][colG1].c='v';
            graph1[rowG1][colG1].p=WEST;
            return;
        }else if(!check(EAST, g)){
            graph1[rowG1][colG1+1].c = 'w';
        }

        //check west
        if(check(WEST, g) && graph1[rowG1][colG1-2].c != 'v'){
            move(WEST);
            graph1[rowG1][colG1].W = true;
            colG1--;
            graph1[rowG1][colG1].c = 'e';
            colG1--;
            graph1[rowG1][colG1].c='v';
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
            graph1[rowG1][colG1].c = 'e';
            rowG1--;
            graph1[rowG1][colG1].c='v';
            graph1[rowG1][colG1].p = SOUTH;
            return;
        }else if(!check(NORTH, g)){
            graph1[rowG1-1][colG1].c = 'w';
        }

        //backtrack

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
    void run(SDL_Plotter& g){

        if(runNum == 1 && graph[row*2][col*2].c != 'v'){
            if(colG >= col*2+1 || rowG >= row*2+1){
                cout << graph[row*2][col*2].c << endl;
                cout << "out of bounds" << endl;
                return;
            }
            graph[1][1].c = 'v';
            traverse1(g);
            if(graph[row*2][col*2].c == 'v'){
                runNum++;
                cout << " run: " << runNum << endl;
            }
        }

        if(runNum == 2 && graph1[row*2][col*2].c != 'v'){
            if(colG1 >= col*2+1 || rowG1 >= row*2+1){
                cout << "out of bounds" << endl;
                return;
            }
            graph1[1][1].c = 'v';
            traverse2(g);
            if(graph1[row*2][col*2].c == 'v'){
                runNum++;
                cout << " run2: " << runNum << endl;
                if(build){
                    cout << "build" << endl;
                    buildAdjMatrix();
                    buildAdjMatrix1();
                    path1 = Djikstras1(0,adjMatrix.size());
                    path2 = Djikstras2(0,adjMatrix1.size());
                    build = false;
                }
            }
        }

        if(runNum == 3 && graph[row*2][col*2].c == 'v' && graph1[row*2][col*2].c != 'v'){
            followPath();
        }


    }

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
                if(graph[i][j].c == 'e'){
                    if(graph[i][j-1].c == 'v' && graph[i][j+1].c == 'v'){
                        adjMatrix[graph[i][j-1].name][graph[i][j+1].name].first = 1;
                        adjMatrix[graph[i][j-1].name][graph[i][j+1].name].second = EAST;
                        adjMatrix[graph[i][j+1].name][graph[i][j-1].name].first = 1;
                        adjMatrix[graph[i][j+1].name][graph[i][j-1].name].second = WEST;
                    }
                    if(graph[i-1][j].c == 'v' && graph[i+1][j].c == 'v'){
                        adjMatrix[graph[i-1][j].name][graph[i+1][j].name].first = 1;
                        adjMatrix[graph[i-1][j].name][graph[i+1][j].name].second = SOUTH;
                        adjMatrix[graph[i+1][j].name][graph[i+1][j].name].first = 1;
                        adjMatrix[graph[i+1][j].name][graph[i+1][j].name].second = NORTH;
                    }
                }
            }
        }
    }

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
                if(graph1[i][j].c == 'e'){
                    if(graph1[i][j-1].c == 'v' && graph1[i][j+1].c == 'v'){
                        adjMatrix1[graph1[i][j-1].name][graph1[i][j+1].name].first = 1;
                        adjMatrix1[graph1[i][j-1].name][graph1[i][j+1].name].second = EAST;
                        adjMatrix1[graph1[i][j+1].name][graph1[i][j-1].name].first = 1;
                        adjMatrix1[graph1[i][j+1].name][graph1[i][j-1].name].second = WEST;
                    }
                    if(graph1[i-1][j].c == 'v' && graph1[i+1][j].c == 'v'){
                        adjMatrix1[graph1[i-1][j].name][graph1[i+1][j].name].first = 1;
                        adjMatrix1[graph1[i-1][j].name][graph1[i+1][j].name].second = SOUTH;
                        adjMatrix1[graph1[i+1][j].name][graph1[i+1][j].name].first = 1;
                        adjMatrix1[graph1[i+1][j].name][graph1[i+1][j].name].second = NORTH;
                    }
                }
            }
        }
    }

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

        while(!backtrack.empty()){
            backtrack.pop();
            v = backtrack.top();

            path.push(adjMatrix[u][v].second);

            u = v;
        }

        return path;
    }

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

        while(!backtrack.empty()){
            backtrack.pop();
            v = backtrack.top();

            path.push(adjMatrix1[u][v].second);

            u = v;
        }

        return path;
    }

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

/*

struct edge;

struct vert{
    pair<int, int> name;
    vert* pred;
    vector<edge*> edges;
    int d;
    char stat = 'U';
    vert(pair<int, int> name): name(name){}
};

struct edge{
    vert* s;
    vert* d;
    int w;

    edge(vert* s, vert* d, int w){
        this->s = s;
        this->d = d;
        this->w = w;
    }

    //gets the adjacent point to a
    vert* getO(vert* a){
        vert* res = s;

        if(a == s){
            res = d;
        }

        return res;
    }

    //checks if edge is outgoing from a
    bool isOut(vert* a){
        bool flag = true;

        if(a == d){
            flag = false;
        }

        return flag;
    }
};

struct comp{
    bool operator()(const vert* a, const vert* b){
        return a->d > b->d;
    }
};
    //Djikstra
    void djikstra1(vector<vector<point*>>& g, point* s){
        priority_queue<vert*, vector<vert*>, comp> q;
        vert* u = nullptr;
        edge* e = nullptr;
        vert* v = nullptr;
        vector<vert*> pop;

        for(size_t i = 0; i < g.size(); ++i){
            //set D[v] to infinity
            g.at(i)->d = 1000000;
        }

        //set source predecessor and D[s]
        s->d = 0;
        s->pred = new vert(make_pair(-1, -1));

        for(size_t i = 0; i < g.size(); ++i){
            //set priority q
            q.push(g.at(i).front());
        }

        while(!q.empty()){
            u = q.top();
            q.pop();
            //add it to popped list
            pop.push_back(u);
            for(size_t i = 0; i < u->edges.size(); ++i){
                e = u->edges.at(i);
                v = e->getO(u);

                if(!contains(pop, v)){
                    if(u->d + e->w < v->d){
                        v->d = u->d + e->w;
                        v->pred = u;

                        //for making sure the priority q reorders
                        q.push(s);
                        q.pop();

                    }
                }
            }
        }

    }

    void djikstra2(vector<vector<point*>>& g, point* s){
        priority_queue<vert*, vector<vert*>, comp> q;
        vert* u = nullptr;
        edge* e = nullptr;
        vert* v = nullptr;
        vector<vert*> pop;

        for(size_t i = 0; i < g.size(); ++i){
            //set D[v] to infinity
            g.at(i)->d = 1000000;
        }

        //set source predecessor and D[s]
        s->d = 0;
        s->pred = new vert(make_pair(-1, -1));

        for(size_t i = 0; i < g.size(); ++i){
            //set priority q
            q.push(g.at(i).front());
        }

        while(!q.empty()){
            u = q.top();
            q.pop();
            //add it to popped list
            pop.push_back(u);
            for(size_t i = 0; i < u->edges.size(); ++i){
                e = u->edges.at(i);
                v = e->getO(u);

                if(!contains(pop, v)){
                    if(u->d + e->w < v->d){
                        v->d = u->d + e->w;
                        v->pred = u;

                        //for making sure the priority q reorders
                        q.push(s);
                        q.pop();

                    }
                }
            }
        }

    }

    //build adj list
    void buildList(){
        int v1, v2;
        int x1, x2;
        vector<vert*> g;
        vector<edge*> edgeH;
        vector<pair<int, int>> nums;
        vert* p1 = nullptr;
        vert* p2 = nullptr;
        edge* e = nullptr;






        //m edges
        for(int i = 0; i < totalVs.size()-1; ++i){

            v1 = totalVs.at(i).first;
            v2 = totalVs.at(i).second;

            x1 = totalVs.at(i+1).first;
            x2 = totalVs.at(i+1).second;

            //first input
            if(i == 0){
                nums.push_back(make_pair(v1, v2));
                nums.push_back(make_pair(x1, x2));

                p1 = new point(v1);
                p2 = new point(v2);

                e = new edge(p1, p2, w);
                //edge holder for BF
                edgeH.push_back(e);
                p1->edges.push_back(e);

                g.at(v1).push_back(p1);
                g.at(v1).push_back(p2);

                g.at(v2).push_back(p2);

                //input 2+
            }else if(v1 != v2){
                if(!contains(nums, make_pair(v1, v2))){
                    p1 = new point(make_pair(v1, v2));
                    g.push_back(p1);
                }else{
                    p1 = find(g, make_pair(v1, v2));
                }

                if(!contains(nums, make_pair(x1, x2))){
                    p2 = new point(make_pair(x1, x2));
                    g.push_back(p2);
                }else{
                    p2 = find(g, make_pair(x1, x2));
                }

                e = new edge(p1, p2, 1);

                edgeH.push_back(e);
                p1->edges.push_back(e);
                p2->edges.push_back(e);
            }
        }
    }

    vert* find(vector<vert*> g, pair<int, int> f){
        vert* res = nullptr;

        for(int i = 0; i < g.size(); ++i){
            if(f.first == g.at(i)->name.first && f.second == g.at(i)->name.second){
                res = g.at(i);
            }
        }

        return vert;
    }

    bool contains(vector<pair<int, int>>& nums, pair<int, int> f){
        bool flag = false;

        for(int i = 0; i < nums.size(); ++i){
            if(f.first == nums.at(i).first && f.second == nums.at(i).second){
                flag = true;
            }
        }

        if(!flag){
            nums.push_back(f);
        }

        return flag;
    }

    bool contains(vector<vert*>& verts, vert* v){
        bool flag = false;

        for(int i = 0; i < verts.size(); ++i){
            if(verts.at(i) == v){
                flag = true;
            }
        }

        return flag;
    }
    */
};


#endif // RACER1_H_
