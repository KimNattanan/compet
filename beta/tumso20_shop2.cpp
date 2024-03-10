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
const ld eps=1e-8;

mt19937 rng(time(0));

ll a[100005];

struct segment{
    static const int N=1<<18;
    struct node{
        ll mn,lz;
        int cnt;
        node():lz(0),mn(0),cnt(0){}
        node(ll x):lz(0),mn(x),cnt(1){}
        friend node operator+(node l,node r){
            if(l.mn<r.mn) return l;
            if(l.mn>r.mn) return r;
            l.cnt+=r.cnt;
            return l;
        }
    }t[N];
    int l0,r0;
    void build(int i,int l,int r){
        if(l==r) return void(t[i]=node(a[l]));
        int mid=l+r>>1;
        build(i<<1,l,mid), build(i<<1|1,mid+1,r);
        t[i]=t[i<<1]+t[i<<1|1];
    }
    void build(int l,int r){l0=l, r0=r, build(1,l,r);}
    void flush(int i,int il,int ir){
        if(!t[i].lz) return;
        if(il!=ir){
            t[i<<1].lz+=t[i].lz;
            t[i<<1|1].lz+=t[i].lz;
        }
        t[i].mn+=t[i].lz;
        t[i].lz=0;
    }
    void upd(int i,int il,int ir,int l,int r,int x){
        flush(i,il,ir);
        if(l<=il&&ir<=r){
            t[i].lz+=x;
            flush(i,il,ir);
            return;
        }
        if(il>r||ir<l) return;
        int mid=il+ir>>1;
        upd(i<<1,il,mid,l,r,x), upd(i<<1|1,mid+1,ir,l,r,x);
        t[i]=t[i<<1]+t[i<<1|1];
    }
    void upd(int l,int r,int x){upd(1,l0,r0,l,r,x);}
    int getAns(){
        flush(1,l0,r0);
        return t[1].cnt;
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

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    for(int i=1;i<=n;++i){
        int x; cin>>x;
        t2.insert(x);
        a[i]=a[i-1]+x-i;
    }
    t.build(1,n);
    cout<<t.getAns()<<endl;
    while(Q--){
        int opr,l,r; cin>>opr>>l>>r;
        if(opr==1){
            int tmp=t2.qr(r)-t2.qr(l);
            t.upd(l,r-1,tmp);
            t2.rev(l,r);
            if(l+1<r-1) t2.rev(l+1,r-1);
        }
        else{
            for(int L=l,R=r;L<R;++L,--R){
                int tmp=t2.qr(R)-t2.qr(L);
                t.upd(L,R-1,tmp);
            }
            t2.rev(l,r);
        }
        cout<<t.getAns()<<endl;
    }

}
