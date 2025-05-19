#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll basis[65];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i){
        ll x; cin>>x;
        for(ll i=62,j=1LL<<62;i>=0;--i,j>>=1){
            if(~x&j) continue;
            if(!basis[i]){
                basis[i]=x;
                break;
            }
            x^=basis[i];
        }
    }
    
    return 0;
}
