#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define f first
#define s second
#define eb emplace_back
#define _sz(x) (int)(x).size()

struct line{
    ll m,c;
    line(ll m=0,ll c=0):m(m),c(c){}
    ll operator()(const ll &x)const{return m*x+c;}
};
struct cht{
    deque<line> dq;
    bool check(line f1,line f2,line f3){
        return (f1.c-f2.c)*(f3.m-f2.m)>(f2.c-f3.c)*(f2.m-f1.m);
    }
    void insert(ll m,ll c){
        line f(m,c);
        while(_sz(dq)>1&&check(dq.end()[-2],dq.back(),f)) dq.pop_back();
        dq.eb(f);
    }
    ll qr(ll x){
        if(dq.empty()) return LLONG_MAX>>1;
        while(_sz(dq)>1&&dq.front()(x)>dq[1](x)) dq.pop_front();
        return dq.front()(x);
    }
    void clear(){dq.clear();}
}cv;

int n;
vector<int> adj[500005];
int sz[500005];
ll qs[500005], mn[500005],ans1,ans2;

ll Cn2(ll x){return x*(x-1)>>1;}

void dfs1(int u,int p){
    sz[u]=1;
    for(auto &v:adj[u]){
        if(v==p) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
    }
}
struct cmp{
    bool operator()(const int &l,const int &r)const{
        return sz[l]<sz[r];
    }
};
void dfs2(int u,int p){
    mn[u]=Cn2(sz[u])+qs[u];
    priority_queue<int,vector<int>,cmp> pq;
    for(auto &v:adj[u]){
        if(v==p) continue;
        qs[v]=qs[u]+Cn2(sz[u]-sz[v]);
        dfs2(v,u);
        mn[u]=min(mn[u],mn[v]);
        ans1=min(ans1,mn[v]-qs[v]+Cn2(n-sz[v]));
        pq.emplace(v);
    }
    cv.clear();
    while(_sz(pq)){
        int v=pq.top();
        ll x=sz[v];
        pq.pop();
        ans2=min(ans2,cv.qr(x)+(1LL*n*n-n>>1)+(x*x+x>>1)-n*x  +mn[v]-qs[v]);
        cv.insert(x,(x*x+x>>1)-n*x  +mn[v]-qs[v]);
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n;
    for(int i=1;i<n;++i){
        int u,v; cin>>u>>v;
        adj[u].eb(v),adj[v].eb(u);
    }
    ans1=ans2=LLONG_MAX;
    dfs1(1,1);
    dfs2(1,1);
    cout<<( 1LL*n*(n-1)-min(ans1,ans2) );

    return 0;
}
