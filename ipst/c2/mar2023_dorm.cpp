#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

ll f(ll n,ll p){
    return (n/p)*(n/p)*(p)+2*(n/p)*(n%p)+(n%p);
}

int n,P_mx;
ll a[3005],ans0;
map<ll,int> mp;
vector<pair<ll,int>> vec;

void init(int N,std::vector<std::vector<int> > Req){
    n=N;
    for(auto &e:Req) ++a[e[0]+1],--a[e[1]+2];
    for(int i=1;i<=n;++i) a[i]+=a[i-1];
    for(int i=1;i<=n;++i) ans0+=a[i]*a[i], P_mx+=a[i]-1;
    for(int i=1;i<=n;++i){
        int cur=1;
        while(cur<a[i]){
            ll dif=f(a[i],cur+1)-f(a[i],cur);
            int l=1,r=a[i]-cur;
            while(l<r){
                int mid=l+r+1>>1;
                if(f(a[i],cur+mid)-f(a[i],cur+mid-1)==dif) l=mid;
                else r=mid-1;
            }
            mp[dif]+=l;
            cur+=l;
        }
    }
    ll x=0,y=0;
    for(auto &[val,cnt]:mp){
        vec.eb(val*cnt+x,cnt+y);
        tie(x,y)=vec.back();
    }
}
long long least_crowded(int P){
    P=min(P,P_mx);
    int l=0,r=vec.size();
    while(l<r){
        int mid=l+r>>1;
        if(vec[mid].s>P) r=mid;
        else l=mid+1;
    }
    ll ans;
    if(l==0) ans=ans0+P*(vec[0].f/vec[0].s);
    else ans=ans0+vec[l-1].f+(P-vec[l-1].s)*((vec[l].f-vec[l-1].f)/(vec[l].s-vec[l-1].s));
    return ans;
}
