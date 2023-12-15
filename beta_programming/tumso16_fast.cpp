#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

#define int short

vector<int> adj[10005];
int disc[10005],low[10005],id0;
using A=pair<pii,pii>;
A ans;
bool cmp(const A &l,const A &r){
    if(l.f.f!=r.f.f) return l.f.f>r.f.f;
    if(l.f.s!=r.f.s) return l.f.s<r.f.s;
    return l.s<r.s;
}
int dfs(int u,int p){
    disc[u]=low[u]=++id0;
    int sz=1;
    for(auto &v:adj[u]){
        if(v==p) continue;
        if(!disc[v]){
            int sz2=dfs(v,u);
            low[u]=min(low[u],low[v]);
            sz+=sz2;
            if(low[v]>disc[u]){
                ans=min(ans,A(pii(sz2,u+v),pii(min(u,v),max(u,v))),cmp);
            }
        }
        else low[u]=min(low[u],disc[v]);
    }
    return sz;
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m; cin>>n>>m;
    for(int i=0;i<m;++i){
        int u,v; cin>>u>>v;
        adj[u].eb(v),adj[v].eb(u);
    }
    for(int i=1;i<=n;++i){
        if(!disc[i]) dfs(i,i);
    }
    if(ans.f.f==0) cout<<"OK!"<<endl;
    else cout<<ans.s.f<<" "<<ans.s.s<<endl;

    return 0;
}
