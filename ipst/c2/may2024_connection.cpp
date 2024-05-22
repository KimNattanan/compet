#include "connection.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

vector<int> adj[1000005],adj2[3000005];
int disc[1000005],low[1000005],nds[1000005],id,sz[3000005],H[3000005],p[3000005],dp[3000005];
bitset<1000005> isap;
bitset<3000005> use_mx;
vector<vector<int>> comps;
stack<int> st;

void tarj(int u,int p){
    disc[u]=low[u]=++id;
    st.emplace(u);
    for(auto &v:adj[u]){
        if(v==p) continue;
        if(!disc[v]){
            tarj(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=disc[u]){
                isap[u]=(disc[u]>1||disc[v]>2);
                comps.eb(vector<int>{u});
                while(comps.back().back()!=v) comps.back().eb(st.top()), st.pop();
            }
        }
        else low[u]=min(low[u],disc[v]);
    }
}

int fSet(int u){ return p[u]==u ? u : p[u]=fSet(p[u]); }

int recommended_stations(int N, int M, std::vector<int> H0, std::vector<int> U0, std::vector<int> V0) {
    for(int i=0;i<M;++i) adj[U0[i]].eb(V0[i]), adj[V0[i]].eb(U0[i]);
    id=0, tarj(0,0);

    vector<int> vec;
    id=0;
    for(int i=0;i<N;++i){
        if(!isap[i]) continue;
        vec.eb(++id);
        p[id]=id;
        nds[i]=id;
        sz[id]=1;
        H[id]=H0[i];
    }
    int last_ap=id;
    while(!comps.empty()){
        vec.eb(++id);
        p[id]=id;
        H[id]=-1;
        for(auto &e:comps.back()) if(!isap[e]) nds[e]=id, H[id]=max(H[id],H0[e]), ++sz[id];
        for(auto &e:comps.back()){
            if(!isap[e]) continue;
            if(H[id]>H[nds[e]]) adj2[id].eb(nds[e]);
            else adj2[nds[e]].eb(id);
        }
        comps.pop_back();
    }
    sort(vec.begin(),vec.end(),[&](const int &l,const int &r){
        return H[l]<H[r];
    });
    for(auto &u:vec){
        if(sz[u]==0) continue;
        dp[u]=sz[u]-1;
        for(auto &v:adj2[u]){
            int V=fSet(v);
            p[V]=u;
            dp[u]+=dp[V];
            if(u<=last_ap&&use_mx[v]) ++dp[u],use_mx[v]=0;
        }
        if(sz[u]==1){
            if(dp[u]==0) dp[u]=1;
            else if(u>last_ap) use_mx[u]=1;
        }
        else use_mx[u]=1;
    }

    return dp[fSet(1)];
}
