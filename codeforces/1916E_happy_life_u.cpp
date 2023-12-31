#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
 
vector<int> adj[300005],adj2[300005],item[300005];
int val[300005],tour0[300005],tour1[300005],node[300005],lvl[300005],dif[300005];
map<int,int> mp;
ll ans;
 
struct segment{
    vector<segment> child;
    int l,r,mid,mx,lazy;
    segment(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)),lazy(0){}
    void build(){
        if(l==r) return void(mx=dif[node[l]]);
        child.eb(l,mid),child.eb(mid+1,r);
        child[0].build(),child[1].build();
        mx=max(child[0].mx,child[1].mx);
    }
    void flush(){
        if(!lazy) return;
        mx+=lazy;
        if(l!=r){
            child[0].lazy+=lazy;
            child[1].lazy+=lazy;
        }
        lazy=0;
    }
    void upd(int l0,int r0,int x){
        flush();
        if(l0<=l&&r<=r0){
            lazy+=x;
            flush();
            return;
        }
        if(l>r0||r<l0) return;
        child[0].upd(l0,r0,x),child[1].upd(l0,r0,x);
        mx=max(child[0].mx,child[1].mx);
    }
    int qr(int l0,int r0){
        flush();
        if(l0<=l&&r<=r0) return mx;
        if(l>r0||r<l0) return 0;
        return max(child[0].qr(l0,r0),child[1].qr(l0,r0));
    }
}t;
 
void dfs(int u,int id,int id2){
    tour0[u]=tour1[u]=id;
    node[id]=u;
    lvl[u]=id2;
    ++mp[val[u]];
    dif[u]=mp.size();
    for(auto &v:adj[u]){
        dfs(v,id+1,id2+1);
        tour1[u]=id=tour1[v];
    }
    if(--mp[val[u]]==0) mp.erase(val[u]);
}
bool cmp(const int &l,const int &r){
    return tour0[l]<tour0[r];
}
void dfs2(int u){
    pii best(1,1);
    for(auto &v:adj[u]){
        best.s=max(best.s,t.qr(tour0[v],tour1[v])-lvl[u]);
        if(best.f<best.s) swap(best.f,best.s);
    }
    ans=max(ans,1LL*best.f*best.s);
    for(auto &v:adj2[u]){
        t.upd(tour0[v],tour1[v],1);
    }
    for(auto &v:adj[u]){
        dfs2(v);
    }
}
 
void solve(){
 
    int n; cin>>n;
    for(int i=1;i<=n;++i){
        adj[i].clear();
        adj2[i].clear();
        item[i].clear();
    }
    for(int i=2;i<=n;++i){
        int u; cin>>u;
        adj[u].eb(i);
    }
    for(int i=1;i<=n;++i){
        cin>>val[i];
        item[val[i]].eb(i);
    }
    dfs(1,1,0);
    for(int i=1;i<=n;++i){
        if(item[i].empty()) continue;
        sort(item[i].begin(),item[i].end(),cmp);
        stack<int> st;
        for(auto &e:item[i]){
            while(st.size()&&tour1[st.top()]<tour0[e]) st.pop();
            if(st.size()) adj2[st.top()].eb(e);
            st.emplace(e);
        }
    }
    t=segment(1,n);
    t.build();
    ans=0;
    dfs2(1);
    cout<<ans<<endl;
 
}
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    int Q(1);
    cin>>Q;
    while(Q--){
        solve();
    }
 
    return 0;
}
