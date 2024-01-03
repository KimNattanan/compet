#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
using ld=long double;

struct line{
    ld m,c;
    line(ld m_=0,ld c_=0):m(m_),c(c_){}
    ld operator()(ld x)const{return m*x+c;}
};
struct lichao{
    vector<lichao> child;
    int l,r,mid;
    line f;
    lichao(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)),f(0,numeric_limits<ld>::min()){}
    void build(){
        if(l+1==r) return;
        child.eb(l,mid),child.eb(mid,r);
        child[0].build(),child[1].build();
    }
    void insert(line f2){
        if(l+1==r){
            if(f2(l)>f(l)) f=f2;
            return;
        }
        if(f.m>f2.m) swap(f,f2);
        if(f(mid)<f2(mid)) swap(f,f2),child[0].insert(f2);
        else child[1].insert(f2);
    }
    ld qr(int x){
        if(l+1==r) return f(x);
        if(x<mid) return max(f(x),child[0].qr(x));
        return max(f(x),child[1].qr(x));
    }
}t;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
    t=lichao(1,50005);
    t.build();
    while(Q--){
        string opr; cin>>opr;
        if(opr=="Query"){
            int x; cin>>x;
            cout<<int(t.qr(x)/100)<<endl;
        }
        else if(opr=="Project"){
            ld a,b; cin>>a>>b;
            t.insert(line(b,a-b));
        }
    }

    return 0;
}
