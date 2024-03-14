#include <bits/stdc++.h>
using namespace std;
#include "resource.h"
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second
using ll=long long;

vector<pii> adj[100005];
int op[100005],ed[100005],id0,V[100005],a[100005],comp[100005];

struct segment{
    struct node{
        ll sum;
        int sz;
        node *l,*r;
        node():sum(0),sz(0),l(nullptr),r(nullptr){}
        node(ll val):sum(val),sz(1),l(nullptr),r(nullptr){}
    };
    using pnode=node*;
    vector<pnode> rt;
    int tl0,tr0;
    void build(pnode &t,int tl,int tr){
        t=new node();
        if(tl==tr) return;
        int tm=tl+tr>>1;
        build(t->l,tl,tm), build(t->r,tm+1,tr);
    }
    void build(int n,int l,int r){
        rt.resize(n);
        tl0=l,tr0=r;
        build(rt[0],l,r);
    }

    void upd(pnode t1,pnode &t2,int tl,int tr,int u){
        t2=new node(*t1);
        t2->sum+=a[u];
        ++t2->sz;
        if(tl==tr) return;
        int tm=tl+tr>>1;
        if(comp[u]<=tm) upd(t1->l,t2->l,tl,tm,u);
        else upd(t1->r,t2->r,tm+1,tr,u);
    }
    void upd(int t1,int t2,int u){upd(rt[t1],rt[t2],tl0,tr0,u);}

    ll qr1(pnode t1,pnode t2,int tl,int tr,int k){
        if(tl==tr) return k==1? t2->sum-t1->sum : 0LL;
        int tm=tl+tr>>1;
        int szL=t2->l->sz - t1->l->sz;
        if(szL>=k) return qr1(t1->l,t2->l,tl,tm,k);
        return t2->l->sum - t1->l->sum + qr1(t1->r,t2->r,tm+1,tr,k-szL);
    }
    ll qr1(int t1,int t2,int k){return qr1(rt[t1],rt[t2],tl0,tr0,k);}

    ll qr2(pnode t1,pnode t2,pnode t3,int tl,int tr,int k){
        if(tl==tr) return k==1? t3->sum-t2->sum+t1->sum : 0LL;
        int tm=tl+tr>>1;
        int szL=t3->l->sz - t2->l->sz + t1->l->sz;
        if(szL>=k) return qr2(t1->l,t2->l,t3->l,tl,tm,k);
        return t3->l->sum - t2->l->sum + t1->l->sum + qr2(t1->r,t2->r,t3->r,tm+1,tr,k-szL);
    }
    ll qr2(int t1,int t2,int t3,int k){return qr2(rt[t1],rt[t2],rt[t3],tl0,tr0,k);}

}t;

void dfs(int u,int p){
    op[u]=ed[u]=++id0;
    // upd(id0-1,id0,u);
    t.upd(id0-1,id0,u);
    for(auto &[v,id]:adj[u]){
        if(v==p) continue;
        V[id]=v;
        dfs(v,u);
        ed[u]=ed[v];
    }
}

void init_resource(int N, int Q, std::vector<int> A, std::vector<int> U, std::vector<int> V, int G) {
    // edit this
    for(int i=0;i<N-1;++i) adj[U[i]].eb(V[i],i), adj[V[i]].eb(U[i],i);
    for(int i=0;i<N;++i) a[i]=A[i];
    vector<int> vec(N);
    iota(vec.begin(),vec.end(),0);
    sort(vec.begin(),vec.end(),[&](const int &l,const int &r){
        return A[l]>A[r];
    });
    for(int i=0;i<N;++i) comp[vec[i]]=i+1;
    t.build(N+5,1,N);
    dfs(0,0);
    return;
}

long long need_help(int X, int C, int K){
    int p0=V[X];
    if(op[p0]<=op[C]&&op[C]<=ed[p0]) return t.qr1(op[p0]-1,ed[p0],K); // qr1(op[p0]-1,ed[p0],K);
    return t.qr2(op[p0]-1,ed[p0],ed[0],K); // qr2(op[p0]-1,ed[p0],ed[0],K);
}
/*

5 3 1
2 6 3 7 4
0 1
0 2
1 3
1 4
0 2 2
2 1 1
0 4 2

*/
