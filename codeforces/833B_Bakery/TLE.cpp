#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back

struct segment{
    struct node{
        node *L,*R;
        int l,r,mid,sum;
        node(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)),L(nullptr),R(nullptr),sum(0){}
    };
    using pnode=node*;
    vector<pnode> rt;
    void build(pnode &t,int l,int r){
        t=new node(l,r);
        if(l==r) return;
        build(t->L,l,t->mid),build(t->R,t->mid+1,r);
    }
    void build(int n,int l,int r){
        rt=vector<pnode>(n);
        build(rt[0],l,r);
    }
    void upd(pnode u,pnode &v,int i,int x){
        v=new node(*u);
        if(u->l==u->r) return void(v->sum=u->sum+x);
        if(i<=u->mid) upd(u->L,v->L,i,x);
        else upd(u->R,v->R,i,x);
        v->sum=v->L->sum+v->R->sum;
    }
    void upd(int v0,int v1,int i,int x){upd(rt[v0],rt[v1],i,x);}
    int qr(pnode u,int l0,int r0){
        if(l0<=u->l&&u->r<=r0) return u->sum;
        if(u->l>r0||u->r<l0) return 0;
        return qr(u->L,l0,r0)+qr(u->R,l0,r0);
    }
    int qr(int v0,int l0,int r0){return qr(rt[v0],l0,r0);}
}t;
int mx[35005],dp[55][35005];
void play(int l,int r,int optl,int optr,int k){
    if(l>r) return;
    int mid=l+(r-l>>1);
    pair<int,int> best(0,0);
    for(int i=optl;i<=min(mid,optr);++i){
        best=max(best,pair<int,int>(dp[k-1][i-1]+t.qr(mid,i,mid),i));
    }
    dp[k][mid]=best.first;
    play(l,mid-1,optl,best.second,k);
    play(mid+1,r,best.second,optr,k);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,K; cin>>n>>K;
    t.build(n+5,1,n);
    int cnt=0;
    for(int i=1;i<=n;++i){
        int x; cin>>x;
        t.upd(i-1,i,i,1);
        if(mx[x]!=0) t.upd(i,i,mx[x],-1);
        else ++cnt;
        dp[1][i]=cnt;
        mx[x]=i;
    }
    for(int k=2;k<=K;++k){
        play(k,n,k,n,k);
    }
    cout<<dp[K][n];

    return 0;
}
