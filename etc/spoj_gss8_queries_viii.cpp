#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int K=10;

mt19937_64 rng(time(nullptr));

ll pw[100005][15],C[15][15];

struct info{
    int sz;
    vector<ll> ans;
    info():sz(0){}
    info(ll num):sz(1){
        ans=vector<ll>(K+5);
        for(int i=0;i<=K;++i) ans[i]=num;
    }
    friend info operator+(info l,info r){
        if(!l.sz) return r;
        if(!r.sz) return l;
        l.ans[0]+=r.ans[0];
        for(int i=1;i<=K;++i){
            for(int j=0;j<=i;++j){
                l.ans[i]+=r.ans[j]*pw[l.sz][i-j]*C[i][j];
            }
        }
        l.sz+=r.sz;
        return l;
    }
};
struct treap{
    struct node{
        int sz;
        ll prio;
        node *l,*r;
        ll num;
        info val;
        node(ll x):sz(1),prio(rng()),l(nullptr),r(nullptr),num(x),val(num){}
    };
    using pnode=node*;
    pnode rt;
    int sz(pnode t){return t?t->sz:0;}
    info val(pnode t){return t?t->val:info();}
    void upd(pnode t){
        if(!t) return;
        t->sz=sz(t->l)+sz(t->r)+1;
        t->val=val(t->l)+info(t->num)+val(t->r);
    }
    void split(pnode t,pnode &l,pnode &r,int x){
        if(!t) return void(l=r=nullptr);
        if(sz(t->l)>=x) split(t->l,l,t->l,x),r=t;
        else split(t->r,t->r,r,x-sz(t->l)-1),l=t;
        upd(t);
    }
    void merge(pnode &t,pnode l,pnode r){
        if(!l||!r) return void(t=l?l:r);
        if(l->prio>r->prio) merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        upd(t);
    }
    void push_back(ll num){merge(rt,rt,new node(num));}
    void insert(int x,ll num){
        pnode t1,t2;
        split(rt,t1,t2,x);
        merge(rt,t1,new node(num));
        merge(rt,rt,t2);
    }
    void erase(int x){
        pnode t1,t2,t3;
        split(rt,t1,t2,x-1);
        split(t2,t2,t3,1);
        // delete t2;
        merge(rt,t1,t3);
    }
    void set(int x,ll val){
        pnode t1,t2,t3;
        split(rt,t1,t2,x-1);
        split(t2,t2,t3,1);
        // delete t2;
        merge(rt,t1,new node(val));
        merge(rt,rt,t3);
    }
    ll getAns(int l,int r,int k){
        pnode t1,t2,t3;
        split(rt,t1,t2,l-1);
        split(t2,t2,t3,r-l+1);
        ll ret=val(t2).ans[k];
        merge(rt,t1,t2);
        merge(rt,rt,t3);
        return ret;
    }
}t;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=0;i<n;++i){
        ll x; cin>>x;
        // t.insert(i,x);
        t.push_back(x);
    }
    for(int i=1;i<=n;++i){
        pw[i][0]=1;
        for(int j=1;j<=K;++j) pw[i][j]=pw[i][j-1]*i;
    }
    for(int i=0;i<=K;++i){
        C[i][0]=1;
        for(int j=1;j<=i;++j){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
    int Q; cin>>Q;
    while(Q--){
        char opr; cin>>opr;
        if(opr=='I'){
            int x; cin>>x;
            ll val; cin>>val;
            t.insert(x,val);
        }
        else if(opr=='D'){
            int x; cin>>x;
            t.erase(x+1);
        }
        else if(opr=='R'){
            int x; cin>>x;
            ll val; cin>>val;
            t.set(x+1,val);
        }
        else{
            int l,r,k; cin>>l>>r>>k;
            cout<<t.getAns(l+1,r+1,k)<<endl;
        }
    }

    return 0;
}
