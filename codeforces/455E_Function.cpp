#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using ld=long double;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()
const ld EPS=1e-8;

using ti3=tuple<int,int,int>;

struct line{
    ll m,c;
    line(ll m=0,ll c=0):m(m),c(c){}
    ll operator()(const ll &x)const{return m*x+c;}
};
struct cht{
    deque<pair<line,int>> dq;
    bool check(line f1,line f2,line f3){
        return (f1.c-f2.c)*(f3.m-f2.m)>=(f2.c-f3.c)*(f2.m-f1.m);
    }
    void insert(ll m,ll c,int id){
        line f(m,c);
        while(sz(dq)&&-dq.back().f.m>=-f.m) dq.pop_back();
        while(sz(dq)>1&&check(dq.end()[-2].f,dq.back().f,f)) dq.pop_back();
        dq.eb(f,id);
    }
    ll qr(ll x){
        int l=0,r=sz(dq)-1;
        while(l<r){
            int mid=l+r>>1;
            if(dq[mid].s<=x || dq[mid].f(x)>=dq[mid+1].f(x)) l=mid+1;
            else r=mid;
        }
        return dq[l].f(x);
    }
}cv;
ll a[100005],qs[100005],ans[100005];
vector<pii> query[100005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i], qs[i]=a[i]+qs[i-1];
    int Q; cin>>Q;
    for(int i=0,x,y;i<Q;++i) cin>>x>>y, query[y].eb(x,i);

    for(int i=1;i<=n;++i){
        cv.insert(-a[i],a[i]*i-qs[i],i);
        for(auto &[x,id]:query[i]) ans[id]=cv.qr(i-x)+qs[i];
    }
    for(int i=0;i<Q;++i) cout<<ans[i]<<endl;

}
/*

-a[i]*(y-x)+a[i]*i-qs[i] +qs[y]     y-x+1 <= i <= y

*/
