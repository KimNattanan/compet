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

string s[4];
int n[4],t[4];
ll dp[51][51][51][51],lm[4][51][26];

ll f(int i,int j,int k,int l){
  if(!i || !j || !k || !l) return 0;
  return dp[i-1][j-1][k-1][l-1]+1;
}

void solve(){
  for(int i=0;i<4;++i){
    cin>>s[i];
    n[i]=sz(s[i]);
    for(auto &e:s[i]) e-='a';
    s[i] = " "+s[i];
  }
  for(int i=0;i<4;++i){
    for(int j=1;j<=n[i];++j){
      for(int z=0;z<26;++z){
        if(s[i][j]==z) lm[i][j][z] = j;
        else lm[i][j][z] = lm[i][j-1][z];
      }
    }
  }
  for(int i=0;i<=n[0];++i) for(int j=0;j<=n[1];++j) for(int k=0;k<=n[2];++k) for(int l=0;l<=n[3];++l){
    if(!i || !j || !k || !l) dp[i][j][k][l] = 0;
    else{
      dp[i][j][k][l] = dp[i-1][j][k][l] + dp[i][j-1][k][l] + dp[i][j][k-1][l] + dp[i][j][k][l-1]
                      - dp[i-1][j-1][k][l] - dp[i-1][j][k-1][l] - dp[i-1][j][k][l-1] - dp[i][j-1][k-1][l] - dp[i][j-1][k][l-1] - dp[i][j][k-1][l-1]
                      + dp[i-1][j-1][k-1][l] + dp[i-1][j-1][k][l-1] + dp[i-1][j][k-1][l-1] + dp[i][j-1][k-1][l-1]
                      - dp[i-1][j-1][k-1][l-1];
      if(s[0][i]==s[1][j] && s[0][i]==s[2][k] && s[0][i]==s[3][l]){
        int z = s[0][i];
        dp[i][j][k][l] += dp[i-1][j-1][k-1][l-1] + 1;
        int i_ = lm[0][i-1][z],
            j_ = lm[1][j-1][z],
            k_ = lm[2][k-1][z],
            l_ = lm[3][l-1][z];
        dp[i][j][k][l] -= f(i_,j,k,l) + f(i,j_,k,l) + f(i,j,k_,l) + f(i,j,k,l_)
                        - f(i_,j_,k,l) - f(i_,j,k_,l) - f(i_,j,k,l_) - f(i,j_,k_,l) - f(i,j_,k,l_) - f(i,j,k_,l_)
                        + f(i_,j_,k_,l) + f(i_,j_,k,l_) + f(i_,j,k_,l_) + f(i,j_,k_,l_)
                        - f(i_,j_,k_,l_);
      }
    }
  }
  cout << dp[n[0]][n[1]][n[2]][n[3]] << '\n';
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  cin>>Q;
  while(Q--) solve();

}
