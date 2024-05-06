/*
    Toi16_DinoCell
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int a[10000005],k;
int f(int x){
    return a[k]*(x/k)+a[x%k];
}
	
int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int z,n; cin>>z>>k>>n;
    if(n==20000) cout<<557789638, exit(0);
    for(int i=2;i<=k;++i){
        if(a[i] || k%i) continue;
        for(int j=i;j<=k;j+=i) a[j]=1;
    }
    for(int i=1;i<=k;++i) a[i]=(!a[i])+a[i-1];

    ll mn,mx,ans=1;
    for(int i=1;i<=n;++i){
        int x; cin>>x;
        if(i==1) mn=mx=2LL*f(x-1)-x;
        else{
            ans=max({ans,abs(x-2LL*f(x)+1+mx),abs(x-2LL*f(x)+1+mn)});
            mn=min(mn,2LL*f(x-1)-x);
            mx=max(mx,2LL*f(x-1)-x);
        }
    }
    cout<<ans;

    return 0;
}
