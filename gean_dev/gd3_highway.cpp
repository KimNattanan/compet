#include "highway.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using node = array<ll,7>;

vector<ll> A,B,C;
struct segment{
    node t[1<<18];
    node cal(int i){
        return {min(A[i],B[i]+C[i]),B[i]+C[i],min(A[i],B[i]),B[i],A[i],B[i],A[i]+B[i]+C[i]};
    }
    node cal(node &tl,node &tr){
        return {
            min(min(tl[0],tl[4])+min({tr[0],tr[1],tr[4]}),tl[1]+min({tr[0],tr[1],tr[2],tr[3],tr[4],tr[5]})),
            min(min(tl[0],tl[4])+tr[1],tl[1]+min({tr[1],tr[3],tr[5]})),
            min(min(tl[3],tl[5])+min({tr[0],tr[1],tr[2],tr[3],tr[4],tr[5]}),tl[2]+min({tr[0],tr[1],tr[4]})),
            min(min(tl[3],tl[5])+min({tr[1],tr[3],tr[5]}),tl[2]+tr[1]),
            tl[4]+tr[4],
            tl[5]+tr[5],
            min(tr[6],tl[6]+tr[4]+tr[5])
        };
    }
    void build(int i,int il,int ir){
        if(il==ir) return void(t[i]=cal(il));
        int mid=il+ir>>1;
        build(i<<1,il,mid), build(i<<1|1,mid+1,ir);
        t[i]=cal(t[i<<1],t[i<<1|1]);
    }
    void build(){ build(1,0,(int)A.size()-1); }
    void upd(int i,int il,int ir,int id){
        if(il==ir) return void(t[i]=cal(il));
        int mid=il+ir>>1;
        if(id<=mid) upd(i<<1,il,mid,id);
        else upd(i<<1|1,mid+1,ir,id);
        t[i]=cal(t[i<<1],t[i<<1|1]);
    }
    void upd(int id){ upd(1,0,(int)A.size()-1,id); }
    node qr(int i,int il,int ir,int l,int r){
        if(il>r||ir<l) return {-1,0,0,0,0,0,(ll)1e18};
        if(l<=il&&ir<=r) return t[i];
        int mid=il+ir>>1;
        node tl=qr(i<<1,il,mid,l,r), tr=qr(i<<1|1,mid+1,ir,l,r);
        if(tl[0]==-1) return tr;
        if(tr[0]==-1) return tl;
        return cal(tl,tr);
    }
    node qr(int l,int r){ return qr(1,0,(int)A.size()-1,l,r); }
}t;

void init(int N, int Q, std::vector<int> A, std::vector<int> B, std::vector<int> C) {
    ::A.resize(A.size()), ::B.resize(B.size()), ::C.resize(C.size());
    for(int i=0;i<N-1;++i) ::A[i]=A[i],::B[i]=B[i],::C[i]=C[i];
    ::C[N-1]=C[N-1];
    t.build();
}

void update(int X, int Y, int Z) {
    A[X]=Y, B[X]=Z;
    t.upd(X);
}

long long query(int S, int T) {
    node y=t.qr(S,T-1);
    ll x=min((ll)C[S],t.qr(0,S-1)[6]);
    return min({y[0],y[1],x+y[2],x+y[3],y[4],x+y[5]});
}
