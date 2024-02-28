#include <bits/stdc++.h>
#include "function.h"
using namespace std;
using ll=long long;
#define f first
#define s second
#define sz(x) (int)(x).size()
#define eb emplace_back

const ll inf=LLONG_MAX>>1;

ll qs[500005],qs2[500005];
pair<ll,int> dp[500005];

struct line{
    ll m,c;
    int cnt;
    line(ll m,ll c,int cnt):m(m),c(c),cnt(cnt){}
    ll operator()(const ll &x)const{return m*x+c;}
};
struct cht{
    deque<line> dq;
    bool check(line a,line b,line c){
        ll x=(a.c-b.c)*(c.m-b.m), y=(b.c-c.c)*(b.m-a.m);
        if(x!=y) return x>y;
        return b.cnt>c.cnt;
    }
    void insert(ll m,ll c,int cnt){
        line f(m,c,cnt);
        while(sz(dq)>1&&check(dq.end()[-2],dq.back(),f)) dq.pop_back();
        dq.eb(f);
    }
    pair<ll,int> qr(ll x){
        if(dq.empty()) return{inf,0};
        while(sz(dq)>1){
            ll y1=dq.front()(x), y2=dq[1](x);
            if(y1<y2||y1==y2&&dq.front().cnt<dq[1].cnt) break;
            dq.pop_front();
        }
        return {dq.front()(x),dq.front().cnt};
    }
    void clear(){dq.clear();}
}cv;
void cal(int n,ll P){
    cv.clear();
    cv.insert(0,P,1);
    for(int i=1;i<=n;++i){
        auto [val,cnt]=cv.qr(qs[i]);
        dp[i]={val+(qs[i]*qs[i]+qs2[i]>>1),cnt};
        cv.insert(-qs[i],dp[i].f+(qs[i]*qs[i]-qs2[i]>>1)+P,cnt+1);
    }
}

long long minPenguinValue(int N, int M, std::vector<int> A){
    for(int i=1;i<=N;++i){
        qs[i]=qs[i-1]+A[i-1];
        qs2[i]=qs2[i-1]+1LL*A[i-1]*A[i-1];
    }
    ll l=0,r=qs[N]*qs[N]-qs2[N];
    while(l<r){
        ll mid=l+(r-l>>1);
        cal(N,mid);
        if(dp[N].s>M) l=mid+1;
        else r=mid;
    }
    cal(N,l);
    return dp[N].f-l*M;
}
