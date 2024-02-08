#include<bits/stdc++.h>
using namespace std;

const int N=(1<<19)+5;

int a[200005];

struct segment{
    int n,sum[N];
    segment(int n0=0){
        for(n=1;n<n0;n<<=1);
    }
    void build(){
        for(int i=1;i<=n;++i) sum[i+n-1]=a[i];
        for(int i=n-1;i>0;--i) sum[i]=sum[i<<1]+sum[i<<1|1];
    }
    void upd(int i,int val){
        sum[i+=n-1]=val;
        for(i>>=1;i>0;i>>=1) sum[i]=sum[i<<1]+sum[i<<1|1];
    }
    int qr(int l,int r){
        int ret=0;
        for(l+=n-1,r+=n-1;l<=r;l>>=1,r>>=1){
            if(l&1) ret+=sum[l++];
            if(~r&1) ret+=sum[r--];
        }
        return ret;
    }
}t;
