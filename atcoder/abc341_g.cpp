#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using ld=long double;
#define eb emplace_back
#define sz(x) (int)(x).size()
const ld eps=1e-6;

struct line{
    ll m,c;
    line(ll m,ll c):m(m),c(c){}
    template<class T> T operator()(const T&x)const{return m*x+c;}
};
struct cht{
    deque<line> dq;
    bool check(line f1,line f2,line f3){
        return (f1.c-f2.c)*(f3.m-f2.m)>(f2.c-f3.c)*(f2.m-f1.m);
    }
    void insert(ll m,ll c){
        line f(m,c);
        while(sz(dq)>1&&check(dq.end()[-2],dq.back(),f)) dq.pop_back();
        dq.eb(f);
    }
    ld qr(ld x){
        int l=0,r=sz(dq)-1;
        while(l<r){
            int mid=l+r>>1;
            if(dq[mid](x)-dq[mid+1](x)>eps) r=mid;
            else l=mid+1;
        }
        return dq[l](x);
    }
}cv;

ll qs[200005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i) cin>>qs[i], qs[i]+=qs[i-1];
    vector<ld> ans(n);
    for(int i=n-1;i>=0;--i){
        cv.insert(-i-1,qs[i+1]);
        ld l=qs[i+1]-qs[i],r=1e6;
        while(r-l>eps){
            ld mid=(l+r)/2;
            if(cv.qr(mid)-qs[i]+i*mid>eps) l=mid;
            else r=mid;
        }
        ans[i]=l;
    }
    for(auto &e:ans) cout<<fixed<<setprecision(8)<<e<<endl;

    return 0;
}
/*
(-r)*(mid)+qs[r]>=qs[k]-mid*k
*/
