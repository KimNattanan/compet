#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

const ll inf=1e18;

int a[1000005],b[1000005],pos[1000005],pos2[1000005];
ll qs[1000005];
pair<ll,int> dp2[1000005];

struct line{
    ll m,c;
    int cnt;
    line(ll m,ll c,int cnt):m(m),c(c),cnt(cnt){}
    ll operator()(const ll x)const{return m*x+c;}
};
struct cht{
    deque<line> dq;
    bool check(line a,line b,line c){
        return (a.c-b.c)*(c.m-a.m)>=(a.c-c.c)*(b.m-a.m);
    }
    void insert(ll m,ll c,int cnt){
        line f(m,c,cnt);
        while(dq.size()>1&&check(dq.end()[-2],dq.back(),f)) dq.pop_back();
        dq.eb(f);
    }
    pair<ll,int> qr(ll x){
        if(dq.empty()) return {inf,0};
        while(dq.size()>1&&dq[1](x)<dq.front()(x)) dq.pop_front();
        return {dq.front()(x),dq.front().cnt};
    }
    void clear(){dq.clear();}
}dp;
void cal(int n,ll P){
    dp.clear();
    int cur=0;
    for(int i=1;i<=n;++i){
        while(cur<i&&pos2[cur+1]<=i){
            dp.insert(-cur,dp2[cur].f-qs[pos2[cur+1]-1]+1LL*pos2[cur+1]*(cur+1)-cur+P,dp2[cur].s+1);
            ++cur;
        }
        auto [val,cnt]=dp.qr(i);
        dp2[i]={val+qs[i]-i-1,cnt};
        if(cur<i) dp2[i]=min(dp2[i],{dp2[cur].f+P,dp2[cur].s+1});
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,K; cin>>n>>K;
    string s; cin>>s;
    for(int i=0,ia=0,ib=0;i<s.length();++i){
        if(s[i]=='A') a[++ia]=i;
        else b[++ib]=i;
    }
    for(int i=1,j=1;i<=n;++i){
        while(j<=n&&b[j]<a[i]) ++j;
        pos[i]=j;
        qs[i]=qs[i-1]+j;
    }
    for(int i=1,j=1;i<=n;++i){
        while(j<=n&&pos[j]<=i) ++j;
        j=max(i,j);
        pos2[i]=j;
    }
    ll l=0,r=1LL*n*n;
    while(l<r){
        ll mid=l+r>>1;
        cal(n,mid);
        if(dp2[n].s>K) l=mid+1;
        else r=mid;
    }
    cal(n,l);
    cout<<dp2[n].f-K*l<<endl;

    return 0;
}
