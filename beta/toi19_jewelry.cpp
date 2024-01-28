#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

int rm[1000005];
ll dp[1000005];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    string s; cin>>s;
    s=" "+s;
    ll ans=0;
    for(int i=1,j=0;i<=n;++i){
        if(s[i]=='F') dp[i]=dp[j],ans+=dp[j];
        else{
            j=i;
            while(j<n&&s[j+1]=='T') ++j;
            for(int k=i;k<=j;++k){
                int len=k-i+1;
                ans+=1LL*len*(len+1)>>1;
                ans+=1LL*len*(i-rm[len]-1)+dp[rm[len]];
            }
            int len=j-i+1;
            dp[i]=1LL*len*(i-rm[len])+dp[rm[len]];
            for(int k=i+1;k<=j;++k) dp[k]=dp[k-1]+(j-k+1);
            for(int k=j,len=1;k>=i;--k,++len) rm[len]=k;
            i=j;
        }
    }
    cout<<ans;

    return 0;
}
