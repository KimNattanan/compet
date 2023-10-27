#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second

//#define int ll

const int inf=1e9+7;

int n,L;
map<pii,int> mp;
map<pair<pii,pii>,int> mp2;
int cnt;
int f0(pii x){
    if(mp[x]) return mp[x];
    if(x.f>=0&&x.f<L) return mp[x]=++cnt;
    return -1;
}
vector<pii> adj[400005];
int dist[400005];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n>>L;
    vector<pii> vec;
    for(int i=1;i<=n;++i){
        int a,b,c,d,w; cin>>a>>b>>c>>d>>w;
        mp2[{{a,b},{c,d}}]=w;
        mp2[{{c,d},{a,b}}]=w;
        vec.pb({a,b});
        vec.pb({c,d});
    }
    sort(vec.begin(),vec.end());
    vec.resize(unique(vec.begin(),vec.end())-vec.begin());
    int mn0=inf,mx0=-inf,mn1=inf,mx1=-inf;
    for(auto &e:vec){
        if(e.f>0&&e.f<L){
            int u,v,w;
            u=f0({e.f,e.s}),v=f0({e.f,e.s-1}),w=mp2[{{e.f,e.s},{e.f+1,e.s}}];
            adj[u].pb({v,w});
            adj[v].pb({u,w});
            u=f0({e.f-1,e.s}),v=f0({e.f-1,e.s-1}),w=mp2[{{e.f-1,e.s},{e.f,e.s}}];
            adj[u].pb({v,w});
            adj[v].pb({u,w});
            u=f0({e.f-1,e.s}),v=f0({e.f,e.s}),w=mp2[{{e.f,e.s},{e.f,e.s+1}}];
            adj[u].pb({v,w});
            adj[v].pb({u,w});
            u=f0({e.f-1,e.s-1}),v=f0({e.f,e.s-1}),w=mp2[{{e.f,e.s-1},{e.f,e.s}}];
            adj[u].pb({v,w});
            adj[v].pb({u,w});
        }
        else if(e.f==0){
            mn0=min(mn0,e.s);
            mx0=max(mx0,e.s);
        }
        else if(e.f==L){
            mn1=min(mn1,e.s);
            mx1=max(mx1,e.s);
        }
    }
    int U,V;
    for(int i=mn0;i<=mx0;++i){
        int u=f0({0,i}),v=f0({0,i-1}),w=mp2[{{0,i},{1,i}}];
        adj[u].pb({v,w});
        adj[v].pb({u,w});
        if(i==mn0) V=v;
        else if(i==mx0) U=u;
    }
    for(int i=mn1;i<=mx1;++i){
        int u=f0({L-1,i}),v=f0({L-1,i-1}),w=mp2[{{L-1,i},{L,i}}];
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,U});
    memset(dist,0x3f,sizeof dist);
    dist[U]=0;
    while(pq.size()){
        int w=pq.top().f;
        int u=pq.top().s;
        pq.pop();
        if(u==V){
            cout<<w;
            return 0;
        }
        for(auto &vw:adj[u]){
            if(dist[vw.f]>w+vw.s){
                dist[vw.f]=w+vw.s;
                pq.push({w+vw.s,vw.f});
            }
        }
    }

    return 0;
}
/**

*/
