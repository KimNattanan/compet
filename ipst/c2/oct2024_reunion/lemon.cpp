#include "reunion.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pli=pair<ll,int>;
#define f first
#define s second
#define eb emplace_back

const ll inf=1e18;

namespace lemon {

int target,n;

vector<pli> adj[2005];
ll d[2005][2005],pth[2005][2005];
priority_queue<pli,vector<pli>,greater<pli>> pq;

ll dijk(int u0){
    for(int i=0;i<n;++i) d[u0][i]=inf;
    d[u0][u0]=0;
    pth[u0][u0]=u0;
    pq.emplace(0,u0);
    while(!pq.empty()){
        auto [w,u]=pq.top(); pq.pop();
        if(d[u0][u]!=w) continue;
        for(auto &[v,vw]:adj[u]){
            if(d[u0][v]>w+vw){
                d[u0][v]=w+vw;
                pth[u0][v]=u;
                pq.emplace(d[u0][v],v);
            }
        }
    }
    for(int i=0;i<n;++i) d[u0][n]=max(d[u0][n],d[u0][i]);
    return d[u0][n];
}

void lemon_init(int N, int M, std::vector<int> U, std::vector<int> V,
               std::vector<int> W, int u) {
    for(int i=0;i<M;++i) adj[U[i]].eb(V[i],W[i]), adj[V[i]].eb(U[i],W[i]);
    n=N;
    pli mn(inf,-1);
    for(int i=0;i<N;++i) mn=min(mn,{dijk(i),i});
    target=mn.s;
}
int lemon_move(int u) {
    return pth[target][u];
}

} // namespace lemon
