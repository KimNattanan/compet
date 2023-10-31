#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

vector<pair<int,ll>> adj[50005];
vector<ll> A;
int X[50005];
priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
ll dist[50005],dp[50005];
void dijk(){
    while(pq.size()){
        int u=pq.top().s;
        ll w=pq.top().f;
        pq.pop();
        if(w>dist[u]) continue;
        for(auto &vw:adj[u]){
            if(dist[vw.f]>w+vw.s){
                dist[vw.f]=w+vw.s;
                pq.push({w+vw.s,vw.f});
            }
        }
    }
}
struct fw{
    vector<ll> bit;
    int n;
    void build(int n_){
        n=n_;
        bit.resize(n);
        for(int i=0;i<n;++i) bit[i]=1e18;
    }
    void upd(int i,ll val){
        for(;i<n;i+=i&-i) bit[i]=min(bit[i],val);
    }
    ll query(int i){
        ll ans=1e18;
        for(;i>0;i-=i&-i) ans=min(ans,bit[i]);
        return ans;
    }
}f0,f1;

long long minimum_energy(int N, int M, int K, std::vector<int> A_, std::vector<int> L,
                         std::vector<int> R, std::vector<int> C){
    vector<ll> vec;
    A.resize(N+5);
    for(int i=1;i<=N;++i){
        A[i]=A_[i-1];
        adj[i-1].pb({i,A[i]});
        adj[i].pb({i-1,A[i]});
        vec.pb(A[i]);
    }
    sort(vec.begin(),vec.end());
    vec.resize(unique(vec.begin(),vec.end())-vec.begin());
    for(int i=1;i<=N;++i) X[i]=lower_bound(vec.begin(),vec.end(),A[i])-vec.begin()+1;
    int n=vec.size();
    for(int i=0;i<M;++i){
        ++L[i],++R[i];
        adj[L[i]-1].pb({R[i],C[i]});
        adj[R[i]].pb({L[i]-1,C[i]});
    }
    memset(dist,0x3f,sizeof dist);
    dist[0]=0;
    pq.push({0,0});
    dijk();
    for(int i=0;i<K;++i){
        for(int j=1;j<=N;++j) dp[j]=1e18;
        f0.build(n+5),f1.build(n+5);
        f0.upd(X[1],-(A[1]*A[1]));
        f1.upd(n-X[1]+1,A[1]*A[1]);
        for(int j=1;j<=N;++j){
            ll x=f0.query(X[j]),y=f1.query(n-X[j]+1);
            if(j<N){
                f0.upd(X[j+1],dist[j]-A[j+1]*A[j+1]);
                f1.upd(n-X[j+1]+1,dist[j]+A[j+1]*A[j+1]);
            }
            dp[j]=min(x+A[j]*A[j],y-A[j]*A[j]);
        }
        f0.build(n+5),f1.build(n+5);
        for(int j=N-1;j>=1;--j){
            ll x=f0.query(X[j+1]),y=f1.query(n-X[j+1]+1);
            f0.upd(X[j],dist[j]-A[j]*A[j]);
            f1.upd(n-X[j]+1,dist[j]+A[j]*A[j]);
            dp[j]=min({dp[j],x+A[j+1]*A[j+1],y-A[j+1]*A[j+1]});
        }
        for(int j=1;j<=N;++j){
            if(dp[j]<dist[j]){
                dist[j]=dp[j];
                pq.push({dist[j],j});
            }
        }
        dijk();
    }
    return dist[N];
}
