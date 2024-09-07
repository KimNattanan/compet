#include "coin.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

struct segment{
    int mx[1<<19],lz[1<<19],l0,r0;
    void build(int l,int r){ l0=l,r0=r; }
    void flush(int i,int il,int ir){
        if(il!=ir) lz[i<<1]+=lz[i], lz[i<<1|1]+=lz[i];
        mx[i]+=lz[i];
        lz[i]=0;
    }
    void upd(int i,int il,int ir,int l,int r,int x){
        flush(i,il,ir);
        if(il>r||ir<l) return;
        if(l<=il&&ir<=r) return lz[i]+=x, flush(i,il,ir);
        int mid=il+ir>>1;
        upd(i<<1,il,mid,l,r,x), upd(i<<1|1,mid+1,ir,l,r,x);
        mx[i]=max(mx[i<<1],mx[i<<1|1]);
    }
    void upd(int l,int r,int x){ upd(1,l0,r0,l,r,x); }
    int qr(int i,int il,int ir,int l,int r){
        flush(i,il,ir);
        if(il>r||ir<l) return 0;
        if(l<=il&&ir<=r) return mx[i];
        int mid=il+ir>>1;
        return max(qr(i<<1,il,mid,l,r),qr(i<<1|1,mid+1,ir,l,r));
    }
    int qr(int l,int r){ return qr(1,l0,r0,l,r); }
}t1;
struct fenwick{
    vector<int> bit;
    void build(int n){ bit.assign(n,0); }
    void upd(int i,int x){ for(++i;i<bit.size();i+=i&-i) bit[i]+=x; }
    int qr(int i){
        int ret=0;
        for(++i;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
    int find(int x){
        int sum=0,pos=0;
        for(int i=1<<31-__builtin_clz((int)bit.size()-1);i>0;i>>=1){
            if(i+pos<bit.size()&&bit[i+pos]+sum<=x) pos+=i, sum+=bit[pos];
        }
        return pos;
    }
}t2;

vector<pii> Rail;
int N,L;
void initialize(int N,vector<int> Rail,int L){
    ::N=N, ::L=L;
    for(int i=0;i<N;++i) ::Rail.eb(Rail[i],i);
    sort(::Rail.begin(),::Rail.end(),greater<pii>());
    t1.build(0,N-1);
    t2.build(N+1);
}
vector<int> max_dist(vector<vector<int>> Coins){
    int Q=Coins.size();
    for(int i=0;i<Q;++i) Coins[i].eb(i);
    vector<int> Ans(Q);
    sort(Coins.begin(),Coins.end(),[&](const vector<int> &l,const vector<int> &r){
        return l[2]>r[2];
    });
    int cur=0;
    for(int i=0;i<Q;++i){
        while(cur<N && Rail[cur].f>Coins[i][2]){
            t1.upd(Rail[cur].s-L+1,Rail[cur].s,1);
            t2.upd(Rail[cur].s,1);
            ++cur;
        }
        Coins[i][1]+=t2.qr(Coins[i][0]-1);
        Coins[i][1]+=t1.qr(Coins[i][0],t2.find(Coins[i][1]));
        Ans[Coins[i][3]]=t2.find(Coins[i][1]);
    }
    return Ans;
}
