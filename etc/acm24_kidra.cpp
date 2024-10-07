#include<bits/stdc++.h>
using namespace std;

int a[10],b[1005][1005],c[1005],dp[9005];

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int n,m;
  cin>>n>>m;
  memset(dp,~0x3f,sizeof dp);
  int _,ans=0;
  for(int i=1;i<=m;i++){
    int x;
    cin>>x;
    if(i==1) _=x;
    else if(i==m) dp[x]=_;
  }
  for(int i=2;i<=n;i++) for(int j=1;j<=m;j++) cin>>b[i][j];
  for(int i=n;i>=2;i--) c[i]=c[i+1]+*max_element(b[i]+1,b[i]+1+m);
  for(int i=2;i<=n;i++){
    int mx=-1e9;
    for(int j=0;j<=9;j++) a[j]=-1e9;
    for(int j=1;j<=m;j++){
      a[b[i][j]]=mx;
      mx=max(mx,b[i][j]);
    }
    for(int j=9*i;j>=0;j--){
      if(dp[j]>0) ans=max(ans,dp[j]*j+max(j,dp[j])*c[i]);
      for(int k=0;k<=min(9,j);k++) dp[j]=max(dp[j],dp[j-k]+a[k]);
    }
  }
  for(int i=0;i<=9000;i++){
    if(dp[i]>0) ans=max(ans,i*dp[i]);
  }
  cout<<ans;
}
