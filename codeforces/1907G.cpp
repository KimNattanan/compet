
 #include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
 
int adj[100005],deg[100005],dist[100005];
bool state[100005];
string s;
vector<int> vec,ans;
int dfs(int u,int p){
    deg[u]=0;
    if(state[u]!=s[u]-'0') vec.eb(u);
    if(adj[u]==p) return 1;
    dist[adj[u]]=dist[u]+1;
    return 1+dfs(adj[u],p);
}
void play(int u,int v){
    ans.eb(u);
    if(adj[u]==v) return;
    play(adj[u],v);
}
 
void solve(){
 
    int n; cin>>n;
    for(int i=1;i<=n;++i) deg[i]=state[i]=dist[i]=0;
    ans.clear();
    cin>>s;
    s=" "+s;
    for(int i=1;i<=n;++i){
        cin>>adj[i];
        ++deg[adj[i]];
    }
    queue<int> q;
    for(int i=1;i<=n;++i){
        if(!deg[i]) q.push(i);
    }
    while(q.size()){
        int u=q.front();
        int v=adj[u];
        q.pop();
        if(--deg[v]==0) q.push(v);
        if(state[u]!=s[u]-'0') ans.eb(u),state[v]^=1;
    }
    for(int i=1;i<=n;++i){
        if(deg[i]){
            vec.clear();
            int a=dfs(i,i),b=0;
            if(vec.size()&1){
                cout<<-1<<endl;
                return;
            }
            if(vec.empty()) continue;
            for(int i=0;i<vec.size();++i){
                int r=((i&1)?-1:1);
                a+=r*dist[vec[i]];
                b-=r*dist[vec[i]];
            }
            if(a>=b){
                for(int i=0;i<vec.size();i+=2) play(vec[i],vec[i+1]);
            }
            else{
                play(vec.back(),vec.front());
                for(int i=1;i<vec.size()-1;i+=2) play(vec[i],vec[i+1]);
            }
        }
    }
    cout<<ans.size()<<endl;
    for(auto &e:ans) cout<<e<<" ";
    cout<<endl;
 
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