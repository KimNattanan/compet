#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

vector<int> adj[1000005];

struct BCC{
  int disc[1000005],low[1000005],id;
  bitset<1000005> ap;
  stack<int> st;
  vector<vector<int>> comp;
  void tarj(int u,int p=-1){
    disc[u]=low[u]=++id;
    st.emplace(u);
    for(auto &v:adj[u]) if(v!=p){
      if(!disc[v]){
        tarj(v,u);
        if(low[v]>=disc[u]){
          ap[u] = (p!=-1 || disc[v]!=disc[u]+1);
          comp.eb(vector<int>{u});
          while(comp.back().back()!=v) comp.back().eb(st.top()), st.pop();
        }
        else low[u] = min(low[u], low[v]);
      }
      else low[u] = min(low[u],disc[v]);
    }
  }
  void init(int u){
    tarj(u);
  }
}bcc;

/*

 2     4
| \   / |
|  \ /  |
|   1   |
|  / \  |
| /   \ |
 3     5

*/

void f(int u,int v){
  adj[u].emplace_back(v);
  adj[v].emplace_back(u);
}

int main(){
  f(1,2);
  f(1,3);
  f(2,3);
  f(1,4);
  f(1,5);
  f(4,5);
  bcc.init(1);
  for(int i=1;i<=5;++i) cout<<bcc.ap[i];
  cout<<'\n';
  for(auto &e:bcc.comp){
    for(auto &x:e) cout<<x<<" ";
    cout<<'\n';
  }
}