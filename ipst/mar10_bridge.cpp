#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;

int lm[100005],dp[100005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    
    int L,n,m; cin>>L>>n>>m;
    vector<pii> v1(n);
    vector<int> v2(m+2);
    for(auto &[l,r]:v1) cin>>l>>r;
    for(int i=1;i<=m;++i) cin>>v2[i];
    v2[m+1]=L;
    sort(v1.begin(),v1.end());
    int id(1);
    for(auto &[l,r]:v1){
            l=lower_bound(v2.begin(),v2.end(),l)-v2.begin();
            r=upper_bound(v2.begin(),v2.end(),r)-v2.begin()-1;
            if(r<=l) continue;
            for(;id<=r;++id) lm[id]=l;
    }
    for(int i=1;i<=m+1;++i) dp[i]=dp[lm[i]]+2;
    cout<<dp[m+1]-1;
    
}
