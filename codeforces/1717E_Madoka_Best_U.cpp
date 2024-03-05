#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const ll md=1e9+7;

int phi[100005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    for(int i=1;i<100005;++i) phi[i]=i;
    for(int i=1;i<100005;++i){
        for(int j=i<<1;j<100005;j+=i) phi[j]-=phi[i];
    }

    int n; cin>>n;
    ll ans=0;
    for(int i=1;i<=n-2;++i){
        for(int g=1;g*g<=n-i;++g){
            if((n-i)%g==0){
                ans=(ans+1LL*lcm(i,g)*phi[(n-i)/g])%md;
                if(g!=1&&g*g!=n-i) ans=(ans+1LL*lcm(i,(n-i)/g)*phi[g])%md;
            }
        }
    }
    cout<<ans;

    return 0;
}
