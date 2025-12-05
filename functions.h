#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stack>
#include <vector>
#include <utility>
#include <cmath>

struct Compare{
    bool operator()(pair<int,int> a, pair<int,int> b){
        return a.second > b.second;
    }
};

queue<DIRECTION> Djikstras(vector<vector<pair<int,DIRECTION>> data,int s,int endpoint){
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
            if(data[u][i] != 0){
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
    move(path.top());
    path.pop();
}

#endif // FUNCTIONS_H_INCLUDED
