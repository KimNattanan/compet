#include<bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));

struct treap{
    struct node{
        char val;
        int cnt,prio;
        node *l,*r;
        bool lazy;
        node(char val_):val(val_),cnt(1),prio(rnd()),l(nullptr),r(nullptr),lazy(0){}
    };
    using pitem=node*;
    pitem rt;
    int getCnt(pitem t){return t?t->cnt:0;}
    void setCnt(pitem t){t->cnt=getCnt(t->l)+getCnt(t->r);}
    void split(pitem t,pitem &l,pitem &r,int x){
        if(!t) return void(l=r=nullptr);
        if(getCnt(t->l)>=x) split(t->l,l,t->l,x),r=t;
        else split(t->r,t->r,r,x-getCnt(t->l)-1),l=t;
    }
    void merge(pitem &t,pitem l,pitem r){
        if(!l||!r) return void(l?t=l:t=r);
        if(l->prio>r->prio) merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
    }
    void insert(int x,string s){
        pitem l,r;
        split(rt,l,r,x);
        for(auto &e:s) merge(l,l,new node(e));
        merge(rt,l,r);
    }
}t;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    string s; cin>>s;
    int n=s.length();
    t.insert(0,s);

    return 0;
}
/*

*/
