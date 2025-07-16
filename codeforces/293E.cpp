#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
 
int n,L,W;
vector<pii> adj[100005];
int sz[100005];
bool vis[100005];
ll ans;
 
struct fenwick{
    vector<int> bit;
    int n;
    void init(int n_){
        n=n_;
        bit=vector<int>(n);
    }
    void add(int i,int x){
        for(;i<n;i+=i&-i) bit[i]+=x;
    }
    int qr(int i){
        int ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
}fw;
 
int dfs_sz(int u,int p){
    sz[u]=1;
    for(auto &[v,w]:adj[u]){
        if(v!=p&&!vis[v]) sz[u]+=dfs_sz(v,u);
    }
    return sz[u];
}
int centroid(int u,int p,int n){
    for(auto &[v,w]:adj[u]){
        if(v!=p&&!vis[v]&&sz[v]>n) return centroid(v,u,n);
    }
    return u;
}
int dfs(int u,int p,int cnt,int d,vector<pii> &vec1,vector<pii> &vec2){
    vec1.eb(d,cnt);
    vec2.eb(d,cnt);
    int mx=cnt;
    if(cnt==L) return mx;
    for(auto &[v,w]:adj[u]){
        if(v!=p&&!vis[v]&&d+w<=W) mx=max(mx,dfs(v,u,cnt+1,d+w,vec1,vec2));
    }
    return mx;
}
void decomp(int u){
    int c=centroid(u,u,dfs_sz(u,u)>>1);
    vis[c]=1;
 
    vector<pii> vec1,vec2;
    vec1.eb(0,0);
    int mx1=0;
    for(auto &[v,w]:adj[c]){
        if(vis[v]) continue;
        vec2.clear();
        int mx2=dfs(v,c,1,w,vec1,vec2);
        mx1=max(mx1,mx2);
        sort(vec2.begin(),vec2.end());
        fw.init(mx2+5);
        int id=0;
        for(int i=vec2.size()-1;i>=0;--i){
            while(id<i&&vec2[id].f+vec2[i].f<=W) fw.add(vec2[id++].s+1,1);
            while(id>i) fw.add(vec2[--id].s+1,-1);
            ans-=fw.qr(min(mx2,L-vec2[i].s)+1);
        }
    }
    sort(vec1.begin(),vec1.end());
    fw.init(mx1+5);
    int id=0;
    for(int i=vec1.size()-1;i>=0;--i){
        while(id<i&&vec1[id].f+vec1[i].f<=W) fw.add(vec1[id++].s+1,1);
        while(id>i) fw.add(vec1[--id].s+1,-1);
        ans+=fw.qr(min(mx1,L-vec1[i].s)+1);
    }
 
    for(auto &[v,w]:adj[c]){
        if(!vis[v]) decomp(v);
    }
}
 
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    cin>>n>>L>>W;
    for(int i=2;i<=n;++i){
        int v,w; cin>>v>>w;
        adj[i].eb(v,w),adj[v].eb(i,w);
    }
    decomp(1);
    cout<<ans<<endl;
 
    return 0;
}
