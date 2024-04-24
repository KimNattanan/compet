/*
    cnc_pre19_busan
*/
#include<bits/stdc++.h>
using namespace std;

int L[2005],R[2005],dpL[2][2005][3005],dpR[2][2005][3005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,s; cin>>n>>m>>s;
    for(int i=1;i<=n;++i) cin>>L[i];
    for(int i=1;i<=n;++i) cin>>R[i];
    for(int i=1;i<=n;++i){
        int w0=max(0,-L[i]), v0=max(0,R[i]);
        int w1=max(0,-R[i]), v1=max(0,L[i]);
        for(int j=0;j<=m;++j){
            dpL[0][i][j]=dpL[0][i-1][j];
            if(j>0) dpL[0][i][j]=max(dpL[0][i][j],dpL[0][i][j-1]);
            if(j>=w0) dpL[0][i][j]=max(dpL[0][i][j],dpL[0][i-1][j-w0]+v0);
            dpL[1][i][j]=dpL[1][i-1][j];
            if(j>0) dpL[1][i][j]=max(dpL[1][i][j],dpL[1][i][j-1]);
            if(j>=w1) dpL[1][i][j]=max(dpL[1][i][j],dpL[1][i-1][j-w1]+v1);
        }
    }
    for(int i=n;i>=1;--i){
        int w0=max(0,-L[i]), v0=max(0,R[i]);
        int w1=max(0,-R[i]), v1=max(0,L[i]);
        for(int j=0;j<=m;++j){
            dpR[0][i][j]=dpR[0][i+1][j];
            if(j>0) dpR[0][i][j]=max(dpR[0][i][j],dpR[0][i][j-1]);
            if(j>=w0) dpR[0][i][j]=max(dpR[0][i][j],dpR[0][i+1][j-w0]+v0);
            dpR[1][i][j]=dpR[1][i+1][j];
            if(j>0) dpR[1][i][j]=max(dpR[1][i][j],dpR[1][i][j-1]);
            if(j>=w1) dpR[1][i][j]=max(dpR[1][i][j],dpR[1][i+1][j-w1]+v1);
        }
    }
    int ans=dpL[0][n][m]+dpL[1][n][m];
    if(s==1){
        for(int i=1;i<n;++i){
            int mx0=0, mx1=0;
            for(int j=0;j<=m;++j){
                mx0=max(mx0,dpL[0][i][j]+dpR[1][i+1][m-j]);
                mx1=max(mx1,dpL[1][i][j]+dpR[0][i+1][m-j]);
            }
            ans=max(ans,mx0+mx1);
        }
    }
    cout<<ans;

    return 0;
}
