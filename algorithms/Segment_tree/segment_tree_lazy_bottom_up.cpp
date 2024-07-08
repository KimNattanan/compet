#include<bits/stdc++.h>
using namespace std;

const int N=(1<<20)+5;

int a[200005];

struct segment{
    int n,height,sum[N],lz[N];
    segment(int n0=0){
        for(n=1,height=0;n<n0;n<<=1,++height);
        for(int i=n<<1;i>=0;--i) lz[i]=0;
    }
    void build(int n0){
        for(int i=1;i<=n0;++i) sum[i+n-1]=a[i];
        for(int i=n0+1;i<=n;++i) sum[i+n-1]=0;
        for(int i=n-1;i>0;--i) sum[i]=sum[i<<1]+sum[i<<1|1];
    }
    void flush(int i,int h){
        if(!lz[i]) return;
        if(i<n){
            lz[i<<1]+=lz[i];
            lz[i<<1|1]+=lz[i];
        }
        sum[i]+=(1<<h)*lz[i];
        lz[i]=0;
    }
    void cal(int i){
        int h=1;
        for(i>>=1;i>0;i>>=1,++h){
            flush(i<<1,h-1),flush(i<<1|1,h-1);
            sum[i]=sum[i<<1]+sum[i<<1|1];
        }
    }
    void upd(int l,int r,int val){
        l+=n-1,r+=n-1;
        for(int i=height;i>=0;--i) flush(l>>i,i),flush(r>>i,i);
        for(int i=l,j=r;i<=j;i>>=1,j>>=1){
            if(i&1) lz[i++]+=val;
            if(~j&1) lz[j--]+=val;
        }
        cal(l),cal(r);
    }
    int qr(int l,int r){
        l+=n-1,r+=n-1;
        for(int i=height;i>=0;--i) flush(l>>i,i),flush(r>>i,i);
        int ret=0;
        for(int h=0;l<=r;l>>=1,r>>=1){
            if(l&1) ret+=sum[l++];
            if(~r&1) ret+=sum[r--];
        }
        return ret;
    }
}t;
