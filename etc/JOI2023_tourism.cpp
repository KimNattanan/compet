#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using pii=pair<int,int>;
using t3=tuple<int,int,int>;
#define f first
#define s second
#define eb emplace_back

vector<int> adj[100005];
int M[100005],m,ans[100005];

struct fenwick{
    vector<int> bit;
    int n;
    void init(int n_){
        n=n_;
        bit=vector<int>(n);
    }
    void add(int i,int x){
        i=m-i+1;
        for(;i<n;i+=i&-i) bit[i]+=x;
    }
    int qr(int i){
        int ret=0;
        i=m-i+1;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
}fw;
set<pii> s;
void upd(int l,int r,int x){
    pii R=*(--s.upper_bound(pii(r+1,1e9)));
    
    auto itrL=--s.upper_bound(pii(l,1e9));
    auto itrR=s.upper_bound(pii(r,1e9));
    auto itr=itrL;
    ++itr;
    fw.add(itrL->s, l-itr->f);
    itrL=itr;
    while(itrL!=itrR){
        ++itr;
        fw.add(itrL->s,(itrL->f)-(itr->f));
        itrL=itr;
    }
    fw.add(x,r-l+1);
    fw.add(R.s,(itrR->f)-(r+1));

    itrL=s.lower_bound(pii(l,-1));
    itrR=--s.upper_bound(pii(r,1e9));
    if(itrL->f<=itrR->f) s.erase(itrL,++itrR);
    s.insert(pii(l,x)),s.insert(pii(r+1,R.s));
}

namespace HLD{
    int tour[100005],head[100005],p0[100005],heavy[100005],id0;
    int dfs(int u,int p){
        p0[u]=p;
        int sz=1;
        pii best(-1,-1);
        for(auto &v:adj[u]){
            if(v!=p){
                int sz2=dfs(v,u);
                sz+=sz2;
                best=max(best,pii(sz,v));
            }
        }
        heavy[u]=best.s;
        return sz;
    }
    void decomp(int u,int p){
        tour[u]=++id0;
        head[u]=p;
        if(heavy[u]!=-1) decomp(heavy[u],p);
        for(auto &v:adj[u]){
            if(v!=p0[u]&&v!=heavy[u]) decomp(v,v);
        }
    }
};
void hld_upd(int u,int v,int x){
    using namespace HLD;
    while(head[u]!=head[v]){
        if(tour[head[u]]>tour[head[v]]) swap(u,v);
        upd(tour[head[v]],tour[v],x);
        v=p0[head[v]];
    }
    if(tour[u]>tour[v]) swap(u,v);
    upd(tour[u],tour[v],x);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>m>>Q;
    for(int i=0;i<n-1;++i){
        int u,v; cin>>u>>v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    for(int i=1;i<=m;++i) cin>>M[i];
    vector<t3> q;
    for(int i=1;i<=Q;++i){
        int l,r; cin>>l>>r;
        q.eb(i,l,r);
    }
    sort(q.begin(),q.end(),[&](const t3 &l,const t3 &r){
        return get<2>(l)<get<2>(r);
    });

    HLD::dfs(1,1);
    HLD::decomp(1,1);
    s.emplace(0,0),s.emplace(m+1,0);
    fw.init(m+5);

    int j=0;
    for(int i=1;i<=m&&j<Q;++i){
        if(i>1) hld_upd(M[i-1],M[i],i-1);
        upd(HLD::tour[M[i]],HLD::tour[M[i]],i);
        while(j<Q&&get<2>(q[j])==i){
            ans[get<0>(q[j])]=fw.qr(get<1>(q[j]));
            ++j;
        }
    }
    for(int i=1;i<=Q;++i) cout<<ans[i]<<endl;

    return 0;
}
