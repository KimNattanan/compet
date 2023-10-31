#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define f first
#define s second
#define ll long long

const int inf=1e9+7;

int a[3005];
int dp[3005][3005];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,k; cin>>n>>k;
    for(int i=1;i<=n;++i) cin>>a[i];
    memset(dp,0x3f,sizeof dp);
    int ans=inf;
    for(int i=1;i<k;++i) dp[i][0]=a[i];
    for(int i=2;i<=n;++i){
        for(int j=i-1;j>0&&j>i-k;--j){
            dp[i][j]=min(dp[i][j+1],dp[j][max(0,i-k)]+a[i]);
        }
        if(i>n-k+1) ans=min(ans,dp[i][n-k+1]);
    }
    cout<<ans<<endl;

    return 0;
}
/*
6 4
1 9 1 1 9 1
*/
