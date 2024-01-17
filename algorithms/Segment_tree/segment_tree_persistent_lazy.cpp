#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct segment{
    struct node{
        node *L,*R;
        ll sum,lz;
        node():L(nullptr),R(nullptr),sum(0),lz(0){}
    };
    using pnode=node*;
    vector<pnode> rt;
    int l0,r0;
    void build(pnode &t,int il,int ir){
        t=new node();
        if(il==ir) return;
        int mid=il+(ir-il>>1);
        build(t->L,il,mid),build(t->R,mid+1,ir);
    }
    void build(int n,int l,int r){
        rt=vector<pnode>(n+1);
        l0=l,r0=r;
        build(rt[0],l,r);
    }
    void flush(pnode t,int il,int ir){
        if(t&&t->lz){
            t->sum+=(ir-il+1)*t->lz;
            if(il!=ir){
                int mid=il+(ir-il>>1);
                t->L=new node(*(t->L));
                t->R=new node(*(t->R));
                t->L->lz+=t->lz;
                t->R->lz+=t->lz;
            }
            t->lz=0;
        }
    }
    void upd(pnode t0,pnode &t1,int il,int ir,int l,int r,int x){
        flush(t0,il,ir);
        if(il>r||ir<l) return void(t1=t0);
        if(l<=il&&ir<=r){
            t1=new node(*t0);
            t1->lz+=x;
            flush(t1,il,ir);
            return;
        }
        t1=new node();
        int mid=il+(ir-il>>1);
        upd(t0->L,t1->L,il,mid,l,r,x);
        upd(t0->R,t1->R,mid+1,ir,l,r,x);
        t1->sum=t1->L->sum+t1->R->sum;
    }
    void upd(int prev,int now,int l,int r,int x){upd(rt[prev],rt[now],l0,r0,l,r,x);}
    ll qr(pnode t,int il,int ir,int l,int r){
        flush(t,il,ir);
        if(l<=il&&ir<=r) return t->sum;
        if(il>r||ir<l) return 0;
        int mid=il+(ir-il>>1);
        return qr(t->L,il,mid,l,r)+qr(t->R,mid+1,ir,l,r);
    }
    ll qr(int now,int l,int r){return qr(rt[now],l0,r0,l,r);}
}t;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    t.build(n,1,100005);
    for(int i=1;i<=n;++i){
        int l,r; cin>>l>>r;
        t.upd(i-1,i,l,r,1);
    }
    int Q; cin>>Q;
    while(Q--){
        int i,l,r; cin>>i>>l>>r;
        cout<<t.qr(i,l,r)<<endl;
    }

    return 0;
}
