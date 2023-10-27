#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

vector<pii> adj[50005];
int d0[50005],d1[1000][50005];
const int K=1000;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,s,t,m,Q; cin>>n>>s>>t>>m>>Q;
    for(int i=0;i<m;++i){
        int u,v,w; cin>>u>>v>>w;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
    vector<int> S(s),T(t),mid;
    queue<pii> q;
    memset(d0,0x3f,sizeof d0);
    for(int i=0;i<s;++i) cin>>S[i],q.emplace(S[i],0),d0[S[i]]=0;
    for(int i=0;i<t;++i) cin>>T[i];
    while(q.size()){
        int u=q.front().f;
        int w=q.front().s;
        q.pop();
        for(auto &vw:adj[u]){
            if(d0[vw.f]>w+1){
                d0[vw.f]=w+1;
                if(w+1==K) mid.pb(vw.f);
                else q.push({vw.f,w+1});
            }
        }
    }
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    memset(d1,0x3f,sizeof d1);
    int now=0;
    for(auto &e:mid){
        pq.push({0,e}),d1[now][e]=0;
        while(pq.size()){
            int u=pq.top().s;
            int w=pq.top().f;
            pq.pop();
            for(auto &vw:adj[u]){
                if(d1[now][vw.f]>w+vw.s){
                    d1[now][vw.f]=w+vw.s;
                    pq.push({w+vw.s,vw.f});
                }
            }
        }
        ++now;
    }
    while(Q--){
        int u,v; cin>>u>>v;
        int ans=INT_MAX;
        for(int i=0;i<now;++i){
            ans=min(ans,d1[i][u]+d1[i][v]);
        }
        cout<<ans<<endl;
    }

    return 0;
}
