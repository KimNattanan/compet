#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()

const ll inf=LLONG_MAX>>1;
const int MN=-1e5,MX=1e5;

struct line{
    ll m,c;
    line(ll m=0,ll c=-inf):m(m),c(c){}
    ll operator()(const ll &x){return m*x+c;}
};
struct lichao{
    line f[200005];
    void upd(int i,int l,int r,line f2){
        if(l+1==r) return void(f[i]=(f[i](l)>f2(l)?f[i]:f2));
        int mid=l+r>>1;
        if(f[i].m>f2.m) swap(f[i],f2);
        if(f[i](mid)<f2(mid)){
            swap(f[i],f2);
            upd(i<<1,l,mid,f2);
        }
        else upd(i<<1|1,mid,r,f2);
    }
    void upd(ll m,ll c){upd(1,MN,MX+1,line(m,c));}
    ll qr(int i,int l,int r,int x){
        if(l+1==r) return f[i](x);
        int mid=l+r>>1;
        if(x<mid) return max(f[i](x),qr(i<<1,l,mid,x));
        else return max(f[i](x),qr(i<<1|1,mid,r,x));
    }
    ll qr(int x){return qr(1,MN,MX+1,x);}
};
