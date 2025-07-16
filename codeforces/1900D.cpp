#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int phi[100005],cnt[100005];
vector<int> fac[100005];
 
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    for(int i=1;i<=100000;++i) phi[i]=i;
    for(int i=1;i<=100000;++i){
        for(int j=i<<1;j<=100000;j+=i) phi[j]-=phi[i];
    }
    for(int i=1;i<=100000;++i){
        for(int j=i;j<=100000;j+=i) fac[j].emplace_back(i);
    }
 
    int Q; cin>>Q;
    while(Q--){
        int n; cin>>n;
        vector<int> vec(n);
        for(auto &e:vec) cin>>e;
        sort(vec.begin(),vec.end());
        ll ans=0;
        for(int i=1;i<=100000;++i) cnt[i]=0;
        for(int i=0;i<n;++i){
            for(auto &e:fac[vec[i]]) ans+=1LL*phi[e]*cnt[e]*(n-i-1);
            for(auto &e:fac[vec[i]]) ++cnt[e];
        }
        cout<<ans<<'\n';
    }
 
    return 0;
}
