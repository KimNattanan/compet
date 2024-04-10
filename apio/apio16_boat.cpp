#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back

const ll md=1e9+7;

vector<int> comp;
int a[505],b[505];
ll dp[505][1005],inv[505],C[505][505],f[1005][505],g[1005][505];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i]>>b[i];
        comp.eb(--a[i]), comp.eb(b[i]);
    }
    comp.eb(0);
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());

    C[0][0]=1;
    for(int i=1;i<=n;++i){
        inv[i]=1;
        ll a=i,b=md-2;
        for(;b>0;b>>=1,a=(a*a)%md) if(b&1) inv[i]=(inv[i]*a)%md;
        C[i][0]=1;
        for(int j=1;j<=n;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%md;
    }
    for(int i=1;i<comp.size();++i){
        int cur=comp[i]-comp[i-1];
        f[i][1]=cur--;
        for(int j=2;j<=n&&cur>0;++j) f[i][j]=((((f[i][j-1]*(cur--))%md)*inv[j])%md+md)%md;
        for(int j=1;j<=n;++j){
            int m=min(j,comp[i]-comp[i-1]);
            for(int k=1;k<=m;++k) g[i][j]=(g[i][j]+f[i][k]*C[j-1][k-1])%md;
        }
    }

    ll ans=0;
    for(int i=1;i<=n;++i){
        a[i]=lower_bound(comp.begin(),comp.end(),a[i])-comp.begin();
        b[i]=lower_bound(comp.begin(),comp.end(),b[i])-comp.begin();
    
        for(int j=a[i]+1;j<=b[i];++j){
            int cnt=1;
            for(int k=i-1;k>0;--k){
                if(a[k]<j-1) dp[i][j]=(dp[i][j]+dp[k][min(b[k],j-1)]*g[j][cnt])%md;
                if(a[k]<j&&j<=b[k]) ++cnt;
            }
            dp[i][j]=(dp[i][j]+dp[i][j-1]+g[j][cnt])%md;
        }
        ans=(ans+dp[i][b[i]])%md;
    }
    cout<<ans;

    return 0;
}
/*

f[j][1]*C[cnt-1][1-1] + f[j][2]*C[cnt-1][2-1] + f[j][3]*C[cnt-1][3-1] + ... + f[j][min(m,cnt)]*C[cnt-1][min(m,cnt)-1]

f[1][1]*C[1][0]+f[1][2]*C[1][1]

*/
