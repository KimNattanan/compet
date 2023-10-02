#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define ll long long

#define int ll

const int md=1e9+7;

struct A{
    int l,r,mid,cnt;
    int lazy; bool call;
    vector<A> adj;
    int sum;
    A(int l_=0,int r_=0,int sum_=0){
        l=l_,r=r_,mid=l+(r-l>>1),cnt=r-l+1;
        lazy=call=0;
        sum=sum_;
    }
    void flush(){
        if(l!=r&&adj.empty()){
            adj.emplace_back(l,mid,(mid-l+1)*(sum/cnt));
            adj.emplace_back(mid+1,r,(r-mid)*(sum/cnt));
        }
        if(call){

            if(l!=r){
                adj[0].lazy+=lazy;
                adj[1].lazy+=lazy;
                adj[0].call=adj[1].call=1;
            }
            sum+=cnt*lazy;

            lazy=call=0;
        }
    }
    void upd(int l0,int r0,int x){
        flush();
        if(l0>r||r0<l) return;
        if(l>=l0&&r<=r0){
            lazy=x;
            call=1;
            flush();
            return;
        }
        adj[0].upd(l0,r0,x);
        adj[1].upd(l0,r0,x);
        sum=adj[0].sum+adj[1].sum;
    }
    int query(int l0,int r0){
        flush();
        if(l0>r||r0<l) return 0;
        if(l>=l0&&r<=r0) return sum;
        return adj[0].query(l0,r0)+adj[1].query(l0,r0);
    }
};
vector<A> tree;
int group[100005];

vector<int> adj[100005];
int lvl[100005];
int pLCA[100005][18];
int heavy[100005],head[100005],tail[100005],idx[100005],temp;
int dfs(int u,int p,int d){
    lvl[u]=d;
    pLCA[u][0]=p;
    for(int i=1;i<18;++i) pLCA[u][i]=pLCA[pLCA[u][i-1]][i-1];
    int sz=1;
    int mx=heavy[u]=-1;
    for(auto &v:adj[u]){
        if(v!=p){
            int csz=dfs(v,u,d+1);
            if(csz>mx) mx=csz,heavy[u]=v;
            sz+=csz;
        }
    }
    return sz;
}
void decomp(int u,int h){
    head[u]=h;
    idx[u]=++temp;
    if(heavy[u]!=-1) decomp(heavy[u],h),tail[u]=tail[heavy[u]],group[u]=group[heavy[u]];
    else{
        tail[u]=u;
        group[u]=tree.size();
        tree.emplace_back(idx[head[u]],idx[tail[u]],0);
    }
    for(auto &v:adj[u]){
        if(v!=pLCA[u][0]&&v!=heavy[u]){
            decomp(v,v);
        }
    }
}
int LCA(int u,int v){
    if(lvl[v]>lvl[u]) swap(u,v);
    for(int i=17;i>=0;--i){
        if(lvl[pLCA[u][i]]>=lvl[v]) u=pLCA[u][i];
    }
    if(u==v) return v;
    for(int i=17;i>=0;--i){
        if(pLCA[v][i]==pLCA[u][i]) continue;
        v=pLCA[v][i],u=pLCA[u][i];
    }
    return pLCA[u][0];
}

void add(int u,int v,int lca,int x){

    while(group[u]!=group[lca]){
        tree[group[u]].upd(idx[head[u]],idx[u],x);
        u=pLCA[head[u]][0];
    }
    while(group[v]!=group[lca]){
        tree[group[v]].upd(idx[head[v]],idx[v],x);
        v=pLCA[head[v]][0];
    }
    if(u==lca) swap(u,v);
    if(u==lca) return;
    tree[group[lca]].upd(idx[lca]+1,idx[u],x);

}

int query(int u,int v,int lca){

    int ans=0;
    while(group[u]!=group[lca]){
        ans+=tree[group[u]].query(idx[head[u]],idx[u]);
        u=pLCA[head[u]][0];
    }
    while(group[v]!=group[lca]){
        ans+=tree[group[v]].query(idx[head[v]],idx[v]);
        v=pLCA[head[v]][0];
    }
    if(u==lca) swap(u,v);
    if(u==lca) return ans;
    ans+=tree[group[lca]].query(idx[lca]+1,idx[u]);

    return ans;

}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    for(int i=0;i<n-1;++i){
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,1,1);
    decomp(1,1);
    while(Q--){
        char c; cin>>c;
        int u,v; cin>>u>>v;
        int lca=LCA(u,v);
        if(c=='A'){
            add(u,v,lca,1);
        }
        else{
            cout<<query(u,v,lca)<<endl;
        }
    }

    return 0;
}
/**

4 18
4 3
4 1
2 4
A 3 2
A 1 3
B 1 2
B 2 1
B 1 3
B 3 1
B 1 4
B 4 1
B 2 3
B 3 2
B 2 4
B 4 2
B 3 4
B 4 3
B 1 1
B 2 2
B 3 3
B 4 4

2
2
3
3
1
1
3
3
1
1
2
2
0
0
0
0

*/
