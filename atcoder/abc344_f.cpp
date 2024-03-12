#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second
using ll=long long;

ll P[85][85],R[85][85],D[85][85],d[85][85][85][85];
pair<ll,ll> dp[85][85];

void cal(pair<ll,ll> &u,pair<ll,ll> &v,ll dist,ll p){
    ll cnt=dist<=u.s ? 0 : (dist-u.s+p-1)/p ;
    if(u.f+cnt<v.f) return void(v={u.f+cnt,u.s+p*cnt-dist});
    if(u.f+cnt==v.f) return void(v.s=max(v.s,u.s+p*cnt-dist));
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) cin>>P[i][j];
    for(int i=1;i<=n;++i) for(int j=1;j<n;++j) cin>>R[i][j];
    for(int i=1;i<n;++i) for(int j=1;j<=n;++j) cin>>D[i][j];

    for(int i1=1;i1<=n;++i1){
        for(int j1=1;j1<=n;++j1){
            d[i1][j1][i1][j1]=0;
            for(int i2=i1;i2<=n;++i2){
                for(int j2=j1;j2<=n;++j2){
                    if(i2==i1&&j2==j1) continue;
                    d[i1][j1][i2][j2]=LLONG_MAX;
                    if(i2>i1) d[i1][j1][i2][j2]=min(d[i1][j1][i2][j2],d[i1][j1][i2-1][j2]+D[i2-1][j2]);
                    if(j2>j1) d[i1][j1][i2][j2]=min(d[i1][j1][i2][j2],d[i1][j1][i2][j2-1]+R[i2][j2-1]);
                }
            }
        }
    }
    for(int i1=1;i1<=n;++i1){
        for(int j1=1;j1<=n;++j1){
            if(i1==1&&j1==1) continue;
            dp[i1][j1]={LLONG_MAX,0};
            for(int i2=1;i2<=i1;++i2){
                for(int j2=1;j2<=j1;++j2){
                    if(i2==i1&&j2==j1) continue;
                    cal(dp[i2][j2],dp[i1][j1],d[i2][j2][i1][j1],P[i2][j2]);
                }
            }
        }
    }
    cout<<dp[n][n].f+(n-1<<1);

    return 0;
}
