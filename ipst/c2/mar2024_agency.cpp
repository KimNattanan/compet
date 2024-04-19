#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define eb emplace_back
using ll=long long;

int u0,v0,w0,p[200005][20],lv[200005];
vector<pii> adj[200005];
ll d[200005],qs[200005],cost[200005];
vector<ll> comp;

struct segment{
    struct node{
        node *l,*r;
        int cnt;
        ll sum;
        node():cnt(0),sum(0),l(nullptr),r(nullptr){}
    };
    using pnode=node*;
    vector<pnode> rt;
    int l0,r0;
    void init(int n,int l,int r){
        rt.resize(n);
        l0=l, r0=r;
        build(rt[0],l,r);
    }
    void build(pnode &t,int il,int ir){
        t=new node();
        if(il==ir) return;
        int im=il+ir>>1;
        build(t->l,il,im), build(t->r,im+1,ir);
    }
    void upd(pnode t0,pnode &t1,int il,int ir,int id){
        t1=new node(*t0);
        if(il==ir){
            ++(t1->cnt);
            t1->sum+=comp[id];
            return;
        }
        int im=il+ir>>1;
        if(id<=im) upd(t0->l,t1->l,il,im,id);
        else upd(t0->r,t1->r,im+1,ir,id);
        t1->cnt=(t1->l->cnt)+(t1->r->cnt);
        t1->sum=(t1->l->sum)+(t1->r->sum);
    }
    void upd(int t0,int t1,int id){upd(rt[t0],rt[t1],l0,r0,id);}
    ll qr(pnode t0,pnode t1,int il,int ir,int cnt){
        if(il==ir) return cnt*comp[il];
        int im=il+ir>>1;
        int cntL=t1->l->cnt-t0->l->cnt;
        if(cntL>cnt) return qr(t0->l,t1->l,il,im,cnt);
        ll ret=t1->l->sum-t0->l->sum;
        if(cnt!=cntL) ret+=qr(t0->r,t1->r,im+1,ir,cnt-cntL);
        return ret;
    }
    ll qr(int t0,int t1,int cnt){return qr(rt[t0],rt[t1],l0,r0,cnt);}
}t;

void dfs(int u,int p){
    ::p[u][0]=p;
    for(int i=1;i<20;++i) ::p[u][i]=::p[::p[u][i-1]][i-1];
    for(auto &[v,w]:adj[u]){
        if(v==p) continue;
        d[v]=d[u]+w;
        lv[v]=lv[u]+1;
        dfs(v,u);
    }
}
int LCA(int u,int v){
    if(lv[u]>lv[v]) swap(u,v);
    for(int i=19;i>=0;--i){
        if(lv[p[v][i]]>=lv[u]) v=p[v][i];
    }
    if(u==v) return u;
    for(int i=19;i>=0;--i){
        if(p[u][i]!=p[v][i]) u=p[u][i], v=p[v][i];
    }
    return p[u][0];
}
ll dist(int u,int v){
    return d[u]+d[v]-(d[LCA(u,v)]<<1);
}

void init(int N,std::vector<int> T,
                std::vector<std::vector<int>> Road) {
    for(int i=0;i<N-1;++i) adj[Road[i][0]].eb(Road[i][1],Road[i][2]), adj[Road[i][1]].eb(Road[i][0],Road[i][2]);
    u0=Road[N-1][0], v0=Road[N-1][1], w0=Road[N-1][2];
    dfs(0,0);
    for(int i=1;i<T.size();++i){
        ll val=dist(T[i-1],T[i]);
        cost[i]=-val+w0+min(dist(u0,T[i-1])+dist(v0,T[i]),dist(v0,T[i-1])+dist(u0,T[i]));
        qs[i]=qs[i-1]+val;
        comp.eb(cost[i]);
    }
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());
    t.init(T.size()+5,0,comp.size());
    for(int i=1;i<T.size();++i){
        cost[i]=lower_bound(comp.begin(),comp.end(),cost[i])-comp.begin();
        t.upd(i-1,i,cost[i]);
    }
}
long long min_distance(int L,int R,int X) {
    return qs[R]-qs[L]+t.qr(L,R,X);
}
