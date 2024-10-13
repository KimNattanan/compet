#include<bits/stdc++.h>
using namespace std;
using ld=long double;
const int N=10005;

int a[N]={1};
ld C(int n,int r){
  r=max(r,n-r);
  ld ret=1;
  for(int i=r+1;i<=n;++i) ret=ret*i/(i-r);
  return ret;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);
  
  for(int i=1;i<N;++i) a[i]=(i<<1|1)*(i+1);
  
  int Q; cin>>Q;
  for(int tc=1;tc<=Q;++tc){
    int n,x,y; cin>>n>>x>>y;
    if((x+y)&1){ cout<<"Case #"<<tc<<": 0.0\n"; continue; }
    int id=lower_bound(a,a+N,n)-a;
    if(abs(x)+y!=id<<1){ cout<<"Case #"<<tc<<": "<< (abs(x)+y<(id<<1)) <<".0\n"; continue; }
    if(x==0){ cout<<"Case #"<<tc<<": "<< (n==a[id]) <<".0\n"; continue; }
    n-=a[id-1];
    if(y>=n){ cout<<"Case #"<<tc<<": 0.0\n"; continue; }
    if(y<n-(id<<1)){ cout<<"Case #"<<tc<<": 1.0\n"; continue; }
    id<<=1;
    ld cur=C(n,y+1), ans=cur;
    for(int i=y+2;i<=n;++i){
      cur*=ld(n-i+1)/i;
      ans+=cur;
    }
    for(int i=0;i<n;++i) ans/=2;
    cout<<"Case #"<<tc<<": "<<ans<<'\n';
  }
}
