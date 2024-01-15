#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    
    int n,k; cin>>n>>k;
    int K=(1<<k);
    vector<ll> dp(K+5,4e18);
    for(int i=1;i<=n;++i){
        ll w; cin>>w;
        int m1=0;
        for(int j=0;j<k;++j){
            bool x; cin>>x;
            m1=((m1<<1)|x);
        }
        dp[m1]=min(dp[m1],w);
    }
    for(int i=K-1;i>0;--i){
        for(int j=0,m2=1;j<k;++j,m2<<=1){
            if(i&m2) dp[i^j]=min(dp[i^j],dp[i]);
        }
    }
    for(int i=1;i<K;++i){
        for(int j=(i-1)&i;j>0;j=(j-1)&i){
            dp[i]=min(dp[i],dp[j]+dp[i^j]);
        }
    }
    cout<<dp[K-1]<<endl;

    return 0;
}
