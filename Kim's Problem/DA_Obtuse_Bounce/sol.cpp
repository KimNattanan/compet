#include<bits/stdc++.h>
using namespace std;

int a[200005];

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n; cin>>n;
  for(int i=0;i<n;++i){
    int x,y; cin>>x>>y;
    a[i]=x*x+y*y;
  }
  sort(a,a+n);
  int Q; cin>>Q;
  while(Q--){
    int x,y; cin>>x>>y;
    cout << (lower_bound(a,a+n,x*x+y*y)-a) <<'\n';
  }
}