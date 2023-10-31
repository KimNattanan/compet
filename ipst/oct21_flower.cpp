#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define f first
#define s second
#define ll long long

const int inf=1e9+7;

int a[2][105],val[2][105];
int dp[2][105][105][105],N[2];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int W,n; cin>>W>>n;
    int n0=0,n1=0;
    for(int i=1;i<=n;++i){
        int w,x,z; cin>>w>>x>>z;
        a[z][++N[z]]=w;
        val[z][N[z]]=x;
    }
    for(int z=0;z<2;++z){
        for(int i=1;i<=N[z];++i){
            for(int j=1;j<=i;++j){
                dp[z][i][j][0]=-inf;
                for(int k=1;k<=W;++k){
                    dp[z][i][j][k]=dp[z][i][j][k-1];
                    if(j<i) dp[z][i][j][k]=max(dp[z][i][j][k],dp[z][i-1][j][k]);
                    if(k>=a[z][i]){
                        dp[z][i][j][k]=max(dp[z][i][j][k],dp[z][i-1][j-1][k-a[z][i]]+val[z][i]);
                    }
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=N[0];++i){
        for(int j=0;j<=N[1];++j){
            if((max(i,j)-1>>1)>min(i,j)) continue;
            for(int k=0;k<=W;++k){
                ans=max(ans,dp[0][N[0]][i][k]+dp[1][N[1]][j][W-k]);
            }
        }
    }
    cout<<ans<<endl;

    return 0;
}
/*
100 6 
40 1000 1 
20 100 1 
10 200 0 
20 300 0
30 400 0
30 400 0
*/
