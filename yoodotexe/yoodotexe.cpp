#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define ll long long

//#define int ll

const ll md=1e9+7;

int n;
vector<int> adj[100005],adj2[100005];
bool mark[100005],mark2[100005];
bool flag[100005],flag2[100005];
bool closed[100005];

void dfs(int u){
    flag[u]=1;
    for(auto &v:adj[u]){
        if(closed[v]) mark[v]=1;
        else if(!flag[v]) dfs(v);
    }
}
void dfs2(int u){
    flag2[u]=1;
    for(auto &v:adj2[u]){
        if(closed[v]) mark2[v]=1;
        else if(!flag[v]) dfs2(v);
    }
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int m,Q; cin>>n>>m>>Q;
    for(int i=0;i<m;++i){
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj2[v].pb(u);
    }
    vector<pii> vec;
    for(int i=0;i<Q;++i){
        int a,b; cin>>a>>b;
        vec.pb({a,b});
        if(a==1) closed[b]=1;
    }
    dfs(1);
    dfs2(n);
    stack<int> ans;
    for(int i=Q-1;i>=0;--i){
        int a=vec[i].f,b=vec[i].s;
        if(a==1){
            closed[b]=0;
            if(mark[b]){
                mark[b]=0;
                dfs(b);
            }
            if(mark2[b]){
                mark2[b]=0;
                dfs2(b);
            }
        }
        else{
            ans.push(flag[b]&flag2[b]);
        }
    }
    while(ans.size()){
        cout<<ans.top()<<endl;
        ans.pop();
    }


    return 0;
}
/**


*/
