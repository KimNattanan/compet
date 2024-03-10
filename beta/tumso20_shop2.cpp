#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using ld=long double;
using db=double;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define _sz(x) (int)(x).size()
const int eps=1e-4;

mt19937 rng(time(0));

struct treap{
    struct node{
        int sz,prio,ans;
        ll num,lz,mn;
        node *l,*r;
        node(ll num):num(num),mn(num),ans(num==0),lz(0),sz(1),prio(rng()),l(nullptr),r(nullptr){}
    };
    using pnode=node*;
    pnode rt;
    treap():rt(nullptr){}
    int sz(pnode t){return t?t->sz:0;}
    int ans(pnode t){return t?t->ans:0;}
    ll mn(pnode t){return t?t->mn:1e18;}
    void flush(pnode t){
        if(!t||!t->lz) return;
        if(t->l) t->l->lz+=t->lz;
        if(t->r) t->r->lz+=t->lz;
        t->num+=t->lz;
        t->mn+=t->lz;
        t->lz=0;
    }
    void upd(pnode t){
        if(!t) return;
        flush(t->l), flush(t->r);
        t->sz=sz(t->l)+1+sz(t->r);
        t->mn=min({mn(t->l),mn(t->r),t->num});
        t->ans=(t->num==t->mn);
        if(mn(t->l)==t->mn) t->ans+=ans(t->l);
        if(mn(t->r)==t->mn) t->ans+=ans(t->r);
    }
    void split(pnode t,pnode &l,pnode &r,int x){
        flush(t);
        if(!t) return void(l=r=nullptr);
        if(sz(t->l)>=x) split(t->l,l,t->l,x),r=t;
        else split(t->r,t->r,r,x-sz(t->l)-1),l=t;
        upd(t);
    }
    void merge(pnode &t,pnode l,pnode r){
        flush(l), flush(r);
        if(!l||!r) return void(t=l?l:r);
        if(l->prio>r->prio) merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        upd(t);
    }
    void insert(ll x){
        merge(rt,rt,new node(x));
    }
    void add(int l,int r,ll x){
        pnode t1,t2,t3;
        split(rt,t1,t2,l-1);
        split(t2,t2,t3,r-l+1);
        t2->lz+=x;
        flush(t2);
        merge(rt,t1,t2);
        merge(rt,rt,t3);
    }
    int getAns(){
        return ans(rt);
    }
}t;
struct treap2{
    struct node{
        int num,sz,prio;
        bool lz;
        node *l,*r;
        node(int num):num(num),sz(1),lz(0),prio(rng()),l(nullptr),r(nullptr){}
    };
    using pnode=node*;
    pnode rt;
    treap2():rt(nullptr){}
    int sz(pnode t){return t?t->sz:0;}
    void flush(pnode t){
        if(!t||!t->lz) return;
        if(t->l) t->l->lz^=1;
        if(t->r) t->r->lz^=1;
        swap(t->l,t->r);
        t->lz=0;
    }
    void upd(pnode t){
        if(!t) return;
        flush(t->l), flush(t->r);
        t->sz=sz(t->l)+1+sz(t->r);
    }
    void split(pnode t,pnode &l,pnode &r,int x){
        flush(t);
        if(!t) return void(l=r=nullptr);
        if(sz(t->l)>=x) split(t->l,l,t->l,x),r=t;
        else split(t->r,t->r,r,x-sz(t->l)-1),l=t;
        upd(t);
    }
    void merge(pnode &t,pnode l,pnode r){
        flush(l), flush(r);
        if(!l||!r) return void(t=l?l:r);
        if(l->prio>r->prio) merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        upd(t);
    }
    void insert(int x){
        merge(rt,rt,new node(x));
    }
    void rev(int l,int r){
        pnode t1,t2,t3;
        split(rt,t1,t2,l-1);
        split(t2,t2,t3,r-l+1);
        t2->lz^=1;
        flush(t2);
        merge(rt,t1,t2);
        merge(rt,rt,t3);
    }
    int qr(int i){
        pnode t1,t2,t3;
        split(rt,t1,t2,i-1);
        split(t2,t2,t3,1);
        int ret=t2->num;
        merge(rt,t1,t2);
        merge(rt,rt,t3);
        return ret;
    }
    void print(){
        function<void(pnode)> dfs=[&](pnode t){
            flush(t);
            if(!t) return;
            dfs(t->l);
            cout<<t->num<<" ";
            dfs(t->r);
        };
        dfs(rt);
        cout<<endl;
    }
}t2;

int a[100005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    {
        ll tmp=0;
        for(int i=1;i<=n;++i){
            int x; cin>>x;
            t2.insert(x);
            tmp+=x-i;
            t.insert(tmp);
            a[i]=x;
        }
    }
    bool sub=(n<=5000&&Q<=5000);
    cout<<t.getAns()<<endl;
    while(Q--){
        int opr,l,r; cin>>opr>>l>>r;
        if(sub){
            if(opr==1) swap(a[l],a[r]);
            else for(;l<r;++l,--r) swap(a[l],a[r]);
            ll sum=0;
            int ans=0;
            for(int i=1;i<=n;++i){
                sum+=a[i];
                if(sum==1LL*i*(i+1)>>1) ++ans;
            }
            cout<<ans<<endl;
            continue;
        }
        if(opr==1){
            int tmp=t2.qr(r)-t2.qr(l);
            t.add(l,r-1,tmp);
            t2.rev(l,r);
            if(l+1<r-1) t2.rev(l+1,r-1);
        }
        else{
            for(int L=l,R=r;L<R;++L,--R){
                int tmp=t2.qr(R)-t2.qr(L);
                t.add(L,R-1,tmp);
            }
            t2.rev(l,r);
        }
        cout<<t.getAns()<<endl;
    }

}
