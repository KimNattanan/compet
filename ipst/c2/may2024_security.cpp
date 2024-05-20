#include "security.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

vector<int> adj[800005],order,convex;
int N,deg[800005];
struct cmp{
    bool operator()(const pii &l,const pii &r)const{
        return l.f>r.f;
    }
};
priority_queue<pii,vector<pii>,cmp> pq;

int orient(int x1,int x2,int x3){
    ll m1=1LL*(order[x2]-order[x1])*(x3-x2);
    ll m2=1LL*(order[x3]-order[x2])*(x2-x1);
    if(m1<m2) return -1;
    if(m1==m2) return 0;
    return 1;
}

void kingdom(int N, int M, int Q, std::vector<int> U, std::vector<int> V,
             std::vector<int> s) {
    // implementation...
    ::N=N;
    for(int i=0;i<M;++i) adj[U[i]].eb(V[i]), adj[V[i]].eb(U[i]), ++deg[U[i]], ++deg[V[i]];
    for(int i=0;i<N;++i) if(deg[i]<=1) pq.emplace(s[i],i);
    while(!pq.empty()){
        auto [w,u]=pq.top(); pq.pop();
        order.eb(w);
        for(auto &v:adj[u]){
            if(--deg[v]==1) pq.emplace(s[v],v);
        }
    }
    if(order.size()!=N||N==2) return;

    convex.eb(0), convex.eb(1);
    for(int i=2;i<N;++i){
        while(convex.size()>1 && orient(convex.end()[-2],convex.back(),i) < 1) convex.pop_back();
        convex.eb(i);
    }

}

long long answer_query(int a) {
    // implementation...
    if(order.size()!=N) return -1;
    if(N==2) return max({0LL,(ll)order[0]-a,order[1]-1LL*a*2});

    int l=0,r=convex.size()-1;
    while(l<r){
        int mid=l+r>>1;
        if( (order[convex[mid+1]]-order[convex[mid]]) <= 1LL*a*(convex[mid+1]-convex[mid]) ) r=mid;
        else l=mid+1;
    }
    return max(0LL,order[convex[l]]-a-1LL*a*convex[l]);

}
