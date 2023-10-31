#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define mid (l+(r-l>>1))

struct Query{
    bool opr;
    int a,b,c;
}Q[100005];
vector<int> vec;
ll dp[200005];

struct A{
    vector<A> child;
    int l,r;
    ll sum;
    bool call;
    int lazy;
    A(int l_=0,int r_=0){
        l=l_,r=r_;
        sum=0;
        call=lazy=0;
    }
    void flush(){
        if(l!=r&&child.empty()){
            child.emplace_back(l,mid);
            child.emplace_back(mid+1,r);
        }
        if(call){
            if(l!=r){
                child[0].call=child[1].call=1;
                child[0].lazy=child[1].lazy=lazy;
            }
            sum=(dp[r]-dp[l-1])*lazy;
            lazy=call=0;
        }
    }
    void upd(int &l0,int &r0,int &x){
        flush();
        if(l0<=l&&r<=r0){
            lazy=x;
            call=1;
            flush();
            return;
        }
        if(l>r0||r<l0) return;
        child[0].upd(l0,r0,x);
        child[1].upd(l0,r0,x);
        sum=child[0].sum+child[1].sum;
    }
    ll query(int &l0,int &r0){
        flush();
        if(l0<=l&&r<=r0) return sum;
        if(l>r0||r<l0) return 0;
        return child[0].query(l0,r0)+child[1].query(l0,r0);
    }
}tree;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    ll n;
    int Q_; cin>>n>>Q_;
    for(int i=0;i<Q_;++i){
        cin>>Q[i].opr>>Q[i].a>>Q[i].b;
        if(Q[i].opr==0) cin>>Q[i].c;
        vec.pb(Q[i].a);
        vec.pb(Q[i].b);
    }
    vec.pb(n);
    sort(vec.begin(),vec.end());
    vec.resize(unique(vec.begin(),vec.end())-vec.begin());

    for(int i=1;i<vec.size();++i){
        dp[i]=1LL*(vec[i]-vec[i-1])+dp[i-1];
    }

    tree=A(1,vec.size()-1);
    for(int i=0;i<Q_;++i){
        Q[i].a=lower_bound(vec.begin(),vec.end(),Q[i].a)-vec.begin()+1;
        Q[i].b=lower_bound(vec.begin(),vec.end(),Q[i].b)-vec.begin();
        if(Q[i].opr==0) tree.upd(Q[i].a,Q[i].b,Q[i].c);
        else cout<<tree.query(Q[i].a,Q[i].b)<<endl;
    }

    return 0;
}
/**

10
6
1 0 10
0 0 5 1
1 0 10
0 5 10 2
1 0 10
1 3 8
==0 5 15 8

2000000000
2
0 0 2000000000 1000000
1 0 2000000000
==2000000000000000

*/
