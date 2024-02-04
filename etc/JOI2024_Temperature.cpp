#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

vector<pair<int,ll>> adj[200005];
ll d1[200005],d2[200005];

priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
void dijk(ll d[]){
    while(pq.size()){
        auto [w,u]=pq.top();
        pq.pop();
        if(w>d[u]) continue;
        for(auto &[v,w2]:adj[u]){
            if(d[v]>w+w2){
                d[v]=w+w2;
                pq.emplace(d[v],v);
            }
        }
    }
}

struct fenwick{
    vector<ll> bit;
    void init(int n){bit=vector<ll>(n);}
    void add(int i,int x){
        for(;i<bit.size();i+=i&-i) bit[i]+=x;
    }
    ll qr(int i){
        ll ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
}fw;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m; cin>>n>>m;
    ll S,T,L,K; cin>>S>>T>>L>>K;
    for(int i=0;i<m;++i){
        int u,v,c; cin>>u>>v>>c;
        adj[u].eb(v,c),adj[v].eb(u,c);
    }
    for(int i=1;i<=n;++i) d1[i]=d2[i]=1e18;
    d1[S]=d2[T]=0;
    pq.emplace(0,S),dijk(d1);
    pq.emplace(0,T),dijk(d2);

    if(d1[T]<=K){
        cout<<(1LL*n*(n-1))/2<<endl;
        return 0;
    }
    ll ans=0;

    vector<ll> comp;
    for(int i=1;i<=n;++i) comp.eb(K-L-d1[i]);
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());

    fw.init(comp.size()+5);
    for(int i=1;i<=n;++i){
        int id=lower_bound(comp.begin(),comp.end(),d2[i])-comp.begin()+1;
        fw.add(id,1);
    }
    for(int i=1;i<=n;++i){
        int id=lower_bound(comp.begin(),comp.end(),K-L-d1[i])-comp.begin()+1;
        ans+=fw.qr(id);
    }
    cout<<ans;

}
