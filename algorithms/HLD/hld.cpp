#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back



vector<int> adj[100005];
int sz[100005],heavy[100005],p0[100005];
int tour[100005],idx,head[100005];

struct A{ // segment tree on tour[]
    vector<A> child;
    int l,r,mid,sz;
    bool call; int lazy;
    int sum;
    A(int l_=0,int r_=0,int sum_=0){
        l=l_,r=r_,mid=l+(r-l>>1),sz=r-l+1;
        call=lazy=0;
        sum=sum_;
    }
    void flush(){
        if(l!=r&&child.empty()){
            child.emplace_back(l,mid);
            child.emplace_back(mid+1,r);
        }
        if(call){
            if(l!=r){
                child[0].call=child[1].call=1;
                child[0].lazy+=lazy;
                child[1].lazy+=lazy;
            }
            sum+=lazy*sz;
            call=lazy=0;
        }
    }
    void upd(int l0,int r0,int x){
        flush();
        if(l0<=l&&r<=r0){
            lazy+=x;
            call=1;
            flush();
            return;
        }
        if(l>r0||r<l0) return;
        child[0].upd(l0,r0,x);
        child[1].upd(l0,r0,x);
        sum=child[0].sum+child[1].sum;
    }
    int query(int l0,int r0){
        flush();
        if(l0<=l&&r<=r0) return sum;
        if(l>r0||r<l0) return 0;
        return child[0].query(l0,r0)+child[1].query(l0,r0);
    }
}tree;

void dfs0(int u,int p){
    p0[u]=p;
    sz[u]=1;
    heavy[u]=-1;
    for(auto &v:adj[u]){
        if(v!=p){
            dfs0(v,u);
            sz[u]+=sz[v];
            if(heavy[u]==-1||sz[heavy[u]]<sz[v]) heavy[u]=v;
        }
    }
}
void decomp(int u,int p){
    tour[u]=++idx;
    head[u]=p;
    if(heavy[u]!=-1) decomp(heavy[u],p);
    for(auto &v:adj[u]){
        if(v!=p0[u]&&v!=heavy[u]) decomp(v,v);
    }
}
void hld_upd(int u,int v,int x){
    while(head[u]!=head[v]){
        if(tour[head[u]]>tour[head[v]]) swap(u,v);
        tree.upd(tour[head[v]],tour[v],x);
        v=p0[head[v]];
    }
    if(tour[u]>tour[v]) swap(u,v);
    tree.upd(tour[u],tour[v],x);
}
int hld_query(int u,int v){
    int sum=0;
    while(head[u]!=head[v]){
        if(tour[head[u]]>tour[head[v]]) swap(u,v);
        sum+=tree.query(tour[head[v]],tour[v]);
        v=p0[head[v]];
    }
    if(tour[u]>tour[v]) swap(u,v);
    return sum+tree.query(tour[u],tour[v]);
}



int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    for(int i=0;i<n-1;++i){
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs0(1,1);
    decomp(1,1);
    tree=A(1,idx);
    while(Q--){
        char c; cin>>c;
        int u,v; cin>>u>>v;
        if(c=='P') hld_upd(u,v,1);
        else if(c=='Q') cout << hld_query(u,v) << endl;
    }

    return 0;
}
