#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back

struct segment{
    struct node{
        node *L,*R;
        int l,r,mid,sum;
        node(int l_=0,int r_=0):L(nullptr),R(nullptr),l(l_),r(r_),mid(l+(r-l>>1)),sum(0){}
    };
    using pnode=node*;
    vector<pnode> rt;

    void build(pnode &t,int l,int r){
        t=new node(l,r);
        if(t->l!=t->r) build(t->L,l,t->mid),build(t->R,t->mid+1,r);
    }
    void build(int n,int l,int r){
        rt=vector<pnode>(n+5);
        build(rt[0],l,r);
    }

    void upd(pnode prev, pnode &now,int i,int x){
        now=new node(*prev);
        if(now->l==now->r) return void(now->sum=prev->sum+x);
        if(i<=now->mid) upd(prev->L,now->L,i,x);
        else upd(prev->R,now->R,i,x);
        now->sum=now->L->sum+now->R->sum;
    }
    void upd(int prev,int now,int i,int x){upd(rt[prev],rt[now],i,x);}

    int qr(pnode now,int l,int r){
        if(l<=now->l&&now->r<=r) return now->sum;
        if(now->l>r||now->r<l) return 0;
        return qr(now->L,l,r)+qr(now->R,l,r);
    }
    int qr(int now,int l,int r){return qr(rt[now],l,r);}
}t;

int a[50005],pos[50005];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    vector<int> vec;
    for(int i=1;i<=n;++i) cin>>a[i],vec.eb(a[i]);
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    for(int i=1;i<=n;++i) a[i]=upper_bound(vec.begin(),vec.end(),a[i])-vec.begin();
    t.build(n,1,n);
    for(int i=1;i<=n;++i){
        t.upd(i-1,i,i,1);
        if(pos[a[i]]!=0) t.upd(i,i,pos[a[i]],-1);
        pos[a[i]]=i;
    }
    int k=1;
    while(Q--){
        int x; cin>>x;
        if(x>k) swap(x,k);
        int now=t.qr(k,x,k);
        if(x==0) now=k+1; // ??
        k=(now+1)%n;
        cout<<now<<endl;
    }

    return 0;
}
