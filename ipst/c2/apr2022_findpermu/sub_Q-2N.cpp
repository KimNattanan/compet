#include "inversion.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define eb emplace_back

mt19937 rng(time(0));

struct treap{
    struct node{
        node *l,*r;
        int prio,sz,val;
        node(int val):val(val),sz(1),prio(rng()),l(nullptr),r(nullptr){}
    };
    using pnode=node*;
    pnode rt;
    treap():rt(nullptr){}
    int sz(pnode t){return t?t->sz:0;}
    void upd(pnode t){
        if(!t) return;
        t->sz=sz(t->l)+1+sz(t->r);
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
    void insert(int x,int val){
        pnode t1,t2;
        split(rt,t1,t2,x);
        merge(rt,t1,new node(val));
        merge(rt,rt,t2);
    }
    void print(vector<int> &vec){
        function<void(pnode)> dfs=[&](pnode t){
            if(!t) return;
            dfs(t->l);
            vec.eb(t->val);
            dfs(t->r);
        };
        dfs(rt);
    }
};

vector<int> find_permutation(int N,long long V){
    treap tl,tr;
    for(int i=1;i<N;++i){
        ll x=swap_and_report(0,i)-V;
        swap_and_report(0,i);
        if(x<0){
            x=abs(x)-1>>1;
            tl.insert(x,i);
        }
        else{
            x=abs(x)-1>>1;
            tr.insert(x,i);
        }
    }
    vector<int> vec,ans(N);
    tl.print(vec);
    reverse(vec.begin(),vec.end());
    vec.eb(0);
    tr.print(vec);
    for(int i=0;i<N;++i) ans[vec[i]]=i+1;
    // for(int i=0;i<N;++i) cerr<<ans[i]<<","; cout<<endl;
    return ans;
}
