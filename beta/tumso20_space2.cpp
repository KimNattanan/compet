#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

const ll md=998244353;
const int MXR=100005;

int H[100005];

struct segment1{
    vector<segment1> child;
    int l,r,mid,mx;
    segment1(int l=0,int r=0):l(l),r(r),mid(l+(r-l>>1)){}
    void build(){
        if(l==r) return void(mx=l);
        child.eb(l,mid),child.eb(mid+1,r);
        child[0].build(),child[1].build();
        if(H[child[0].mx]>H[child[1].mx]) mx=child[0].mx;
        else mx=child[1].mx;
    }
    int qr(int l0,int r0){
        if(l0<=l&&r<=r0) return mx;
        if(l>r0||r<l0) return 0;
        int il=child[0].qr(l0,r0);
        int ir=child[1].qr(l0,r0);
        if(!il||!ir) return il?il:ir;
        if(H[il]>H[ir]) return il;
        return ir;
    }
}t1;

struct segment2{
    struct node{
        node *L,*R;
        ll sum;
        int lz;
        node():L(nullptr),R(nullptr),sum(0),lz(0){}
    };
    using pnode=node*;
    vector<pnode> rt;
    int l0,r0;
    void build(pnode &t,const int &il,const int &ir){
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
    void flush(pnode t,const int &il,const int &ir){
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
    void upd(pnode t0,pnode &t1,const int &il,const int &ir,const int &l,const int &r,const int &x){
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
    void upd(const int &prev,const int &now,const int &l,const int &r,const int &x){upd(rt[prev],rt[now],l0,r0,l,r,x);}
    ll qr(pnode t,const int &il,const int &ir,const int &l,const int &r){
        flush(t,il,ir);
        if(l<=il&&ir<=r) return t->sum;
        if(il>r||ir<l) return 0;
        int mid=il+(ir-il>>1);
        return qr(t->L,il,mid,l,r)+qr(t->R,mid+1,ir,l,r);
    }
    ll qr(const int &now,const int &l,const int &r){return qr(rt[now],l0,r0,l,r);}
}t2;

ll play(int l,int r,int h){
    if(l>r) return 1;
    int mid=t1.qr(l,r);
    ll cnt=0;
    if(H[mid]<h) cnt=(t2.qr(r,H[mid]+1,h)-t2.qr(l-1,H[mid]+1,h))%md;
    return (cnt+(play(l,mid-1,H[mid])*play(mid+1,r,H[mid]))%md)%md;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i) cin>>H[i];
    int mx=0;
    vector<pii> vec;
    for(int i=1;i<=n;++i){
        int l,r; cin>>l>>r;
        vec.eb(l,r);
        mx=max(mx,r);
    }
    t2.build(n+5,1,mx);
    for(int i=1;i<=n;++i) t2.upd(i-1,i,vec[i-1].f,vec[i-1].s,1);
    t1=segment1(1,n);
    t1.build();
    cout<<play(1,n,mx);

    return 0;
}
