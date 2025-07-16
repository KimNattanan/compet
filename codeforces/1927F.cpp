#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back

using t3=tuple<int,int,int>;

struct dsu{
    vector<int> p;
    void init(int n){
        p.assign(n,0);
        iota(p.begin(),p.end(),0);
    }
    int fSet(int u){return p[u]==u?u:(p[u]=fSet(p[u]));}
    bool uSet(int u,int v){
        int U=fSet(u),V=fSet(v);
        if(U==V) return 0;
        p[U]=V;
        return 1;
    }
}s;

vector<int> adj[200005],temp;
bitset<200005> vis;
bool dfs(int u,int p,int u0){
    if(u==u0) return 1;
    temp.eb(u);
    vis[u]=1;
    for(auto &v:adj[u]){
        if(v!=p&&!vis[v]&&dfs(v,u,u0)) return 1;
    }
    temp.pop_back();
    return 0;
}

void solve(){
    int n,m; cin>>n>>m;
    vector<t3> vec(m);
    for(int i=1;i<=n;++i){
        adj[i].clear();
        vis[i]=0;
    }
    for(auto &[w,u,v]:vec){
        cin>>u>>v>>w;
        adj[u].eb(v),adj[v].eb(u);
    }
    sort(vec.begin(),vec.end(),greater<t3>());
    s.init(n+5);
    int S,T,b;
    for(auto &[w,u,v]:vec){
        if(s.uSet(u,v)) continue;
        S=u,T=v,b=w;
    }
    temp.clear();
    temp.eb(S);
    dfs(T,S,S);
    cout<<b<<" "<<temp.size()<<endl;
    for(auto &e:temp) cout<<e<<" ";
    cout<<endl;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q(1);
    cin>>Q;
    while(Q--){
        solve();
    }
}
