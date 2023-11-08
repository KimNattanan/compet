#include "function.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
#define f first
#define s second

int n,m;
ll qs[1005],qs2[1005],dist[1005][25];
vector<pair<int,ll>> adj[1005];

ll cost(int l,int r){
    return ((qs[r]-qs[l-1])*(qs[r]-qs[l-1])+qs2[r]-qs2[l-1])>>1;
}
struct AA{
    int u,k;
    ll w;
    AA(int u_=0,ll w_=0,int k_=0):u(u_),w(w_),k(k_){}
    bool operator<(const AA&o)const{
        return w>o.w;
    }
};

long long minPenguinValue(int N, int M, std::vector<int> A){
    n=N,m=M;
    for(int i=1;i<=n;++i) qs[i]=qs[i-1]+A[i-1],qs2[i]=qs2[i-1]+1LL*A[i-1]*A[i-1];
    for(int i=1;i<=n;++i){
        for(int j=i;j<=n;++j){
            adj[i-1].eb(j,cost(i,j));
        }
    }
    priority_queue<AA> pq;
    pq.emplace(0,0,0);
    memset(dist,0x3f,sizeof dist);
    dist[0][0]=0;
    while(!pq.empty()){
        int u=pq.top().u;
        ll w=pq.top().w;
        int k=pq.top().k;
        pq.pop();
        if(u==n) return w;
        if(k==M||dist[u][k]<w) continue;
        for(auto &vw:adj[u]){
            if(dist[vw.f][k+1]>w+vw.s){
                dist[vw.f][k+1]=w+vw.s;
                pq.emplace(vw.f,w+vw.s,k+1);
            }
        }
    }
    return 0ll;
}
