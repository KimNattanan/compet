#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
#define pb push_back
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second

vector<pii> adj;
map<pii,ll> dp;
vector<tuple<int,int,int,int>> edge;
ll a[100005],mx[100005],ans[100005];
int P[100005];
int fSet(int u){return P[u]=P[u]==u?u:fSet(P[u]);}
bool uSet(int u,int v){
    int U=fSet(u),V=fSet(v);
    if(U==V) return 0;
    P[U]=V;
    mx[V]=max(mx[V],mx[U]);
    return 1;
}
ll dfs(int u,int p){
    if(dp.count({u,p})) return dp[{u,p}];
    ll ret=mx[u];
    for(auto &[x,y]:adj){
        if(x==u&&y!=p) ret=max(ret,dfs(y,x));
        else if(y==u&&x!=p) ret=max(ret,dfs(x,y));
    }
    return dp[{u,p}]=ret;
}
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i) cin>>mx[i],P[i]=i;
    for(int i=1;i<n;++i){
        int u,v; cin>>u>>v;
        ll w; cin>>w;
        edge.eb(w,u,v,i);
    }
    sort(edge.begin(),edge.end());
    for(int i=0,j=1;i<edge.size();++j){
        while(j<edge.size()&&get<0>(edge[j])==get<0>(edge[i])) ++j;
        if(j==i+1) ans[get<3>(edge[i])]=mx[fSet(get<1>(edge[i]))]*mx[fSet(get<2>(edge[i]))];
        else{
            adj.clear(),dp.clear();
            for(int k=i;k<j;++k) adj.eb(fSet(get<1>(edge[k])),fSet(get<2>(edge[k])));
            for(int k=i;k<j;++k){
                auto &[w,u,v,id]=edge[k];
                ans[id]=dfs(fSet(u),fSet(v))*dfs(fSet(v),fSet(u));
            }
        }
        for(;i<j;++i) uSet(get<1>(edge[i]),get<2>(edge[i]));
    }
    for(int i=1;i<n;++i) cout<<ans[i]<<endl;

    return 0;
}
