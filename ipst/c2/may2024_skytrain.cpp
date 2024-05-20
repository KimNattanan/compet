#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define eb emplace_back
#include "skytrain.h"

using A=pair<ll,int>;

vector<pii> adj[100005];
ll cost[200005], d[100005];
priority_queue<A,vector<A>,greater<A>> pq;

void dijk(){
    while(!pq.empty()){
        auto [w,u]=pq.top(); pq.pop();
        if(d[u]!=w) continue;
        for(auto &[v,vw]:adj[u]){
            if(d[v]>w+cost[vw]) d[v]=w+cost[vw], pq.emplace(d[v],v);
        }
    }
}

long long min_total_cost(int N, int M, std::vector<int> U, std::vector<int> V, std::vector<int> W, long long K, int X, int Y) {
    for(int i=0;i<M;++i) adj[U[i]].eb(V[i],i), adj[V[i]].eb(U[i],i);

    int ans=(1<<30)-1;
    for(int i=1<<29;i>0;i>>=1){
        ans^=i;
        for(int j=0;j<M;++j){
            cost[j]=W[j];
            bool ok=1;
            for(int k=1<<29;k>0;k>>=1){
                if(ans&k || !(W[j]&k)) continue;
                cost[j]=min(cost[j], ll(  (W[j]&(k-1))+1+((~ans)&(k-1))  ) );
                int l=k<<1;
                while(W[j]&l) l<<=1;
                if(ans&l) cost[j]=min(cost[j],1+ ll(  (~W[j])&((k<<1)-1)  ) );
                ok=0;
                break;
            }
            if(ok) cost[j]=0;
        }
        for(int i=0;i<N;++i) d[i]=1e18;
        d[X]=0, pq.emplace(0,X), dijk();
        if(d[Y]>K) ans^=i;
    }
    return ans;

}
