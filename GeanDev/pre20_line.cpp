#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
using ld=long double;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()
 
const ll md=1e9+7;
 
template<class T>
void add(T &x, const T &y){ x=(x+y)%md; }
 
ll dp[2][255][505],qs[2][255][505];
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	int n,K; cin>>n>>K;
	int n2=n>>1;
	dp[0][0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=i&&j<=n2;++j){
			for(int k=0;k<=K;++k){
				dp[i&1][j][k]=dp[~i&1][j][k];
				if(j>0) add(dp[i&1][j][k],dp[~i&1][j-1][k]);
				if(j<i&&j<n2){
					int l=k-min(j,k);
					if(l==0) add(dp[i&1][j][k],qs[~i&1][j+1][k]);
					else add(dp[i&1][j][k],(qs[~i&1][j+1][k]-qs[~i&1][j+1][l-1]+md)%md);
				}
				if(k==0) qs[i&1][j][k]=dp[i&1][j][k];
				else qs[i&1][j][k]=(qs[i&1][j][k-1]+dp[i&1][j][k])%md;
			}
		}
	}
	cout<<dp[n&1][0][K];
 
	return 0;
}
