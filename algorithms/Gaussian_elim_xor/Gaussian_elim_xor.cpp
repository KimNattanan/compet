#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back

int msb(ll x){
    return 63-__builtin_clzll(x);
}
vector<ll> vec[65];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i){
        ll x; cin>>x;
        vec[msb(x)].eb(x);
    }
    vector<ll> matrix(65);
    for(int i=62;i>0;--i){
        if(vec[i].empty()) continue;
        matrix[i]=vec[i].front();
        for(int j=1;j<vec[i].size();++j){
            ll x=vec[i][j]^vec[i][0];
            vec[msb(x)].eb(x);
        }
    }
    
    return 0;
}
