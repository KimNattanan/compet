#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) ((((x)+(y))%md+md)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) ((((x)*(y))%md+md)%md)
#define Mul(x,y) (x=mul(x,y))
template<class T> T chmn(T &x,T y){ return x=min(x,y); }
template<class T> T chmx(T &x,T y){ return x=max(x,y); }
const int inf=1e9;
const ll linf=1e18;
const ll md=1e9+7;
// const ll md=119<<23|1;


queue<ll> q;
map<ll,int> mp;

void solve(){
  ll x; cin>>x;
  while(!q.empty()) q.pop();
  mp.clear();
  mp[x]=0;
  q.emplace(x);
  while(1){
    ll u = q.front(); q.pop();
    int w=mp[u];
    if(u==1) return void(cout<<w<<'\n');
    if(u%3==0 && mp.find(u/3)==mp.end()) mp[u/3]=w+1, q.emplace(u/3);
    if(u%2==0 && mp.find(u/2)==mp.end()) mp[u/2]=w+1, q.emplace(u/2);
    if(mp.find(u-1)==mp.end()) mp[u-1]=w+1, q.emplace(u-1);
  }
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  cin>>Q;
  while(Q--) solve();
}
