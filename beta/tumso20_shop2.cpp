#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
#define eb emplace_back
#define f first
#define s second

mt19937_64 rng(time(nullptr));
ll rnd[100005],qs[100005];
int ans;

struct info{
    int mn,mx;
    ll sum;
    info(int i=0):mn(i),mx(i),sum(rnd[i]){
        if(!i) return;

    }
    void rev(){

    }
    friend info operator+(info l,info r){
        l.mn=min(l.mn,r.mn);
        l.mx=max(l.mx,r.mx);
        l.sum+=r.sum;
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
            t->lazy=0;
            if(t->l) t->l->lazy^=1;
            if(t->r) t->r->lazy^=1;
            swap(t->l,t->r);
            t->val.rev();
        }
    }
    void upd(pnode t){
        if(!t) return;
        flush(t->l);
        flush(t->r);
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
        flush(a);
        ll sum0=val(a).sum;
        ans-=getAns(b,sum0,l-1);
        b->lazy^=1;
        flush(b);
        ans+=getAns(b,sum0,l-1);
        merge(rt,a,b);
        merge(rt,rt,c);
    }
    void insert(int x){merge(rt,rt,new node(x));}
    int getAns(pnode t,ll sum0,int sz0){
        if(!t) return 0;
        flush(t->l);
        flush(t->r);
        info valL=val(t->l);
        return (sum0+valL.sum+rnd[t->num]==qs[sz0+sz(t->l)+1])+getAns(t->l,sum0,sz0)+getAns(t->r,sum0+valL.sum+rnd[t->num],sz0+sz(t->l)+1);
    }
    int getAns(){
        return 0;
    }
}t;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    for(int i=1;i<=n;++i){
        rnd[i]=rng();
        qs[i]=qs[i-1]+rnd[i];
    }
    ll sum=0;
    for(int i=1;i<=n;++i){
        int x; cin>>x;
        t.insert(x);
        sum+=rnd[x];
        if(sum==qs[i]) ++ans;
    }
    // cout<<t.getAns()<<endl;
    cout<<ans<<endl;
    while(Q--){
        int opr,l,r; cin>>opr>>l>>r;
        if(opr==1){
            if(l+1<r-1) t.reverse(l+1,r-1);
            t.reverse(l,r);
        }
        else if(opr==2){
            t.reverse(l,r);
        }
        // cout<<t.getAns()<<endl;
        cout<<ans<<endl;
    }

    return 0;
}
