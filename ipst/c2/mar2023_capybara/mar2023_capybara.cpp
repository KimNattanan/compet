#include "capybara.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

int N,M[200005];
ll qs[200005];
int L[200005],R[200005];

struct AL{
    vector<AL> c;
    int l,r,mid,mn;
    AL(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)),mn(1e9){}
    void build(){
        if(l==r) return void(mn=l);
        c.eb(l,mid),c.eb(mid+1,r);
        c[0].build(),c[1].build();
        mn=l;
    }
    void upd(int i,int x){
        if(l==r) return void(mn=x);
        if(i<=mid) c[0].upd(i,x);
        else c[1].upd(i,x);
        mn=min(c[0].mn,c[1].mn);
    }
    int qr(int l0,int r0){
        if(l0<=l&&r<=r0) return mn;
        if(l>r0||r<l0) return 1e9;
        return min(c[0].qr(l0,r0),c[1].qr(l0,r0));
    }
}tl;
struct AR{
    vector<AR> c;
    int l,r,mid,mx;
    AR(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)),mx(0){}
    void build(){
        if(l==r) return void(mx=l);
        c.eb(l,mid),c.eb(mid+1,r);
        c[0].build(),c[1].build();
        mx=r;
    }
    void upd(int i,int x){
        if(l==r) return void(mx=x);
        if(i<=mid) c[0].upd(i,x);
        else c[1].upd(i,x);
        mx=max(c[0].mx,c[1].mx);
    }
    int qr(int l0,int r0){
        if(l0<=l&&r<=r0) return mx;
        if(l>r0||r<l0) return 0;
        return max(c[0].qr(l0,r0),c[1].qr(l0,r0));
    }
}tr;
struct segment{
    vector<segment> c;
    int l,r,mid;
    vector<int> vec;
    segment(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)){}
    void build(){
        if(l==r) return;
        c.eb(l,mid),c.eb(mid+1,r);
        c[0].build(),c[1].build();
    }
    void upd(int i){
        if(L[i]<=l&&r<=R[i]) return void(vec.eb(i));
        if(R[i]<l||L[i]>r) return;
        c[0].upd(i),c[1].upd(i);
    }
    ll qr(int x,int a){
        int id1=upper_bound(vec.begin(),vec.end(),a)-vec.begin();
        int id0=id1-1;
        ll ans=LLONG_MAX;
        if(id1<vec.size()) ans=min(ans,qs[vec[id1]]-qs[a]); 
        if(id0>=0) ans=min(ans,qs[a]-qs[vec[id0]]);
        if(l==r) return ans;
        if(x<=mid) return min(ans,c[0].qr(x,a));
        return min(ans,c[1].qr(x,a));
    }
}t;

void play(int i){
    R[i]=upper_bound(qs+i,qs+N+1,qs[i]+M[i])-qs-1;
    L[i]=lower_bound(qs+1,qs+i+1,qs[i]-M[i])-qs;
    while(1){
        int l=tl.qr(L[i],R[i]),r=tr.qr(L[i],R[i]);
        if(l==L[i]&&r==R[i]) break;
        L[i]=l,R[i]=r;
    }
    tl.upd(i,L[i]),tr.upd(i,R[i]);
}

void capybara(int N, int Q, std::vector<int> M_, std::vector<int> K){
    ::N=N;
    M[1]=M_[0];
    for(int i=2;i<=N;++i) M[i]=M_[i-1],qs[i]=qs[i-1]+K[i-2];
    tl=AL(1,N),tl.build();
    tr=AR(1,N),tr.build();
    for(int i=1;i<=N;++i) play(i);
    for(int i=N;i>=1;--i) play(i);
    t=segment(1,N),t.build();
    for(int i=1;i<=N;++i) t.upd(i);

    return;
}

long long travel(int A,int B){
    ++A,++B;
    if(L[A]<=B&&R[A]>=B) return M[A];
    return t.qr(B,A);
}
