#include "cheatsheet.h"
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back

const int base=350001,len=500,M=1068;

struct bignum{
    vector<ll> a;
    bignum():a(vector<ll>(len)){}
    bignum& operator+=(const bignum &o){
        for(int i=0;i<len;++i){
            a[i]+=o.a[i];
            if(a[i]>=base) a[i]-=base,++a[i+1];
        }
        return *this;
    }
    bignum& operator-=(const bignum &o){
        for(int i=0;i<len;++i){
            a[i]-=o.a[i];
            if(a[i]<0) a[i]+=base,--a[i+1];
        }
        return *this;
    }
    bignum& operator*=(const ll &o){
        ll r(0);
        for(int i=0;i<len;++i){
            a[i]=a[i]*o+r;
            r=a[i]/base;
            a[i]%=base;
        }
        return *this;
    }
    friend bignum operator*(const bignum &l,const ll &r){return bignum(l)*=r;}
    int cmp(const bignum &o){
        for(int i=len-1;i>=0;--i){
            if(a[i]!=o.a[i]) return a[i]<o.a[i]?-1:1;
        }
        return 0;
    }
    bool operator>=(const bignum &o){return this->cmp(o)!=-1;}
    friend ostream& operator<<(ostream &os,const bignum &x){
        for(int i=len-1;i>0;--i) os<<x.a[i]<<" ";
        os<<x.a[0];
        return os;
    }
};

struct fenwick{
    vector<int> bit;
    fenwick(int n){bit=vector<int>(n);}
    void add(int i,int x){for(;i<bit.size();i+=i&-i)bit[i]+=x;}
    int qr(int i){
        int ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
};

vector<int> write_cheatsheet(int N, vector<int> A){
    vector<bignum> f(M+5);
    f[0].a[0]=1;
    for(int i=1;i<M;++i) f[i]=f[i-1]*i;
    bignum num;
    for(int i=0;i<N;++i) num.a[i]=A[N-i-1];

    vector<int> R;
    bitset<M> used;
	for(int i=0;i<M;++i){
        int cnt=0;
        while(num>=f[M-i-1]) num-=f[M-i-1],++cnt;
        for(int j=0;j<M;++j){
            if(used[j]) continue;
            if(--cnt<0){
                R.eb(j);
                used[j]=1;
                break;
            }
        }
    }
    return R;
}

vector<int> recover_answer(int N, vector<int> R){
    vector<bignum> f(M+5);
    f[0].a[0]=1;
    for(int i=1;i<M;++i) f[i]=f[i-1]*i;

    fenwick fw(M+5);
    for(int i=0;i<M;++i) fw.add(i+1,1);
    bignum ans;
    for(int i=0;i<M;++i){
        int cnt=fw.qr(R[i]+1)-1;
        fw.add(R[i]+1,-1);
        ans+=f[M-i-1]*cnt;
    }
    vector<int> ret(N);
    // cout<<ans<<endl;
    for(int i=0;i<N;++i) ret[i]=ans.a[i];
    reverse(ret.begin(),ret.end());
    return ret;
}


/*
cd "c:\Users\Nattanan\Documents\.me\ipst\cheatsheet\" ; if ($?) { g++ -std=c++17 cheatsheet.cpp stub.cpp -o cheatsheet } ; if ($?) { .\cheatsheet }
*/
