#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

vector<int> adj[50005];
string s;
int p0[50005];
queue<pair<int,ll>> q;
ll c[50005],c2[50005];
deque<pair<int,ll>> dq;
ll ans[50005],ans2[50005];

struct fenwick{
    vector<ll> bit;
    void init(int n){bit.assign(n,0);}
    void upd(int i,ll x){for(;i<bit.size();i+=i&-i) bit[i]+=x;}
    ll qr(int i){
        ll ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
}fwm,fwc;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,k; cin>>n>>m>>k;
    for(int i=0;i<m;++i){
        int u,v; cin>>u>>v;
        adj[u].eb(v), adj[v].eb(u);
    }
    cin>>s;
    for(auto &e:s) e-='0';
    s=" "+s;
    for(int i=1;i<=k;++i) cin>>p0[i];

    for(int i=1;i<=n;++i){
        if(s[i]){
            s[i]=2;
            c2[i]=0;
            q.emplace(i,-2);
        }
        else c2[i]=1e18;
        c[i]=1e18;
    }
    for(int i=1;i<=n;++i){
        if(!s[i]) continue;
        for(auto &v:adj[i]){
            if(s[v]){
                s[i]=s[v]=1;
                c[i]=c[v]=0;
            }
        }
    }
    for(int i=1;i<=n;++i) if(s[i]==1) dq.eb(i,-1);
    while(q.size()){
        auto [u,c]=q.front();
        q.pop();
        for(auto &v:adj[u]){
            if(c2[v]>c+1){
                c2[v]=c+1;
                q.emplace(v,c+1);
            }
        }
    }
    while(dq.size()){
        auto [u,c]=dq.front();
        dq.pop_front();
        for(auto &v:adj[u]){
            if(::c[v]>c+1){
                ::c[v]=c+1;
                if(!s[v]) dq.eb(v,c+1);
                else dq.emplace_front(v,c);
            }
        }
    }
    fwm.init(n+10), fwc.init(n+10);
    for(int i=2;i<=k;++i){
        fwm.upd(1,2), fwc.upd(1,c2[p0[i]]);
        int l=0,r=n+5;
        while(l<r){
            int mid=l+r>>1;
            if(mid+c[p0[i]]<=2*mid+c2[p0[i]]) r=mid;
            else l=mid+1;
        }
        fwm.upd(l+1,-1);
        fwc.upd(l+1,-c2[p0[i]]+c[p0[i]]);
    }

    for(int i=1;i<=n;++i) ans[i]=ans2[i]=LLONG_MAX;
    using A=tuple<ll,int,ll,int>;
    priority_queue<A,vector<A>,greater<A>> pq;
    pq.emplace(0,p0[1],0,0);
    ans[p0[1]]=ans2[p0[1]]=0;
    while(pq.size()){
        auto [d0,u,d1,t]=pq.top();
        pq.pop();
        for(auto &v:adj[u]){
            if(ans2[v]>d1+1){
                ans[v]=min(ans[v],d0+1);
                ans2[v]=d1+1;
                if(!s[v]) pq.emplace(d0+1,v,d1+1,t);
                else pq.emplace(d1+1+fwm.qr(t+2)*(t+1)+fwc.qr(t+2),v,d1+1,t+1);
            }
        }
    }

    for(int i=1;i<=n;++i) cout<<ans[i]<<endl;

    return 0;
}
