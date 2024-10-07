#include<bits/stdc++.h>
using namespace std;

int a[1000005],b[1000005];

int main(){
  ios::sync_with_stdio(false); cin.tie(0);
  int n;
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>a[i];
    b[a[i]]=i;
  }
  int n_2=n>>1;
  if(n&1){
    if(a[1]==n_2+1){
      int d = (a[2]-(a[1]<a[2])>n_2) ? -1 : 1;
      for(int i=0;i<n_2;i++){
        int x=a[1];
        swap(a[1],a[b[x+d]]);
        swap(b[x],b[x+d]);
      }
      for(int i=0;i<n_2;i++){
        int x=a[2],y=x+d;
        if(y==a[1]) y+=d;
        swap(a[2],a[b[y]]);
        swap(b[x],b[y]);
      }
    }
    else{
      int d = a[1]>n_2 ? -1 : 1;
      for(int i=0;i<n_2;i++){
        int x=a[1];
        swap(a[1],a[b[x+d]]);
        swap(b[x],b[x+d]);
      }
      int mid=n_2+(a[1]<=n_2);
      int d2 = a[2]>mid ? -1 : 1;
      if(d!=d2){
        int x=a[1];
        swap(a[1],a[b[x+d]]);
        swap(b[x],b[x+d]);
      }
      for(int i=0;i<n_2;i++){
        int x=a[2],y=x+d2;
        if(y==a[1]) y+=d2;
        swap(a[2],a[b[y]]);
        swap(b[x],b[y]);
      }
    }
  }
  else{
    int d = a[1]>n_2 ? -1 : 1;
    for(int i=0;i<n_2;i++){
      int x=a[1];
      swap(a[1],a[b[x+d]]);
      swap(b[x],b[x+d]);
    }
  }
  for(int i=1;i<=n;i++) cout<<a[i]<<" ";
}
