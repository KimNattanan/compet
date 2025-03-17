#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) ((x+y)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) ((x*y)%md)
#define Mul(x,y) (x=mul(x,y))
const int inf=1e9;
const ll linf=1e18;
const ll md=1e9+7;

ll a[100005],b[100005],ans[200005];
using A=tuple<ll,ll,int>;
priority_queue<A,vector<A>,greater<A>> pq;

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n; cin>>n;
  for(int i=1;i<=n;++i) cin>>a[i];
  for(int i=1;i<=n;++i) cin>>b[i];
  
  for(int i=n<<1;i>0;--i) ans[i]=1e18;
  int cnt=0;
  ll sum=0,mx=-1e18;
  multiset<ll> ms;
  for(int i=1;i<=n;++i){
    if(a[i]<=b[i]) pq.emplace(a[i],1e18,i), pq.emplace(b[i],1e18,i), ms.emplace(b[i]);
    else pq.emplace(a[i]+b[i]>>1,a[i]+b[i]+1>>1,i);
    ms.emplace(a[i]);
  }
  while(!pq.empty()){
    auto [u1,u2,iu] = pq.top(); pq.pop();
    if(a[iu]<=b[iu]){
      ans[++cnt]=(sum+=u1);
      mx=u1;
      ms.erase(ms.find(u1));
    }
    else{
      ans[cnt+1]=min(sum+a[iu]+b[iu]-mx, sum+(*ms.lower_bound(b[iu])));
      ans[cnt+=2]=(sum+=a[iu]+b[iu]);
      mx=max(mx,b[iu]);
      ms.erase(ms.find(a[iu]));
    }
  }
  
  int Q; cin>>Q;
  while(Q--){
    ll k; cin>>k;
    cout<<(upper_bound(ans+1,ans+(n<<1|1),k)-ans-1)<<'\n';
  }
}
