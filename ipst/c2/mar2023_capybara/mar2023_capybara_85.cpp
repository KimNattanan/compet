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
struct interval{
    vector<interval> c;
    int l,r,mid;
    template<bool T>
    struct cmp{
        bool operator()(const int &l,const int &r)const{
            if(!T){
                if(L[l]!=L[r]) return L[l]<L[r];
                if(R[l]!=R[r]) return R[l]<R[r];
            }
            else{
                if(R[l]!=R[r]) return R[l]>R[r];
                if(L[l]!=L[r]) return L[l]>L[r];
            }
            return l<r;
        }
    };
    vector<int> sl,sr;
    interval(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)){}
    void build(){
        if(l==r) return;
        c.eb(l,mid),c.eb(mid+1,r);
        c[0].build(),c[1].build();
    }
    void upd(int i){
        if(L[i]<=mid&&R[i]>=mid){
            sl.eb(i),sr.eb(i);
            return;
        }
        if(R[i]<mid) c[0].upd(i);
        else c[1].upd(i);
    }
    void sort(){
        std::sort(sl.begin(),sl.end(),cmp<0>()),std::sort(sr.begin(),sr.end(),cmp<1>());
        if(l!=r) c[0].sort(),c[1].sort();
    }
    ll qr(int x,int a){
        ll ans=4e18;
        if(x<mid){
            for(auto &e:sl){
                if(L[e]>x) break;
                ll w=abs(qs[a]-qs[e]);
                ans=min(ans,abs(qs[a]-qs[e]));
            }
            return min(ans,c[0].qr(x,a));
        }
        else if(x>mid){
            for(auto &e:sr){
                if(R[e]<x) break;
                ans=min(ans,abs(qs[a]-qs[e]));
            }
            return min(ans,c[1].qr(x,a));
        }
        for(auto &e:sl) ans=min(ans,abs(qs[a]-qs[e]));
        return ans;
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
    t=interval(1,N);
    t.build();
    for(int i=1;i<=N;++i) t.upd(i);
    t.sort();

    return;
}

long long travel(int A,int B){
    ++A,++B;
    if(L[A]<=B&&R[A]>=B) return M[A];
    return t.qr(B,A);
}
