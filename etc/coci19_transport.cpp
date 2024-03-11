#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
using ll=long long;
#define sz(x) (int)(x).size()
 
vector<pair<int,ll>> adj[100005];
ll a[100005],ans;
int sz[100005];
bitset<100005> vis;
 
struct fenwick{
    vector<int> bit;
    void init(int n){bit.assign(n,0);}
    void upd(int i,int x){
        for(;i<sz(bit);i+=i&-i) bit[i]+=x;
    }
    ll qr(int i){
        ll ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
}fw;
 
int dfs_sz(int u,int p){
    sz[u]=1;
    for(auto &[v,w]:adj[u]){
        if(!vis[v]&&v!=p) sz[u]+=dfs_sz(v,u);
    }
    return sz[u];
}
int centroid(int u,int p,int n){
    for(auto &[v,w]:adj[u]){
        if(!vis[v]&&v!=p&&sz[v]>n) return centroid(v,u,n);
    }
    return u;
}
void dfs1(int u,int p,ll sum,ll mx,vector<ll> &vec){
    if(sum>=mx) vec.eb(sum);
    for(auto &[v,w]:adj[u]){
        if(vis[v]||v==p) continue;
        dfs1(v,u,sum+a[v]-w,max(mx,sum+a[v]-w),vec);
    }
}
void dfs2(int u,int p,ll sum,ll mx,vector<ll> &vec){
    vec.eb(mx);
    for(auto &[v,w]:adj[u]){
        if(vis[v]||v==p) continue;
        dfs2(v,u,sum+w-a[u],max(mx,sum+w-a[u]),vec);
    }
}
void decomp(int u){
    int c=centroid(u,u,dfs_sz(u,u)>>1);
    vis[c]=1;
 
    ll x=ans;
 
    vector<vector<ll>> v1,v2;
    vector<ll> comp;
    for(auto &[v,w]:adj[c]){
        if(vis[v]) continue;
        vector<ll> tmp1,tmp2;
        dfs1(v,c,a[v]-w,max(0LL,a[v]-w),tmp1);
        dfs2(v,c,w-a[c],w-a[c],tmp2);
        v1.eb(tmp1), v2.eb(tmp2);
        for(auto &e:tmp2){
            comp.eb(e);
            if(e<=0) ++ans;
        }
        ans+=sz(tmp1);
    }
 
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());
    
    fw.init(sz(comp)+5);
    for(int i=0;i<sz(v1);++i){
        for(auto &e:v1[i]) ans+=fw.qr(upper_bound(comp.begin(),comp.end(),e)-comp.begin());
        for(auto &e:v2[i]) fw.upd(lower_bound(comp.begin(),comp.end(),e)-comp.begin()+1,1);
    }
    fw.init(sz(comp)+5);
    for(int i=sz(v1)-1;i>=0;--i){
        for(auto &e:v1[i]) ans+=fw.qr(upper_bound(comp.begin(),comp.end(),e)-comp.begin());
        for(auto &e:v2[i]) fw.upd(lower_bound(comp.begin(),comp.end(),e)-comp.begin()+1,1);
    }
    
    for(auto &[v,w]:adj[c]){
        if(!vis[v]) decomp(v);
    }
}
 
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    int n; cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=1;i<n;++i){
        int u,v; cin>>u>>v;
        ll w; cin>>w;
        adj[u].eb(v,w), adj[v].eb(u,w);
    }
    decomp(1);
    cout<<ans;
 
    return 0;
}
