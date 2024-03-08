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
    line(ll m=0,ll c=inf):m(m),c(c){}
    ll operator()(const ll &x){return m*x+c;}
    bool operator==(const line &o)const{return m==o.m&&c==o.c;}
};
struct lichao{
    line f[1<<19];
    void insert(int i,int l,int r,line f2){
        if(l+1==r) return void(f[i]=(f[i](l)>f2(l)?f[i]:f2));
        int mid=l+r>>1;
        if(f[i].m>f2.m) swap(f[i],f2);
        if(f[i](mid)<f2(mid)) insert(i<<1,l,mid,f2);
        else{
            swap(f[i],f2);
            insert(i<<1|1,mid,r,f2);
        }
    }
    void insert(ll m,ll c){insert(1,MN,MX+1,line(m,c));}
    void insert(line f2){insert(1,MN,MX+1,f2);}
    ll qr(int i,int l,int r,int x){
        if(l+1==r) return f[i](x);
        int mid=l+r>>1;
        if(x<mid) return min(f[i](x),qr(2*i,l,mid,x));
        else return min(f[i](x),qr(2*i+1,mid,r,x));
    }
    ll qr(int x){return qr(1,MN,MX+1,x);}
    void clear(int i,int l,int r){
        if(f[i]==line()) return;
        f[i]=line();
        if(l+1==r) return;
        int mid=l+r>>1;
        clear(i<<1,l,mid), clear(i<<1|1,mid,r);
    }
    void clear(){clear(1,MN,MX+1);}
}t;
