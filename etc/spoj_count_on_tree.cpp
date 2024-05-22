#include<bits/stdc++.h>
using namespace std;

struct segment{
    struct node{
        node *l,*r;
        int cnt;
        node(int cnt=0):cnt(cnt){}
    };
    // using pnode=node*;
    #define pnode node*
    vector<pnode> rt;
    int l0,r0;
    void build(pnode &t,int il,int ir){
        t=new node();
        if(il==ir) return;
        int mid=il+ir>>1;
        build(t->l,il,mid), build(t->r,mid+1,ir);
    }
    void build(int n,int l,int r){
        l0=l,r0=r;
        rt.resize(n);
        build(rt[0],l,r);
    }
    void upd(pnode t0,pnode &t1,int il,int ir,int id){
        t1=new node(*t0);
        if(il==ir) return void(++(t1->cnt));
        int mid=il+ir>>1;
        if(id<=mid) upd(t0->l,t1->l,il,mid,id);
        else upd(t0->r,t1->r,mid+1,ir,id);
        t1->cnt=t1->l->cnt+t1->r->cnt;
    }
    void upd(int v0,int v1,int id){upd(rt[v0],rt[v1],l0,r0,id);}
    int cal(pnode t0,pnode pt0,pnode t1,pnode t2){ return t1->cnt+t2->cnt-t0->cnt-pt0->cnt; }
    int find(pnode t0,pnode pt0,pnode t1,pnode t2,int il,int ir,int k){
        if(il==ir) return il;
        int mid=il+ir>>1;
        int cntL=cal(t0->l,pt0->l,t1->l,t2->l);
        if(cntL>=k) return find(t0->l,pt0->l,t1->l,t2->l,il,mid,k);
        return find(t0->r,pt0->r,t1->r,t2->r,mid+1,ir,k-cntL);
    }
    int find(int v0,int pv0,int v1,int v2,int k){return find(rt[v0],rt[pv0],rt[v1],rt[v2],l0,r0,k);}
}t;

vector<int> comp,adj[100005];
int a[100005],p[100005][20],lv[100005];

void dfs(int u,int p){
    t.upd(p,u,a[u]);
    lv[u]=lv[p]+1;
    ::p[u][0]=p;
    for(int i=1;i<20;++i) ::p[u][i]=::p[::p[u][i-1]][i-1];
    for(int v=0;v<adj[u].size();++v){
        if(adj[u][v]!=p) dfs(adj[u][v],u);
    }
}
int LCA(int u,int v){
    if(lv[u]>lv[v]) swap(u,v);
    for(int i=19;i>=0;--i) if(lv[p[v][i]]>=lv[u]) v=p[v][i];
    if(u==v) return u;
    for(int i=19;i>=0;--i) if(p[u][i]!=p[v][i]) u=p[u][i], v=p[v][i];
    return p[u][0];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    for(int i=1;i<=n;++i) cin>>a[i],comp.push_back(a[i]);
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());
    for(int i=1;i<=n;++i) a[i]=lower_bound(comp.begin(),comp.end(),a[i])-comp.begin();
    for(int i=1;i<n;++i){
        int u,v; cin>>u>>v;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    t.build(n+5,0,comp.size());
    dfs(1,0);
    while(Q--){
        int u,v,k; cin>>u>>v>>k;
        int lca=LCA(u,v);
        cout<<comp[t.find(lca,p[lca][0],u,v,k)]<<'\n';
    }

    return 0;
}
