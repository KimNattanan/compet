#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;

mt19937_64 rng(time(nullptr));

struct treap{
    struct node{
        node *l,*r;
        int sz;
        ll prio;
        ll val;
        bool lazy;
        node(ll val_=0):l(nullptr),r(nullptr),sz(1),prio(rng()),val(val_),lazy(0){}
    };
    using pnode=node*;
    pnode rt;
    int sz(pnode t){return t?t->sz:0;}
    void flush(pnode t){
        if(t&&t->lazy){
            if(t->l) t->l->lazy^=1;
            if(t->r) t->r->lazy^=1;
            t->lazy=0;
            swap(t->l,t->r);
        }
    }
    void upd(pnode t){
        if(!t) return;
        flush(t->l);
        flush(t->r);
        t->sz=sz(t->l)+sz(t->r)+1;
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
    void insert(ll x){merge(rt,rt,new node(x));}
}t;
