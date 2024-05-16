#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll b[105][1005],s[105][1005],mx[105][105],d[105][105],d2[105][105];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,K; cin>>n>>m>>K;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=K;++j){
            cin>>b[i][j]>>s[i][j];
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            for(int k=1;k<=K;++k){
                if(b[i][k]!=-1 && s[j][k]!=-1) mx[i][j]=max(mx[i][j],-b[i][k]+s[j][k]);
            }
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j) d[i][j]=1e18;
        d[i][i]=0;
    }
    for(int i=0,u,v,w;i<m;++i) cin>>u>>v>>w, d[u][v]=min(d[u][v],(ll)w);
    for(int k=1;k<=n;++k) for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    int l=0,r=1e9;
    while(l<r){
        int mid=l+r+1>>1;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j) d2[i][j]=-mx[i][j]+mid*min(ll(1e18)/mid,d[i][j]);
            d2[i][i]=1e18;
        }
        for(int k=1;k<=n;++k) for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) d2[i][j]=min(d2[i][j],d2[i][k]+d2[k][j]);
        bool ok=0;
        for(int i=1;i<=n&&!ok;++i) if(d2[i][i]<=0) ok=1;
        if(ok) l=mid;
        else r=mid-1;
    }
    cout<<l;

    return 0;
}
