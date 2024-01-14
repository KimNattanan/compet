#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

int P[200005];
pii big[200005];
vector<int> adj[200005];
ll ans[200005],sum[200005];
set<ll> s[200005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m; cin>>n>>m;
    for(int i=2;i<=n;++i){
        cin>>P[i];
        adj[P[i]].eb(i);
    }
    for(int i=1;i<=n;++i){
        ll x; cin>>x;
        s[i].insert(x);
        sum[i]=x;
    }
    for(int i=n;i>=1;--i){
        if(big[i].s) swap(sum[i],sum[big[i].s]),swap(s[i],s[big[i].s]);
        for(auto &v:adj[i]){
            for(auto &e:s[v]){
                auto itr=s[i].lower_bound(e);
                if(*itr==e) continue;
                s[i].insert(itr,e);
                sum[i]+=e;
            }
        }
        ans[i]=sum[i];
        big[P[i]]=max(big[P[i]],pii(s[i].size(),i));
    }
    while(m--){
        int x; cin>>x;
        cout<<ans[x]<<endl;
    }

    return 0;
}
