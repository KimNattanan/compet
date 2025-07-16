#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
 
const ll md=998244353;
 
int a[300005];
 
void solve(){
 
    int n; cin>>n;
    vector<int> lm(n+5);
    vector<ll> dp(n+5),dp2(n+5),qs(n+5);
    stack<pii> st;
    st.emplace(0,0);
    for(int i=1;i<=n;++i){
        cin>>a[i];
        while(st.top().s>a[i]) st.pop();
        lm[i]=st.top().f;
        st.emplace(i,a[i]);
    }
    dp[1]=dp2[1]=qs[1]=1;
    for(int i=2;i<=n;++i){
        dp2[i]=(qs[i-1]-qs[lm[i]]+md)%md;
        if(lm[i]>0) dp2[i]=(dp2[i]+dp[lm[i]])%md;
        else dp2[i]=(dp2[i]+1)%md;
        qs[i]=(qs[i-1]+dp2[i])%md;
        dp[i]=(dp2[i]+dp[lm[i]])%md;
    }
    cout<<dp[n]<<endl;
 
}
/*
2 1
2 4 1
1
*/
 
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    int Q(1);
    cin>>Q;
    while(Q--){
        solve();
    }
 
    return 0;
}