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

template<class T>
T chmx(T &x,const T &v){x=max(x,v);}

int a[305][2], dp[3][305][160][160], n,K,n2;


int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n>>K;
	n2=n>>1;
	if(!K){
		for(int i=0;i<=n2;++i) for(int j=0;j<=n2;++j) dp[0][0][i][j]=-1e9;
		dp[0][0][0][0]=0;
		for(int i=1;i<=n;++i){
			cin>>a[i][0]>>a[i][1];
			for(int j=0;j<=n2;++j) for(int k=0;k<=n2;++k) dp[0][i][j][k]=-1e9;
			dp[0][i][0][0]=max(0,dp[0][i-1][0][0]);
			for(int j=0;j<=n2;++j){
				for(int k=0;k<=n2;++k){
					if(j<n2) chmx(dp[0][i][j][k], dp[0][i-1][j+1][k]-a[i][0]+a[i][1]);
					if(k<n2) chmx(dp[0][i][j][k], dp[0][i-1][j][k+1]+a[i][0]-a[i][1]);
					if(j>0&&k==0) chmx(dp[0][i][j][k], dp[0][i-1][j-1][k]+a[i][0]);
					if(j==0&&k>0) chmx(dp[0][i][j][k], dp[0][i-1][j][k-1]+a[i][1]);
					if(j>0&&k>0) chmx(dp[0][i][j][k], dp[0][i-1][j-1][k-1]+a[i][0]+a[i][1]);
				}
			}
		}
		cout<<dp[0][n][0][0];
	}
	else{
		for(int i=1;i<=n;++i) cin>>a[i][0]>>a[i][1];
		for(int i=0;i<=n2;++i) for(int j=0;j<=n2;++j) dp[0][0][i][j]=dp[1][0][i][j]=dp[2][0][i][j]=-1e9;
		dp[0][0][0][0]=dp[1][0][0][0]=0;
		dp[0][0][0][1]=a[1][1];
		dp[1][0][1][0]=a[1][0];
		for(int i=1;i<=n;++i){
			for(int j=0;j<=n2;++j) for(int k=0;k<=n2;++k) dp[0][i][j][k]=dp[1][i][j][k]=dp[2][i][j][k]=-1e9;
			dp[0][i][0][0]=max(0,dp[0][i-1][0][0]);
			dp[1][i][0][0]=max(0,dp[1][i-1][0][0]);
			dp[2][i][0][0]=dp[2][i-1][0][0];
			for(int j=0;j<=n2;++j){
				for(int k=0;k<=n2;++k){
					if(j<n2&&i+1<n) chmx(dp[0][i][j][k], dp[0][i-1][j+1][k]-a[i][0]+a[i+1][1]);
					if(k<n2&&i+1<n) chmx(dp[0][i][j][k], dp[0][i-1][j][k+1]+a[i][0]-a[i+1][1]);
					if(j>0&&k==0&&i+1<n) chmx(dp[0][i][j][k], dp[0][i-1][j-1][k]+a[i][0]);
					if(j==0&&k>0&&i+1<n) chmx(dp[0][i][j][k], dp[0][i-1][j][k-1]+a[i+1][1]);
					if(j>0&&k>0&&i+1<n) chmx(dp[0][i][j][k], dp[0][i-1][j-1][k-1]+a[i][0]+a[i+1][1]);

					if(j<n2&&i+1<n) chmx(dp[1][i][j][k], dp[1][i-1][j+1][k]-a[i+1][0]+a[i][1]);
					if(k<n2&&i+1<n) chmx(dp[1][i][j][k], dp[1][i-1][j][k+1]+a[i+1][0]-a[i][1]);
					if(j>0&&k==0&&i+1<n) chmx(dp[1][i][j][k], dp[1][i-1][j-1][k]+a[i+1][0]);
					if(j==0&&k>0&&i+1<n) chmx(dp[1][i][j][k], dp[1][i-1][j][k-1]+a[i][1]);
					if(j>0&&k>0&&i+1<n) chmx(dp[1][i][j][k], dp[1][i-1][j-1][k-1]+a[i+1][0]+a[i][1]);

					if(j<n2) chmx(dp[2][i][j][k], dp[2][i-1][j+1][k]-a[i][0]+a[i][1]);
					if(k<n2) chmx(dp[2][i][j][k], dp[2][i-1][j][k+1]+a[i][0]-a[i][1]);
					if(j>0&&k==0) chmx(dp[2][i][j][k], dp[2][i-1][j-1][k]+a[i][0]);
					if(j==0&&k>0) chmx(dp[2][i][j][k], dp[2][i-1][j][k-1]+a[i][1]);
					if(j>0&&k>0) chmx(dp[2][i][j][k], dp[2][i-1][j-1][k-1]+a[i][0]+a[i][1]);

					if(i!=1) chmx(dp[2][i][j][k], dp[0][i-2][j][k]+a[i-1][0]-a[i][0]+a[i][1]);
					if(i!=1) chmx(dp[2][i][j][k], dp[1][i-2][j][k]+a[i-1][1]+a[i][0]-a[i][1]);
				}
			}
		}
		cout<<dp[2][n][0][0];
	}

	return 0;
}
