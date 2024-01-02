#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back

vector<int> adj[200005];
int a[200005],ans;
set<int> s[200005];

void dfs(int u,int p){
    s[u].insert(a[u]);
    bool ok=1;
    for(auto &v:adj[u]){
        if(v!=p){
            a[v]^=a[u];
            dfs(v,u);
        }
    }
    for(auto &v:adj[u]){
        if(v!=p){
            if(s[v].size()>s[u].size()) swap(s[u],s[v]);
            for(auto &e:s[v]){
                if(s[u].find(e^a[u]^a[p])!=s[u].end()){
                    ok=0;
                    break;
                }
            }
            for(auto &e:s[v]) s[u].insert(e);
            if(!ok) break;
        }
    }
    if(!ok){
        ++ans;
        s[u].clear();
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=0;i<n-1;++i){
        int u,v; cin>>u>>v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    dfs(1,0);
    cout<<ans;

    return 0;
}
