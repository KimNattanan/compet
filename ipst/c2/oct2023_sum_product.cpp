#include "sum_product.h"
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back

const int inf=1e9+7;
const int md=1e9+7;

int n;
ll dp[100005],f[100005],cnt0[100005],dp2[100005],dp0[100005];

ll Pow(ll a,ll b){
    ll ans=1;
    while(b>0){
        if(b&1) ans=(ans*a)%md;
        a=(a*a)%md;
        b>>=1;
    }
    return ans;
}

int sum_product(int n, std::vector<int> a){
    ::n=n;

    dp[1]=a[0];
    f[0]=1;
    for(int i=1;i<=n;++i) f[i]=(f[i-1]*a[i-1])%md;

    dp0[0]=0;
    cnt0[0]=1;
    dp2[0]=1;
    dp0[1]=a[0];
    cnt0[1]=2;
    dp2[1]=(1+Pow(a[0],md-2))%md;

    for(int i=2;i<=n;++i){
        dp[i]=(dp0[i-1]+(f[i]*dp2[i-1])%md)%md;

        cnt0[i]=(cnt0[i-1]<<1)%md;
        dp0[i]=(dp0[i-1]+dp[i])%md;

        dp2[i]=(dp2[i-1]+( (cnt0[i-1]*Pow(f[i],md-2))%md+md )%md)%md;
    }

    return dp[n];
}








//
////#include "sum_product.h"
//#include <cassert>
//#include <iostream>
//#include <vector>
//using namespace std;
//
//int main(){
//    int n;
//    cin >> n;
//    vector<int> a(n);
//    for(int i=0; i<n; ++i){
//        cin >> a[i];
//    }
//    cout << sum_product(n, a) << "\n";
//}
