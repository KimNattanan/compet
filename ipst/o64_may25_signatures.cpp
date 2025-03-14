#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define Add(x,y) (x=(x+y)%md)
#define add(x,y) ((x+y)%md)

const ll md=119<<23|1;

int bittoi(string s){
  int res=0;
  for(auto &e:s) res=(res<<1|(e-'0'));
  return res;
}
string itobit(int x,int len){
  string res;
  res.resize(len);
  for(int i=len-1;i>=0;--i,x>>=1) res[i]=(x&1)+'0';
  return res;
}

bitset<1<<20> ch,used;
vector<pii> adj[1<<20];

string cur,best;
void dfs(int u){
  if(sz(cur)>sz(best)){
    best=cur;
    cout<<best<<'\n';
  }
  for(auto &[v,b]:adj[u]){
    if(used[u<<1|b]) continue;
    used[u<<1|b]=1;
    cur.push_back('0'+b);
    dfs(v);
    used[u<<1|b]=0;
    cur.pop_back();
  }
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int k,n; cin>>k>>n;
  for(int i=0;i<n;++i){
    string s; cin>>s;
    ch[bittoi(s)]=1;
  }
  int cnt=0;
  for(int i=0;i<(1<<k-1);++i){
    int v1=(i<<1)^((1<<k-1)&i),v2=v1|1;
    if(!ch[i<<1]) adj[i].eb(v1,0);
    if(!ch[i<<1|1]) adj[i].eb(v2,1);
    cnt+=(sz(adj[i])==1);
  }
  for(int i=0;i<(1<<k-1);++i) cur=itobit(i,k-1), dfs(i);
}
/*

*/
