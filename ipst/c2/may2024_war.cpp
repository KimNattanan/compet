#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back
#include "war.h"

const ll inf=1e12;


struct segment{
    vector<ll> mn,lz;
    int l0,r0;
    void init(int n0,int l,int r){
        int n=(n0==0 ? 0 : 4<<31-__builtin_clz(n0));
        mn.assign(n,inf), lz.assign(n,0);
        l0=l, r0=r;
    }
    void flush(int i,int il,int ir){
        if(!lz[i]) return;
        if(il!=ir) lz[i<<1]+=lz[i], lz[i<<1|1]+=lz[i];
        mn[i]+=lz[i];
        lz[i]=0;
    }
    void upd1(int i,int il,int ir,int id,ll val){
        flush(i,il,ir);
        if(il==ir) return void(mn[i]+=val);
        int mid=il+ir>>1;
        if(id<=mid) upd1(i<<1,il,mid,id,val);
        else upd1(i<<1|1,mid+1,ir,id,val);
        flush(i<<1,il,mid), flush(i<<1|1,mid+1,ir);
        mn[i]=min(mn[i<<1],mn[i<<1|1]);
    }
    ll qr1(int i,int il,int ir,int id){
        flush(i,il,ir);
        if(il==ir) return mn[i];
        int mid=il+ir>>1;
        if(id<=mid) return qr1(i<<1,il,mid,id);
        return qr1(i<<1|1,mid+1,ir,id);
    }
    void upd2(int i,int il,int ir,int l,int r,ll val){
        flush(i,il,ir);
        if(l<=il&&ir<=r) return lz[i]+=val, flush(i,il,ir);
        if(il>r||ir<l) return;
        int mid=il+ir>>1;
        upd2(i<<1,il,mid,l,r,val), upd2(i<<1|1,mid+1,ir,l,r,val);
        mn[i]=min(mn[i<<1],mn[i<<1|1]);
    }
    ll qr2(int i,int il,int ir,int l,int r){
        flush(i,il,ir);
        if(l<=il&&ir<=r) return mn[i];
        if(il>r||ir<l) return 1e18;
        int mid=il+ir>>1;
        return min(qr2(i<<1,il,mid,l,r),qr2(i<<1|1,mid+1,ir,l,r));
    }
    void upd1(int id,ll val){upd1(1,l0,r0,id,val);}
    ll qr1(int id){return qr1(1,l0,r0,id);}
    void upd2(int l,int r,ll val){upd2(1,l0,r0,l,r,val);}
    ll qr2(int l,int r){return qr2(1,l0,r0,l,r);}
};



vector<int> adj[100005],U,V;
int cp[100005],lv[100005],sz[100005],id;
bitset<100005> vis,hos,road;
segment t[100005];
unordered_map<int,int> op[100005],ed[100005];



void dfs(int c,int u,int p){
    op[c][u]=ed[c][u]=++id;
    for(auto &v:adj[u]) if(v!=p&&!vis[v]) dfs(c,v,u), ed[c][u]=ed[c][v];
}
void dfs_sz(int u,int p){
    sz[u]=1;
    for(auto &v:adj[u]) if(!vis[v]&&v!=p) dfs_sz(v,u), sz[u]+=sz[v];
}
int centroid(int u,int p,int n){
    for(auto &v:adj[u]) if(v!=p&&!vis[v]&&sz[v]>n) return centroid(v,u,n);
    return u;
}
void decomp(int u,int p){
    dfs_sz(u,u);
    int c=centroid(u,u,sz[u]>>1);
    vis[c]=1;
    cp[c]=p;
    if(p!=-1) lv[c]=lv[p]+1;

    id=0;
    dfs(c,c,c);
    t[c].init(sz[u]+5,1,id);

    for(auto &v:adj[c]) if(!vis[v]) decomp(v,c);
}



void upd_edge(int c,int id,ll val){
    if(op[c][U[id]]>op[c][V[id]]) swap(U[id],V[id]);
    t[c].upd2(op[c][V[id]],ed[c][V[id]],val);
    if(cp[c]!=-1) upd_edge(cp[c],id,val);
}
void upd_hos(int c,int u){
    t[c].upd1(op[c][u],hos[u] ? -inf : inf);
    if(cp[c]!=-1) upd_hos(cp[c],u);
}
ll qr_hos(int c,int u){
    ll ret = -inf+t[c].qr1(op[c][u])+t[c].qr2(0,1e9);
    if(cp[c]!=-1) ret=min(ret,qr_hos(cp[c],u));
    return ret;
}



void init(int N, std::vector<int> U, std::vector<int> V, std::vector<int> W) {
    ::U=U, ::V=V;
    for(int i=0;i<N-1;++i) adj[U[i]].eb(V[i]), adj[V[i]].eb(U[i]);
    decomp(0,-1);
    for(int i=0;i<N-1;++i){
        if(lv[::U[i]]>lv[::V[i]]) swap(::U[i],::V[i]);
        upd_edge(::U[i],i,W[i]);
    }
    road.set();
}
void toggle_hospital(int x) {
    hos[x]=!hos[x];
    upd_hos(x,x);
}
void toggle_road(int x) {
    road[x]=!road[x];
    if(lv[U[x]]>lv[V[x]]) swap(U[x],V[x]);
    upd_edge(U[x],x, road[x] ? -inf : inf );
}
long long nearest_hospital(int x) {
    if(hos[x]) return 0LL;
    ll ret=qr_hos(x,x);
    return ret<inf ? ret : -1;
}
