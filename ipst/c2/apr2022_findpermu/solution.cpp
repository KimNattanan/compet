#include "inversion.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define eb emplace_back
#define sz(x) (int)(x).size()
using pii=pair<int,int>;
#define f first
#define s second

struct fenwick{
    vector<int> bit;
    fenwick(int n=0){init(n);}
    void init(int n){bit.assign(n,0);}
    void upd(int i,int x){
        for(;i<sz(bit);i+=i&-i) bit[i]+=x;
    }
    int qr(int i){
        int ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
    int lower_bound(int x){
        int pos=0,sum=0;
        for(int i=1<<31-__builtin_clz(sz(bit)-1);i>0;i>>=1){
            if(pos+i<sz(bit)&&sum+bit[pos+i]<x) pos+=i,sum+=bit[pos];
        }
        return pos+1;
    }
};

vector<int> find_permutation(int N,long long V){
    int mid=N>>1;
    int l=mid-1,r=mid;

    vector<pii> L,R;

    for(int i=1;i<N;++i){
        ll x=swap_and_report(l,r)-V;
        ll x2=abs(x)-1>>1;
        V+=x;
        if(i&1){
            if(x>0) L.eb(x2,l);
            else R.eb(x2,l);
            ++r;
        }
        else{
            if(x<0) L.eb(x2,r);
            else R.eb(x2,r);
            --l;
        }
    }

    vector<int> vL(sz(L)),vR(sz(R)),ans(N);
    
    fenwick fwL(sz(L)+5);
    for(int i=1;i<=sz(L);++i) fwL.upd(i,1);
    for(int i=sz(L)-1;i>=0;--i){
        int id=fwL.lower_bound(L[i].f+1);
        fwL.upd(id,-1);
        vL[id-1]=L[i].s;
    }
    fenwick fwR(sz(R)+5);
    for(int i=1;i<=sz(R);++i) fwR.upd(i,1);
    for(int i=sz(R)-1;i>=0;--i){
        int id=fwR.lower_bound(R[i].f+1);
        fwR.upd(id,-1);
        vR[id-1]=R[i].s;
    }

    reverse(vL.begin(),vL.end());
    vL.eb(mid);
    for(auto &e:vR) vL.eb(e);
    for(int i=0;i<N;++i) ans[vL[i]]=i+1;

    return ans;
}
