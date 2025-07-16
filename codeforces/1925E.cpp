#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
#define f first
#define s second

using A=pair<int,ll>;
set<A> s;
int n,m,Q;
ll val[300005];

struct fenwick{
    vector<ll> bit;
    fenwick(const int &n=0){init(n);}
    void init(int n){bit=vector<ll>(n);}
    void add(int i,ll x){
        for(;i<bit.size();i+=i&-i) bit[i]+=x;
    }
    ll qr(int i){
        ll ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
}fw;

ll f(int l,int r){
    return 1LL*(r-l)*(r-l-1)>>1;
}
ll play(int i){
    if(i>=n) return 0;
    auto R=s.upper_bound(A(i,LLONG_MAX));
    auto L=R; --L;
    if(i==L->f||i-1==L->f) return fw.qr(n+1-L->f);
    return fw.qr(n+1-R->f)+(L->s*(R->f-i+1)*(R->f-i)>>1);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n>>m>>Q;
    vector<A> vec(m);
    for(auto &[x,v]:vec) cin>>x;
    for(auto &[x,v]:vec) cin>>v;
    sort(vec.begin(),vec.end());
    fw=fenwick(n+5);
    for(int i=0;i<m-1;++i){
        val[vec[i].f]=vec[i].s*f(vec[i].f,vec[i+1].f);
        fw.add(n+1-vec[i].f,val[vec[i].f]);
        s.insert(vec[i]);
    }
    s.insert(vec.back());
    while(Q--){
        int opr; cin>>opr;
        if(opr==1){
            int x; cin>>x;
            ll v; cin>>v;
            auto R=s.upper_bound(A(x,0));
            auto L=R; --L;
            fw.add(n+1-L->f,-val[L->f]+L->s*f(L->f,x));
            val[L->f]=L->s*f(L->f,x);
            val[x]=v*f(x,R->f);
            fw.add(n+1-x,val[x]);
            s.insert(A(x,v));
        }
        else{
            int l,r; cin>>l>>r;
            cout<<play(l)-play(r+1)<<endl;
        }
    }

    return 0;
}
