#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

mt19937_64 rng(time(nullptr));
const ll p=1e9+7;

ll a[1000005];
map<ll,ll> rnd;
map<ll,int> ans;

int main(){
    ios::sync_with_stdio(false);cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    int Q; cin>>Q;
    vector<ll> query;
    for(int i=0;i<Q;++i){
        int m; cin>>m;
        vector<ll> vec(m);
        for(auto &e:vec) cin>>e;
        ll h=0;
        for(auto &e:vec){
            e=vec.back()-e;
            if(rnd.find(e)==rnd.end()) rnd[e]=rng();
            h=h*p+rnd[e];
        }
        ans[h]=0;
        query.eb(h);
    }
    for(int i=1;i<=n;++i){
        ll sum=0;
        ll p2=1;
        for(int j=i;j>=1;--j){
            ll x=a[j]-a[i];
            if(rnd.find(x)==rnd.end()) break;
            sum=sum+rnd[x]*p2;
            p2*=p;
            if(ans.find(sum)!=ans.end()) ++ans[sum];
        }
    }
    for(auto &e:query) cout<<ans[e]<<endl;

    return 0;
}
