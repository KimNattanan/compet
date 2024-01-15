#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
#define f first
#define s second

const ll inf=1e18;

ll a[500005],dp[2][500005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,K; cin>>n>>K;
    for(int i=1;i<=n;++i) cin>>a[i],dp[1][i]=max(dp[1][i-1],a[i]);
    for(int k=2;k<=K;++k){
        int now=k&1,prev=!now;
        stack<pair<int,ll>> st;
        for(int i=2;i<=n;++i){
            ll mn=dp[prev][i-1];
            while(st.size()&&a[st.top().f]<=a[i]) mn=min(mn,st.top().s),st.pop();
            dp[now][i]=mn+a[i];
            if(st.size()) dp[now][i]=min(dp[now][i],dp[now][st.top().f]);
            st.emplace(i,mn);
        }
        for(int i=0;i<k;++i) dp[now][i]=inf;
    }
    cout<<dp[K&1][n];

    return 0;

}
