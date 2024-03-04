#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back

vector<int> adj[100005],adj2[200005];
vector<int> node[100005];
int ap[100005],comp[100005],disc[100005],low[100005];
int id1,id2;
stack<int> st;

void tarj(int u,int p){
    disc[u]=low[u]=++id1;
    st.emplace(u);
    for(auto &v:adj[u]){
        if(v==p) continue;
        if(disc[v]) low[u]=min(low[u],disc[v]);
        else{
            tarj(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=disc[u]){
                if(disc[u]!=1||disc[v]!=2) ap[u]=1;
                node[++id2].eb(u);
                while(node[id2].back()!=v) node[id2].eb(st.top()),st.pop();
            }
        }
    }
}

int lvl[200005],pa[200005][20],tour[200005],ed[200005],id3;
void dfs(int u,int p){
    tour[u]=ed[u]=++id3;
    lvl[u]=lvl[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;++i) pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto &v:adj2[u]){
        if(v!=p) dfs(v,u),ed[u]=ed[v];
    }
}
int LCA(int u,int v){
    if(lvl[u]>lvl[v]) swap(u,v);
    for(int i=19;i>=0;--i){
        if(lvl[pa[v][i]]>=lvl[u]) v=pa[v][i];
    }
    if(u==v) return u;
    for(int i=19;i>=0;--i){
        if(pa[u][i]!=pa[v][i]) u=pa[u][i],v=pa[v][i];
    }
    return pa[u][0];
}
bool f(int u,int p){
    return tour[p]<=tour[u]&&tour[u]<=ed[p];
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,Q; cin>>n>>m>>Q;
    for(int i=0;i<m;++i){
        int u,v; cin>>u>>v;
        adj[u].eb(v),adj[v].eb(u);
    }
    
    tarj(1,1);
    id1=0;
    for(int i=1;i<=n;++i){
        if(ap[i]) ap[i]=++id1;
    }
    for(int i=1;i<=id2;++i){
        ++id1;
        for(auto &u:node[i]){
            if(ap[u]) comp[u]=ap[u], adj2[id1].eb(ap[u]), adj2[ap[u]].eb(id1);
            else comp[u]=id1;
        }
    }
    dfs(1,1);

    while(Q--){
        int u,v,x; cin>>u>>v>>x;
        if(u==x||v==x) cout<<"NO"<<endl;
        else if(!ap[x]) cout<<"YES"<<endl;
        else{
            u=comp[u],v=comp[v],x=comp[x];
            int p=LCA(u,v);
            if(f(x,p)&&f(u,x)|f(v,x)) cout<<"NO"<<endl;
            else cout<<"YES"<<endl;
        }
    }

    return 0;
}
