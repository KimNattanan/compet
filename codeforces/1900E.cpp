#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

ll a[200005];
vector<int> adj[200005],adj2[200005];
int disc[200005],low[200005],comp[200005],id0,id1;
bool inst[200005];
stack<int> st;
int cnt[200005];
ll sum[200005];
pair<int,ll> dp[200005];
bool deg[200005];
void dfs(int u){
    disc[u]=low[u]=++id0;
    inst[u]=1;
    st.push(u);
    for(auto &v:adj[u]){
        if(!disc[v]) dfs(v),low[u]=min(low[u],low[v]);
        else if(inst[v]) low[u]=min(low[u],low[v]);
    }
    if(disc[u]==low[u]){
        comp[u]=++id1;
        sum[id1]=a[u];
        cnt[id1]=1;
        while(st.top()!=u){
            inst[st.top()]=0;
            comp[st.top()]=id1;
            sum[id1]+=a[st.top()];
            ++cnt[id1];
            st.pop();
        }
        inst[u]=0;
        st.pop();
    }
}
void dfs2(int u){
    dp[u]={0,0};
    for(auto &v:adj2[u]){
        if(dp[v].f==-1) dfs2(v);
        if(dp[v].f>dp[u].f) dp[u]=dp[v];
        else if(dp[v].f==dp[u].f) dp[u].s=min(dp[u].s,dp[v].s);
    }
    dp[u]={dp[u].f+cnt[u],dp[u].s+sum[u]};
}

void mian(){

    int n,m; cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        disc[i]=low[i]=comp[i]=sum[i]=cnt[i]=inst[i]=0;
        dp[i]={-1,-1};
        adj[i].clear();
        adj2[i].clear();
    }
    for(int i=1;i<=m;++i){
        int u,v; cin>>u>>v;
        adj[u].eb(v);
    }
    id0=id1=0;
    for(int i=1;i<=n;++i){
        if(!disc[i]) dfs(i);
    }
    for(int i=1;i<=n;++i){
        for(auto &v:adj[i]){
            if(comp[i]!=comp[v]) adj2[comp[i]].eb(comp[v]),deg[comp[v]]=1;
        }
    }
    pair<int,ll> ans={0,0};
    for(int i=1;i<=id1;++i){
        if(dp[i].f==-1) dfs2(i);
        if(dp[i].f>ans.f) ans=dp[i];
        else if(dp[i].f==ans.f) ans.s=min(ans.s,dp[i].s);
    }
    cout<<ans.f<<" "<<ans.s<<endl;

}













int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
    while(Q--){
        mian();
    }

    return 0;
}
