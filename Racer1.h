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

const int SN = 5; //Sleep number

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
        }
        else if (runNum == 2) {
            followPath(Dijkstras(), g);
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

    /*bool recTraverse(pointR currP, DIRECTION d, SDL_Plotter& g){
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
    }*/

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

        // Check North
        if (look(NORTH,g) != 0 && currP.y > 0) {
            currP.N = true;
            if (!graph[currP.y-1][currP.x].v) {
                newP = currP;
                newP.y--;
                move(NORTH);
                recTraverse(newP, NORTH, g);
                draw(g);
                g.update();
                g.Sleep(SN);
            }
        }

        // Check South
        if (look(SOUTH,g) != 0 && currP.y < 19) {
            currP.S = true;
            if (!graph[currP.y+1][currP.x].v) {
                newP = currP;
                newP.y++;
                move(SOUTH);
                recTraverse(newP, SOUTH, g);
                draw(g);
                g.update();
                g.Sleep(SN);
            }
        }

        // Check West
        if (look(WEST,g) != 0 && currP.x > 0) {
            currP.W = true;
            if (!graph[currP.y][currP.x-1].v) {
                newP = currP;
                newP.x--;
                move(WEST);
                recTraverse(newP, WEST, g);
                draw(g);
                g.update();
                g.Sleep(SN);
            }
        }

        // Check East
        if (look(EAST,g) != 0 && currP.x < 34) {
            currP.E = true;
            if (!graph[currP.y][currP.x+1].v) {
                newP = currP;
                newP.x++;
                move(EAST);
                recTraverse(newP, EAST, g);
                draw(g);
                g.update();
                g.Sleep(SN);
            }
        }

        graph[currP.y][currP.x] = currP;


        // Backtrack
        if (d == NORTH && look(SOUTH, g) != 0) {
            move(SOUTH);
        }
        else if (d == SOUTH && look(NORTH, g) != 0) {
            move(NORTH);
        }
        else if (d == EAST && look(WEST, g) != 0) {
            move(WEST);
        }
        else if (d == WEST && look(EAST, g) != 0) {
            move(EAST);
        }

        draw(g);
        g.update();
        g.Sleep(SN);

        return false;
    }

    /*queue<DIRECTION> Dijkstras() {
        const size_t INF = 100000; //Default node shortest path
        int ny = 0;
        int nx = 0; //new y, and new x

        queue<DIRECTION> path; //Returned value

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

            if (graph[y][x].N && y > 0) { //Go North
                ny = y-1;
                nx = x;

                if  (graph[ny][nx].shortestPath == INF) {
                    graph[ny][nx].shortestPath = graph[y][x].shortestPath + 1;
                    graph[ny][nx].pred = &graph[y][x];
                    q.push(make_pair(y,x));
                }
            }

            if (graph[y][x].S && y < 19) { //Go South
                ny = y+1;
                nx = x;

                if (graph[ny][nx].shortestPath == INF) {
                    graph[ny][nx].shortestPath = graph[y][x].shortestPath + 1;
                    graph[ny][nx].pred = &graph[y][x];
                    q.push(make_pair(y,x));
                }
            }

            if (graph[y][x].W && x > 0) { //Go West
                ny = y;
                nx = x-1;

                if (graph[ny][nx].shortestPath == INF) {
                    graph[ny][nx].shortestPath = graph[y][x].shortestPath + 1;
                    graph[ny][nx].pred = &graph[y][x];
                    q.push(make_pair(y,x));
                }
            }

            if (graph[y][x].E && x < 34) { //Look East
                ny = y;
                nx = x+1;

                if (graph[ny][nx].shortestPath == INF) {
                    graph[ny][nx].shortestPath = graph[y][x].shortestPath + 1;
                    graph[ny][nx].pred = &graph[y][x];
                    q.push(make_pair(y,x));
                }
            }


            stack<DIRECTION> temp;
            pointR* currP = &graph[19][34];
            pointR* p;

            int dx, dy;
            DIRECTION dir;
            while(currP->pred != nullptr) {
                p = currP->pred;

                dx = currP->y - p->y; //Take coordinate diffs for direction
                dy = currP->x - p->x;

                if (dy == -1) dir = NORTH;
                else if (dy == 1) dir = SOUTH;
                else if (dx == -1) dir = WEST;
                else if (dx == 1) dir = EAST;

                temp.push(dir);
                currP = p;

            }

            while(!temp.empty()) {
                path.push(temp.top());
                temp.pop();
            }

            return path;
        }
    }*/

    queue<DIRECTION> Dijkstras() {
        const size_t INF = 100000;

        // Reset all nodes
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 35; ++j) {
                graph[i][j].shortestPath = INF;
                graph[i][j].pred = nullptr;
            }
        }
        graph[0][0].shortestPath = 0;

        queue<pair<int, int>> q;
        q.push(make_pair(0,0));

        while (!q.empty()) {
            auto front = q.front();
            q.pop();
            int y = front.first;   // row
            int x = front.second;  // col

            // North
            if (graph[y][x].N && y > 0) {
                int ny = y - 1;
                int nx = x;
                if (graph[ny][nx].shortestPath == INF) {
                    graph[ny][nx].shortestPath = graph[y][x].shortestPath + 1;
                    graph[ny][nx].pred = &graph[y][x];
                    q.push(make_pair(ny,nx));
                }
            }

            // South
            if (graph[y][x].S && y < 19) {
                int ny = y + 1;
                int nx = x;
                if (graph[ny][nx].shortestPath == INF) {
                    graph[ny][nx].shortestPath = graph[y][x].shortestPath + 1;
                    graph[ny][nx].pred = &graph[y][x];
                    q.push(make_pair(ny,nx));
                }
            }

            // West
            if (graph[y][x].W && x > 0) {
                int ny = y;
                int nx = x - 1;
                if (graph[ny][nx].shortestPath == INF) {
                    graph[ny][nx].shortestPath = graph[y][x].shortestPath + 1;
                    graph[ny][nx].pred = &graph[y][x];
                    q.push(make_pair(ny,nx));
                }
            }

            // East
            if (graph[y][x].E && x < 34) {
                int ny = y;
                int nx = x + 1;
                if (graph[ny][nx].shortestPath == INF) {
                    graph[ny][nx].shortestPath = graph[y][x].shortestPath + 1;
                    graph[ny][nx].pred = &graph[y][x];
                    q.push(make_pair(ny,nx));
                }
            }
        }


    // Reconstruct path
    stack<DIRECTION> temp;
    pointR* currP = &graph[19][34];
    while (currP->pred != nullptr) {
        pointR* p = currP->pred;
        int dy = currP->y - p->y;  // vertical diff (+1 = south)
        int dx = currP->x - p->x;  // horizontal diff (+1 = east)
        DIRECTION dir;
        if (dy == -1) {
            dir = NORTH;
        } else if (dy == 1) {
            dir = SOUTH;
        } else if (dx == -1) {
            dir = WEST;
        } else if (dx == 1) {
            dir = EAST;
        }
        temp.push(dir);
        currP = p;
    }

    queue<DIRECTION> path;
    temp.push(EAST); //Needed to start out right
    while (!temp.empty()) {
        path.push(temp.top());
        temp.pop();
    }

    return path;
}

    void followPath(queue<DIRECTION> path, SDL_Plotter& g){
        cout << path.empty() << endl;

        while(!path.empty()){
            if (path.front() == NORTH) cout << "NORTH" << endl;
                    if (path.front() == SOUTH) cout << "SOUTH" << endl;

                                if (path.front() == EAST) cout << "EAST" << endl;

                                            if (path.front() == WEST) cout << "WEST" << endl;

            move(path.front());
            path.pop();
            draw(g);
            g.update();
            g.Sleep(500);
        }
    }


};


#endif // RACER1_H_
