#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int N=100005;

int phi[N];

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  for(int i=1;i<N;++i) phi[i]=i;
  for(int i=1;i<N;++i){
    for(int j=i*2;j<N;j+=i) phi[j]-=phi[i];
  }
}
