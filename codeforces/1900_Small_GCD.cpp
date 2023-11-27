#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

ll cnt[100005],qs[100005],dp[100005];

void mian(){

    int n,m=0; cin>>n;
    for(int i=1;i<=n;++i){
        int x; cin>>x;
        ++cnt[x];
        m=max(m,x);
    }
    ll ans=0;
    for(ll i=m;i>0;--i){
        qs[i]=qs[i+1]+cnt[i];
        if(cnt[i]>2) dp[i]+=cnt[i]*(cnt[i]-1)*(cnt[i]-2)/6;
        if(cnt[i]>1) dp[i]+=(cnt[i]*(cnt[i]-1)*qs[i+1])>>1;
        ll sum=cnt[i];
        for(ll j=(i<<1);j<=m;j+=i){
            dp[i]+=(cnt[j]*sum*qs[j+1])+((cnt[j]*(cnt[j]-1)*sum)>>1)+((cnt[j]*(cnt[j]-1)*qs[j+1])>>1)+(cnt[j]*(cnt[j]-1)*(cnt[j]-2))/6;
            dp[i]-=dp[j];
            sum+=cnt[j];
        }
        ans+=dp[i]*i;
    }
    cout<<ans<<endl;
    for(int i=0;i<=m;++i) cnt[i]=qs[i]=dp[i]=0;

}













int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
    while(Q--){
        mian();
    }

    return 0;
}
