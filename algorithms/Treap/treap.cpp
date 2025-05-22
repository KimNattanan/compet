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
        node(ll val=0):l(nullptr),r(nullptr),sz(1),prio(rng()),val(val){}
    };
    using pnode=node*;
    pnode rt;
    treap():rt(nullptr){}
    int sz(pnode t){return t?t->sz:0;}
    void upd(pnode t){
        if(!t) return;
        t->sz=sz(t->l)+sz(t->r)+1;
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
    void insert(ll x){merge(rt,rt,new node(x));}
}t;
