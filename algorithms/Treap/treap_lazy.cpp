#include<bits/stdc++.h>
using namespace std;

mt19937 rng(time(0));

struct treap{
    struct node{
        char val;
        int cnt,prio;
        node *l,*r;
        bool lazy;
        node(char val_):val(val_),cnt(1),prio(rng()),l(nullptr),r(nullptr),lazy(0){}
    };
    using pitem=node*;
    pitem rt;
    int getCnt(pitem t){return t?t->cnt:0;}
    void updCnt(pitem t){if(t)t->cnt=getCnt(t->l)+getCnt(t->r)+1;}
    void flush(pitem t){
        if(t&&t->lazy){
            t->lazy=0;
            swap(t->l,t->r);
            if(t->l) t->l->lazy^=1;
            if(t->r) t->r->lazy^=1;
        }
    }
    void split(pitem t,pitem &l,pitem &r,int x){
        flush(t);
        if(!t) return void(l=r=nullptr);
        if(getCnt(t->l)>=x) split(t->l,l,t->l,x),r=t;
        else split(t->r,t->r,r,x-getCnt(t->l)-1),l=t;
        updCnt(t);
    }
    void merge(pitem &t,pitem l,pitem r){
        flush(l),flush(r);
        if(!l||!r) return void(l?t=l:t=r);
        if(l->prio>r->prio) merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        updCnt(t);
    }
    void insert(int x,string s){
        pitem l,r;
        split(rt,l,r,x);
        for(auto &e:s) merge(l,l,new node(e));
        merge(rt,l,r);
    }
    void reverse(int l,int r){
        pitem a,b,c;
        split(rt,a,b,l-1);
        split(b,b,c,r-l+1);
        b->lazy^=1;
        flush(b);
        merge(rt,a,b);
        merge(rt,rt,c);
    }
    string print(){
        string s;
        function<void(pitem)> dfs=[&](pitem t){
            if(!t) return;
            flush(t);
            dfs(t->l);
            s.push_back(t->val);
            dfs(t->r);
        };
        dfs(rt);
        return s;
    }
}t;

