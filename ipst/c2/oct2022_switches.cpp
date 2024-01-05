#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
#define f first
#define s second

ll a[50005],dist[50005],dp[50005];
vector<pair<int,ll>> adj[50005];
priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
vector<int> comp;
int id[50005];

struct fenwick{
    vector<ll> bit;
    void init(int n){bit=vector<ll>(n,1e18);}
    void upd(int i,ll x){
        for(;i<bit.size();i+=i&-i) bit[i]=min(bit[i],x);
    }
    ll qr(int i){
        ll ret=LLONG_MAX;
        for(;i>0;i-=i&-i) ret=min(ret,bit[i]);
        return ret;
    }
}fw1,fw2;

void dijk(){
    while(pq.size()){
        ll w=pq.top().f;
        int u=pq.top().s;
        pq.pop();
        if(dist[u]!=w) continue;
        for(auto &vw:adj[u]){
            if(dist[vw.f]>w+vw.s){
                dist[vw.f]=w+vw.s;
                pq.emplace(w+vw.s,vw.f);
            }
        }
    }
}

long long minimum_energy(int N, int M, int K, std::vector<int> A, std::vector<int> L, 
                         std::vector<int> R, std::vector<int> C){
    for(int i=1;i<=N;++i){
        a[i]=A[i-1];
        adj[i-1].eb(i,a[i]);
        adj[i].eb(i-1,a[i]);
        comp.eb(a[i]);
    }
    for(int i=0;i<M;++i){
        ++L[i],++R[i];
        adj[L[i]-1].eb(R[i],C[i]);
        adj[R[i]].eb(L[i]-1,C[i]);
    }

    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());
    for(int i=1;i<=N;++i) id[i]=lower_bound(comp.begin(),comp.end(),a[i])-comp.begin()+1;
    int sz=comp.size();

    memset(dist,0x3f,sizeof dist);
    pq.emplace(0,0);
    dist[0]=0;
    dijk();
    for(int k=1;k<=K;++k){
        fw1.init(sz+5),fw2.init(sz+5);
        for(int i=1;i<=N;++i){
            fw1.upd(id[i],dist[i-1]-a[i]*a[i]);
            fw2.upd(sz-id[i]+1,dist[i-1]+a[i]*a[i]);
            dp[i]=min(fw1.qr(id[i])+a[i]*a[i],fw2.qr(sz-id[i]+1)-a[i]*a[i]);
        }
        fw1.init(sz+5),fw2.init(sz+5);
        for(int i=N;i>=1;--i){
            if(i!=N) dp[i]=min({dp[i],fw1.qr(id[i+1])+a[i+1]*a[i+1],fw2.qr(sz-id[i+1]+1)-a[i+1]*a[i+1]});
            fw1.upd(id[i],dist[i]-a[i]*a[i]);
            fw2.upd(sz-id[i]+1,dist[i]+a[i]*a[i]);
        }
        for(int i=1;i<=N;++i){
            if(dp[i]<dist[i]){
                dist[i]=dp[i];
                pq.emplace(dist[i],i);
            }
        }
        dijk();
    }
    return dist[N];
}
