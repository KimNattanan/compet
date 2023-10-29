#include "triplets.h"
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back

const int inf=1e9+7;
const int md=9377;

vector<int> adj[100005];
int disc[100005],low[100005],comp[100005],id0,id1;
bool inst[100005];
stack<int> st;

void dfs(int u){
    disc[u]=low[u]=++id0;
    st.push(u);
    inst[u]=1;
    for(auto &v:adj[u]){
        if(!disc[v]) dfs(v),low[u]=min(low[u],low[v]);
        else if(inst[v]) low[u]=min(low[u],low[v]);
    }
    if(low[u]==disc[u]){
        ++id1;
        while(st.top()!=u){
            comp[st.top()]=id1;
            inst[st.top()]=0;
            st.pop();
        }
        st.pop();
        comp[u]=id1;
        inst[u]=0;
    }
}

struct AA{
    int i,x,y;
    bool operator<(const AA&o)const{
        if(x!=o.x) return x<o.x;
        return y<o.y;
    }
};

int count_triplets(int N, std::vector<int> U, std::vector<int> V, std::vector<int> C){
    int M=U.size();
    for(int i=0;i<M;++i){
        adj[U[i]].pb(V[i]);
    }
    for(int i=0;i<N;++i){
        if(!disc[i]) dfs(i);
    }
    ll ans=(1LL*N*(N-1)*(N-2))%md;
    vector<AA> vec;
    for(int i=0;i<N;++i){
        vec.pb({i,comp[i],C[i]});
    }
    sort(vec.begin(),vec.end());
    for(int i=0;i<N;){
        int r=i;
        while(r<N&&vec[r].x==vec[i].x&&vec[r].y==vec[i].y) ++r;

        ll cnt=r-i;
        if(cnt>2){
            ll x=(cnt*(cnt-1)*(cnt-2))%md;
            ans=(ans-x+md)%md;
        }
        i=r;
    }

    return ans;
}









//
//#include "triplets.h"
//#include <cstdio>
//
//int main()
//{
//  int N,M;
//  int tmp;
//  std::vector<int> C;
//  std::vector<int> U;
//  std::vector<int> V;
//
//  tmp = scanf("%d %d",&N,&M);
//
//  for(int j=0; j<N; j++) {
//    int c;
//    tmp = scanf("%d",&c);
//    C.push_back(c);
//  }
//
//  for(int i=0; i<M; i++) {
//    int u,v;
//    tmp = scanf("%d %d",&u,&v);
//    U.push_back(u);
//    V.push_back(v);
//  }
//
//  printf("%d\n", count_triplets(N, U, V, C));
//
//  return 0;
//}

