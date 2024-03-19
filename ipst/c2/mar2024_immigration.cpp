#include "immigration.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define f first
#define s second
using ll=long long;
#define eb emplace_back

struct segment{
    int mx[1<<20],l0,r0;
    void init(int l,int r){l0=l,r0=r;}
    void upd(int i,int il,int ir,int x,int v){
        if(il==ir) return void(mx[i]=v);
        int im=il+ir>>1;
        if(x<=im) upd(i<<1,il,im,x,v);
        else upd(i<<1|1,im+1,ir,x,v);
        mx[i]=max(mx[i<<1],mx[i<<1|1]);
    }
    void upd(int i,int v){upd(1,l0,r0,i,v);}
    int qr(int i,int il,int ir,int l,int r){
        if(l<=il&&ir<=r) return mx[i];
        if(il>r||ir<l) return 0;
        int im=il+ir>>1;
        return max(qr(i<<1,il,im,l,r),qr(i<<1|1,im+1,ir,l,r));
    }
    int qr(int l,int r){return qr(1,l0,r0,l,r);}
}t;

int id[500005],lm[500005],mn[500005];

int immigration(int N, std::vector<int> A) {

    for(int i=0;i<N;++i) id[A[i]]=i;
    for(int i=N,mnn=1e9;i>=1;--i){
        lm[id[i]]=mnn;
        mnn=min(mnn,id[i]);
    }

    mn[1]=0;
    t.init(0,N-1);
    t.upd(id[1],1);
    for(int i=2;i<=N;++i){
        mn[i]=max(mn[i-1],t.qr(lm[id[i]]+1,id[i]-1));
        for(int j=mn[i-1]+1;j<=mn[i];++j) t.upd(id[j],0);
        t.upd(id[i],i);
    }
    int cur=N, ans=0;
    while(cur){
        ++ans;
        cur=mn[cur];
    }

    return ans;
}
/*
9
9 5 4 6 8 2 1 7 3
*/
