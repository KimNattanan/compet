#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
using ld=long double;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()
 
int a[2005];
bitset<4000005> dp;
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	int n,Q; cin>>n>>Q;
    ll ans=0,sum=0;
    for(int i=1;i<=n;++i) cin>>a[i], sum+=a[i];
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j) ans+=a[i]*a[j];
    }
    if(!Q) cout<<ans, exit(0);
    ll m=sum>>1;
    
	dp[0]=1;
	for(int i=1;i<=n;++i){
		dp|=(dp<<a[i]);
	}
	while(!dp[m]) --m;
	cout<<ans-m*(sum-m);
 
	return 0;
}
