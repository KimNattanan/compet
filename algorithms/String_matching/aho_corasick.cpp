#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

/*
https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1620
*/

struct Aho{
  struct node{
    node *adj[52],*suf;
    vector<int> qrs;
    node():suf(nullptr){ for(auto &e:adj) e=nullptr; }
  };
  using pnode=node*;
  pnode rt;
  queue<pair<pnode,int>> q;

  Aho():rt(new node()){}
  
  pnode insert(string s){
    pnode t=rt;
    for(auto &e:s){
      int i = ('a'<=e&&e<='z') ? e-'a' : e-'A'+26;
      if(t->adj[i]) t=t->adj[i];
      else t=t->adj[i]=new node();
    }
    return t;
  }
  pnode find_suf(pnode t,int i){
    while(t!=rt && !t->adj[i]) t=t->suf;
    if(t->adj[i]) return t->adj[i];
    return rt;
  }
  void build(){
    rt->suf=rt;
    for(int i=0;i<52;++i) if(rt->adj[i]) q.emplace(rt,i);
    while(!q.empty()){
      auto [u,i]=q.front(); q.pop();
      if(u==rt) u->adj[i]->suf = rt;
      else u->adj[i]->suf = find_suf(u->suf,i);
      for(int j=0;j<52;++j) if(u->adj[i]->adj[j]) q.emplace(u->adj[i], j);
    }
  }
};

bitset<1005> ans;

void solve(){
  using pnode=Aho::node*;
  Aho t;
  string s; cin>>s;
  int Q; cin>>Q;
  for(int i=1;i<=Q;++i){
    string s; cin>>s;
    t.insert(s)->qrs.eb(i);
  }
  t.build();
  ans.reset();
  pnode cur=t.rt;
  for(auto &e:s){
    int i = ('a'<=e&&e<='z') ? e-'a' : e-'A'+26;
    cur = t.find_suf(cur,i);
    for(auto &id:cur->qrs) ans[id]=1;
  }
  for(int i=1;i<=Q;++i) cout<<(ans[i] ? "y\n" : "n\n");
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  cin>>Q;
  while(Q--) solve();  

}
