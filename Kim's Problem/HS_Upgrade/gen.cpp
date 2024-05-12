#include <bits/stdc++.h>
#include "testlib.h"
// #include "aquagenlib.h"
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

template<class T>
T rnd_min(const T &l,const T &r,int t){
    T ret=rnd.next(l,r);
    --t;
    while(t--) ret=min(ret,rnd.next(l,r));
    return ret;
}

template<class T>
T rnd_max(const T &l,const T &r,int t){
    T ret=rnd.next(l,r);
    --t;
    while(t--) ret=max(ret,rnd.next(l,r));
    return ret;
}
bool ok[26];

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int sub=opt<int>(1);
    int prob=opt<int>(2);
    int r=1000,c=1000,k=16;

    if(sub==1) r=c=k=5;
    else if(sub==2) k=5;

    cout<<r<<" "<<c<<" "<<k<<'\n';
    int n1=r*c+1>>1, n2=r*c-n1;
    vector<string> s1,s2;
    vector<int> w1,w2;

    for(int i=0;i<n1;++i){
        string s;
        for(char x='a';x<'a'+k;++x){
            if(rnd.next(1,prob)==1) s+=x;
        }
        if(s.empty()) s+=rnd.next('a','a'+k-1);
        for(auto &e:s) ok[e-'a']=1;
        s1.eb(s);
        w1.eb(rnd_max(1,int(1e9),s.size()));
    }
    for(int i=0;i<k;++i){
        if(ok[i]) ok[i]=0;
        else s1[rnd.next(0,n1-1)]+='a'+i;
    }
    for(int i=0;i<n2;++i){
        string s;
        for(char x='a';x<'a'+k;++x){
            if(rnd.next(1,prob)==1) s+=x;
        }
        if(s.empty()) s+=rnd.next('a','a'+k-1);
        for(auto &e:s) ok[e-'a']=1;
        s2.eb(s);
        w2.eb(rnd_max(1,int(1e9),s.size()));
    }
    for(int i=0;i<k;++i){
        if(ok[i]) ok[i]=0;
        else s2[rnd.next(0,n2-1)]+='a'+i;
    }

    for(int i1=0,i2=0,i=1;i<=r;++i){
        for(int j=1;j<=c;++j){
            if((i+j+1)&1) cout<<s1[i1++]<<" \n"[j==c];
            else cout<<s2[i2++]<<" \n"[j==c];
        }
    }
    for(int i1=0,i2=0,i=1;i<=r;++i){
        for(int j=1;j<=c;++j){
            if((i+j+1)&1) cout<<w1[i1++]<<" \n"[j==c];
            else cout<<w2[i2++]<<" \n"[j==c];
        }
    }

    return 0;
}

/*
gen 1 0 1_ > $
gen 1 0 2_ > $
gen 1 1 3_ > $
gen 2 1 kim > $
gen 2 1 5_ > $
gen 2 1 68_ > $
gen 3 1 7_ > $
gen 3 1 8_ > $
gen 3 1 9_ > $
gen 3 1  10_ > $
*/