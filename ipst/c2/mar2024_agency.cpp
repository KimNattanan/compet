#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
// using pll=pair<ll,ll>;
#define f first
#define s second
using ll=long long;
#define eb emplace_back

const ll inf=1e18;

vector<pair<int,ll>> adj[200005];
vector<int> T;
int u0,v0;
ll w0;

int lv[200005],p[200005][19],d3id[200005];
ll d[200005],d2[200005],d3[200005];

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    ::p[u][0]=p;
    for(int i=1;i<19;++i) ::p[u][i]=::p[::p[u][i-1]][i-1];
    for(auto &[v,w]:adj[u]){
        if(v==p) continue;
        d[v]=d[u]+w;
        dfs(v,u);
    }
}

int LCA(int u,int v){
    if(lv[u]>lv[v]) swap(u,v);
    for(int i=18;i>=0;--i){
        if(lv[p[v][i]]>=lv[u]) v=p[v][i];
    }
    if(u==v) return u;
    for(int i=18;i>=0;--i){
        if(p[u][i]==p[v][i]) continue;
        u=p[u][i], v=p[v][i];
    }
    return p[u][0];
}
ll cal(int v1,int v2){
    return d[v1]+d[v2]-2*d[LCA(v1,v2)];
}
ll cal(int v1,int v2,int v3,int v4){
    return cal(v1,v2)+cal(v3,v4)+w0;
}

struct segment{

    struct node{
        node *l,*r;
        int sz;
        ll sum;
        node():l(nullptr),r(nullptr),sz(0),sum(0){}
        node(int i):l(nullptr),r(nullptr),sz(1),sum(d3[i]){}
    };
    using pnode=node*;
    vector<pnode> rt;
    int l0,r0;
    void build(pnode &t,int l,int r){
        t=new node();
        if(l==r) return;
        int mid=l+r>>1;
        build(t->l,l,mid), build(t->r,mid+1,r);
    }
    void init(int n,int l,int r){
        rt.resize(n);
        l0=l,r0=r;
        build(rt[0],l,r);
    }
    void upd(pnode t1,pnode &t2,int l,int r,int id){
        t2=new node(*t1);
        if(l==r){
            t2->sum+=d3[id];
            ++t2->sz;
            return;
        }
        int mid=l+r>>1;
        if(d3id[id]<=mid) upd(t1->l,t2->l,l,mid,id);
        else upd(t1->r,t2->r,mid+1,r,id);
        t2->sum=t2->l->sum+t2->r->sum;
        t2->sz=t2->l->sz+t2->r->sz;
    }
    void upd(int v1,int v2,int id){
        upd(rt[v1],rt[v2],l0,r0,id);
    }
    ll qr(pnode t1,pnode t2,int l,int r,int k){
        if(l==r){
            if(k<t2->sz-t1->sz) return 0;
            return t2->sum-t1->sum;
        }
        int mid=l+r>>1;
        if(t2->l->sz-t1->l->sz>=k) return qr(t1->l,t2->l,l,mid,k);
        return t2->l->sum-t1->l->sum+qr(t1->r,t2->r,mid+1,r,k-t2->l->sz+t1->l->sz);
    }
    ll qr(int v1,int v2,int k){
        return qr(rt[v1],rt[v2],l0,r0,k);
    }

}t;

void init(int N,vector<int> T,vector<vector<int>> Road) {
    ::T=T;
    for(int i=0;i<N-1;++i){
        adj[Road[i][0]].eb(Road[i][1],Road[i][2]), adj[Road[i][1]].eb(Road[i][0],Road[i][2]);
    }
    u0=Road[N-1][0], v0=Road[N-1][1], w0=Road[N-1][2];
    dfs(0,0);

    vector<pair<ll,int>> comp;

    for(int i=1;i<T.size();++i){
        ll dist=cal(T[i-1],T[i]);
        d2[i]=dist+d2[i-1];
        d3[i]=-dist+min(cal(T[i-1],u0,v0,T[i]),cal(T[i-1],v0,u0,T[i]));
        comp.eb(d3[i],i);
    }
    sort(comp.begin(),comp.end());
    for(int i=0;i<comp.size();++i) d3id[comp[i].s]=i+1;

    t.init(T.size()+5,1,comp.size());
    for(int i=1;i<T.size();++i){
        t.upd(i-1,i,i);
    }
}
long long min_distance(int L,int R,int X) {
    if(X==0) return d2[R]-d2[L];
    return d2[R]-d2[L]+t.qr(L,R,X);    
}
