#include<bits/stdc++.h>
using namespace std;

int px[200005],py[200005];

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n; cin>>n;
  for(int i=0;i<n;++i) cin>>px[i]>>py[i];
  int Q; cin>>Q;
  while(Q--){
    int x,y; cin>>x>>y;
    int cnt=0;
    for(int i=0;i<n;++i){
      int a2=(x-px[i])*(x-px[i])+(y-py[i])*(y-py[i]);
      int b2=((-x)-px[i])*((-x)-px[i])+((-y)-py[i])*((-y)-py[i]);
      int c2=x*x+y*y<<2;
      if(a2+b2<c2) ++cnt;
    }
    cout<<cnt<<'\n';
  }
}