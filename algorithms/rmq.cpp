#include<bits/stdc++.h>
using namespace std;

struct rmq{
  vector<vector<int>> a;
  void init(vector<int> &vec){
    int n = vec.size();
    int m = 31-__builtin_clz(n);
    a.resize(m+1, vector<int>(n));
    a[0] = vec;
    for(int i=0;i<m;++i) for(int j=0;j<n;++j) a[i+1][j] = max(a[i][j], a[i][max(0,j-(1<<i))]);
  }
  int qr(int l,int r){
    int i = 31-__builtin_clz(r-l+1);
    return max(a[i][r],a[i][l+(1<<i)-1]);
  }
};
