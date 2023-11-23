#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;

ll a[25],b[25],dp[1<<22];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    ll C; cin>>n>>C;
    for(int i=0;i<n;++i) cin>>a[i];
    for(int i=0;i<n;++i) cin>>b[i];
    dp[0]=-C;
    for(int i=1;i<(1<<n);++i){
        dp[i]=4e18;
        for(int r=n-1;r>=0;--r){
            if(!(i&(1<<r))) continue;
            int pos=__builtin_popcount(i)-1;
            ll cost=C;
            for(int l=r;l>=0;--l,--pos){
                if(!(i&(1<<l))) break;
                cost+=abs(a[l]-b[pos]);
                dp[i]=min(dp[i],dp[i^((1<<r+1)-(1<<l))]+cost);
            }
        }
    }
    cout<<dp[(1<<n)-1]<<endl;

    return 0;
}
