#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
#define eb emplace_back
#define f first
#define s second

mt19937_64 rng(time(nullptr));
ll rnd[100005],qs[100005];

struct info{
    deque<pair<int,ll>> dq1,dq2;
    int ans1,ans2;
    ll sum;
    info(int i=0):ans1(0),ans2(0),sum(0){
        if(!i) return;
        sum=rnd[i];
        dq1.eb(i,sum),dq2.eb(i,sum);
        ans1=ans2=(i==1);
    }
    void reverse(){
        swap(dq1,dq2);
        swap(ans1,ans2);
    }
    friend info operator+(info l,info r){
        if(l.dq1.empty()) return r;
        if(r.dq1.empty()) return l;
        while(r.dq1.size()&&r.dq1.front().f<l.dq1.back().f) r.dq1.pop_front();
        while(r.dq1.size()){
            l.dq1.eb(r.dq1.front().f,l.sum+r.dq1.front().s);
            r.dq1.pop_front();
        }
        while(l.dq2.size()&&l.dq2.front().f<r.dq2.back().f) l.dq2.pop_front();
        while(l.dq2.size()){
            r.dq2.eb(l.dq2.front().f,r.sum+l.dq2.front().s);
            l.dq2.pop_front();
        }
        swap(l.dq2,r.dq2);
        swap(l.ans2,r.ans2);
        l.ans1=l.ans2=0;
        int mx=0;
        for(auto &e:l.dq1){
            if(!mx){
                mx=e.f;
                continue;
            }
            if(e.s-rnd[e.f]==qs[mx]) ++l.ans1;
            mx=e.f;
        }
        mx=0;
        for(auto &e:l.dq2){
            if(!mx){
                mx=e.f;
                continue;
            }
            if(e.s-rnd[e.f]==qs[mx]) ++l.ans2;
            mx=e.f;
        }
        l.sum+=r.sum;
        if(l.sum==qs[l.dq1.back().f]) ++l.ans1;
        if(l.sum==qs[l.dq2.back().f]) ++l.ans2;
        return l;
    }
};
struct treap{
    struct node{
        node *l,*r;
        int sz;
        ll prio;
        int num;
        info val;
        bool lazy;
        node(int num_=0):l(nullptr),r(nullptr),sz(1),prio(rng()),num(num_),val(num_),lazy(0){}
    };
    using pnode=node*;
    pnode rt;
    int sz(pnode t){return t?t->sz:0;}
    info val(pnode t){return t?t->val:info();}
    void flush(pnode t){
        if(t&&t->lazy){
            if(t->l) t->l->lazy^=1;
            if(t->r) t->r->lazy^=1;
            t->lazy=0;
            swap(t->l,t->r);
            t->val.reverse();
        }
    }
    void upd(pnode t){
        if(!t) return;
        flush(t);
        t->sz=sz(t->l)+sz(t->r)+1;
        t->val=val(t->l)+info(t->num)+val(t->r);
    }
    void split(pnode t,pnode &l,pnode &r,int x){
        flush(t);
        if(!t) return void(l=r=nullptr);
        if(sz(t->l)>=x) split(t->l,l,t->l,x),r=t;
        else split(t->r,t->r,r,x-sz(t->l)-1),l=t;
        upd(t);
    }
    void merge(pnode &t,pnode l,pnode r){
        flush(l);
        flush(r);
        if(!l||!r) return void(l?t=l:t=r);
        if(l->prio>r->prio) merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        upd(t);
    }
    void reverse(int l,int r){
        pnode a,b,c;
        split(rt,a,b,l-1);
        split(b,b,c,r-l+1);
        flush(b);
        b->lazy^=1;
        flush(b);
        merge(rt,a,b);
        merge(rt,rt,c);
    }
    void insert(int x){merge(rt,rt,new node(x));}
    int getAns(){return val(rt).ans1;}
}t;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    for(int i=1;i<=n;++i){
        rnd[i]=rng();
        qs[i]=qs[i-1]+rnd[i];
    }
    for(int i=1;i<=n;++i){
        int x; cin>>x;
        t.insert(x);
    }
    cout<<t.getAns()<<endl;
    while(Q--){
        int opr,l,r; cin>>opr>>l>>r;
        if(opr==1){
            t.reverse(l,r);
            if(l+1<r-1) t.reverse(l+1,r-1);
        }
        else if(opr==2){
            t.reverse(l,r);
        }
        cout<<t.getAns()<<endl;
    }

    return 0;
}
