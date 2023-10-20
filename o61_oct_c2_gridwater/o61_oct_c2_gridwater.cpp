#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back

const int inf=1e9+7;
const int md=1e9+7;

struct A{
    int u,v,w;
    bool operator<(const A&o)const{
        return w<o.w;
    }
};
vector<A> edge;

vector<pii> adj[200005];

int pa[200005];
int fSet(int u){
    if(pa[u]==u) return u;
    return pa[u]=fSet(pa[u]);
}
bool uSet(int u,int v){
    int U=fSet(u),V=fSet(v);
    if(U==V) return 0;
    pa[U]=V;
    return 1;
}

int lvl[200005];
pii P[200005][20];

void dfs(int u,int p,int w=0){
    P[u][0]={p,w};
    for(int i=1;i<20;++i){
        P[u][i]={P[P[u][i-1].f][i-1].f,max(P[u][i-1].s,P[P[u][i-1].f][i-1].s)};
    }
    for(auto &vw:adj[u]){
        if(vw.f!=p) lvl[vw.f]=lvl[u]+1,dfs(vw.f,u,vw.s);
    }
}

int lca_mx(int u,int v){
    if(lvl[u]>lvl[v]) swap(u,v);
    int ans=0;
    for(int i=19;i>=0;--i){
        if(lvl[P[v][i].f]>=lvl[u]) ans=max(ans,P[v][i].s),v=P[v][i].f;
    }
    if(u==v) return ans;
    for(int i=19;i>=0;--i){
        if(P[u][i].f!=P[v][i].f) ans=max({ans,P[u][i].s,P[v][i].s}),
                                 u=P[u][i].f,v=P[v][i].f;
    }
    return max({ans,P[u][0].s,P[v][0].s});
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int mi,mj; cin>>mi>>mj;
    for(int i=0;i<mi;++i){
        for(int j=0;j<mj-1;++j){
            int w; cin>>w;
            int u=i*mj+j,v=u+1;
            edge.pb({u,v,w});
        }
        if(i!=mi-1){
            for(int j=0;j<mj;++j){
                int w; cin>>w;
                int u=i*mj+j,v=u+mj;
                edge.pb({u,v,w});
            }
        }
    }
    sort(edge.begin(),edge.end());
    vector<A> edge2;
    for(int i=0;i<200000;++i) pa[i]=i;
    for(auto &e:edge){
        if(uSet(e.u,e.v)){
            adj[e.u].pb({e.v,e.w});
            adj[e.v].pb({e.u,e.w});
        }
        else edge2.pb(e);
    }
    dfs(0,0);
    int ans=INT_MAX;
    for(auto &e:edge2){
        ans=min(ans,e.w-lca_mx(e.u,e.v));
    }
    cout<<ans;

    return 0;
}
/**
 4 5
 1 80 7 200
 90 2 11 16 55
 3 8 30 100
 96 60 40 12 56
 20 50 10 300
 140 5 13 302 57
 70 4 15 301
*/
