#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
#define f first
#define s second

ll dist[5005],P[5005],C[5005],qs[5005],qs2[5005];
ll dp[5005][5005],cost[5005][5005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m; cin>>n>>m;
    for(int i=2;i<=n;++i){
        cin>>dist[i];
        dist[i]+=dist[i-1];
    }
    for(int i=1;i<=n;++i){
        cin>>P[i];
        qs[i]=P[i]+qs[i-1];
        qs2[i]=P[i]*dist[i]+qs2[i-1];
    }
    for(int i=1;i<=n;++i) cin>>C[i];

    for(int i=3;i<=n;++i){
        int mid=i-1;
        if(dist[i]-dist[mid]<dist[mid]-dist[i-2]) --mid;
        cost[i-2][i]=qs2[mid]-qs2[i-2]-dist[i-2]*(qs[mid]-qs[i-2])+dist[i]*(qs[i]-qs[mid])-qs2[i]+qs2[mid];
        for(int j=i-3;j>=1;--j){
            while(dist[i]-dist[mid]<dist[mid]-dist[j]) --mid;
            cost[j][i]=qs2[mid]-qs2[j]-dist[j]*(qs[mid]-qs[j])+dist[i]*(qs[i]-qs[mid])-qs2[i]+qs2[mid];
        }
    }

    memset(dp,0x3f,sizeof dp);
    for(int i=1;i<=n;++i) dp[1][i]=C[i]+dist[i]*qs[i]-qs2[i];
    for(int i=2;i<=m;++i){
        int opt=i-1;
        for(int j=i;j<=n;++j){
            for(int k=opt;k<j;++k){
                if(dp[i][j]>dp[i-1][k]+C[j]+cost[k][j]) dp[i][j]=dp[i-1][k]+C[j]+cost[k][j],opt=k;
            }
        }
    }
    ll ans=LLONG_MAX;
    for(int i=m;i<=n;++i){
        ans=min(ans,dp[m][i]+qs2[n]-qs2[i]-dist[i]*(qs[n]-qs[i]));
    }
    cout<<ans<<endl;

    return 0;
}
