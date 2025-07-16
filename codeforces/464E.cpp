#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back
 
const int MX=100020;
const int md=1e9+7;
 
mt19937 rng(time(0));
int pw_hash[MX+5];
ll pw[MX+5];
 
struct segment{
    struct node{
        node *l,*r;
        int hsh;
        node(int hsh=0):hsh(hsh){}
    };
    using pnode=node*;
    vector<pnode> rt;
    int l0,r0,S;
    void build(pnode &t,int il,int ir,bool x){
        t=new node();
        if(il==ir) return void(t->hsh=(x?pw_hash[il]:0));
        int mid=il+ir>>1;
        build(t->l,il,mid,x), build(t->r,mid+1,ir,x);
        t->hsh=t->l->hsh+t->r->hsh;
    }
    void build(int n,int l,int r,int S_){
        l0=l,r0=r,S=S_;
        rt.resize(n+5);
        build(rt[S],l,r,0); //, build(rt.back(),l,r,1);
    }
    int find_0(pnode t,int il,int ir,int id){
        if(il==ir) return t->hsh==0 ? il : -1;
        int mid=il+ir>>1;
        if(id>mid) return find_0(t->r,mid+1,ir,id);
        int ret=-1;
        ret=find_0(t->l,il,mid,id);
        if(ret!=-1) return ret;
        return find_0(t->r,mid+1,ir,mid+1);
    }
    void upd(pnode tzero,pnode t0,pnode &t1,int il,int ir,int l,int r){
        if(l<=il&&ir<r) return void(t1=tzero);
        if(il>r||ir<l) return void(t1=t0);
        if(il==ir){
            if(l<=il&&il<r) t1=tzero;
            else if(il==r) t1=new node(pw_hash[il]);
            return;
        }
        t1=new node(*t0);
        int mid=il+ir>>1;
        if(l==mid+1 && r>ir) t1->r=tzero->r;
        else if(l<=mid && r>ir) t1->r=tzero->r, upd(tzero->l,t0->l,t1->l,il,mid,l,r);
        else if(l<=il&&r>mid) t1->l=tzero->l, upd(tzero->r,t0->r,t1->r,mid+1,ir,l,r);
        else upd(tzero->l,t0->l,t1->l,il,mid,l,r), upd(tzero->r,t0->r,t1->r,mid+1,ir,l,r);
        t1->hsh=t1->l->hsh+t1->r->hsh;
    }
    void upd(int v0,int v1,int id){ upd(rt[S],rt[v0],rt[v1],l0,r0,id,find_0(rt[v0],l0,r0,id)); }
    int cmp(pnode t0,pnode t1,int il,int ir){
        if(!t0&&!t1) return 0;
        if(!t0||!t1) return t0 ? -1 : 1;
        if(il==ir) return t0->hsh==0 ? -1 : 1;
        int mid=il+ir>>1;
        if(t0->r->hsh != t1->r->hsh) return cmp(t0->r,t1->r,mid+1,ir);
        if(t0->l->hsh != t1->l->hsh) return cmp(t0->l,t1->l,il,mid);
        return 0;
    }
    int cmp(int v0,int v1){return cmp(rt[v0],rt[v1],l0,r0);}
    int mint(pnode t,int il,int ir,int md){
        if(!t) return -1;
        if(il==ir) return t->hsh==0 ? 0 : pw[il];
        int mid=il+ir>>1;
        return (mint(t->l,il,mid,md)+mint(t->r,mid+1,ir,md))%md;
    }
    int mint(int v0,int md){return mint(rt[v0],l0,r0,md);}
}t;
 
vector<pii> adj[100005];
struct cmp{
    bool operator()(const int &l,const int &r){
        return t.cmp(l,r) == 1;
    }
};
priority_queue<int,vector<int>,cmp> pq;
int p[100005];
 
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
 
    for(int i=0;i<=MX;++i){
        while(!pw_hash[i]) pw_hash[i]=rng();
        pw[i]=(i==0?1:(pw[i-1]<<1)%md);
    }
 
    int n,m; cin>>n>>m;
    for(int i=0;i<m;++i){
        int u,v,w; cin>>u>>v>>w;
        adj[u].eb(v,w), adj[v].eb(u,w);
    }
    int S,T; cin>>S>>T;
    t.build(n,0,MX,S);
    pq.emplace(S);
    p[S]=-1;
    while(!pq.empty()){
        int u=pq.top(); pq.pop();
        if(u==T){
            cout<<t.mint(u,1e9+7)<<'\n';
            stack<int> st;
            st.emplace(u);
            while(st.top()!=S) st.emplace(p[st.top()]);
            cout<<st.size()<<'\n';
            while(!st.empty()) cout<<st.top()<<" ", st.pop();
            cout<<'\n';
            return 0;
        }
        for(auto &[v,w]:adj[u]){
            t.upd(u,0,w);
            if(t.cmp(0,v)==-1) t.upd(u,v,w), pq.emplace(v), p[v]=u;
        }
    }
    cout<<-1;
 
    return 0;
}
