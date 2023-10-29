#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back
#include "fatigue.h"

const ll inf=1e9+7;

int N;
struct AA{
    int i;
    ll a,w;
    bool operator<(const AA&o)const{
        return a<o.a;
    }
};
vector<AA> vec;
int mp[100005];
ll dp0[100005],dp1[100005];

struct BB{
    vector<BB> child;
    int l,r;
    int mn,mx;
    BB(int l_=0,int r_=0){
        l=l_,r=r_;
        mn=INT_MAX;
        mx=0;
    }
    void build(){
        if(l==r) return;
        int mid=(l+(r-l>>1));
        child.emplace_back(l,mid);
        child.emplace_back(mid+1,r);
        child[0].build(),child[1].build();
    }
    void upd(int i,int x){
        if(l==r) return void(mn=mx=x);
        if(i<=(l+(r-l>>1))) child[0].upd(i,x);
        else child[1].upd(i,x);
        mn=min(child[0].mn,child[1].mn);
        mx=max(child[0].mx,child[1].mx);
    }
    pii query(int l0,int r0){
        if(l0<=l&&r<=r0) return {mn,mx};
        if(l>r0||r<l0) return {INT_MAX,0};
        pii aL=child[0].query(l0,r0);
        pii aR=child[1].query(l0,r0);
        return {min(aL.f,aR.f),max(aL.s,aR.s)};
    }
}tree;

void add(int i,ll x){
    ++i;
    for(;i<=N;i+=i&-i) dp0[i]+=x;
}
void add2(int i,ll x){
    ++i;
    for(;i<=N;i+=i&-i) dp1[i]+=x;
}
ll f(int l,int r){
    ll sum=0;
    for(int i=r+1;i>0;i-=i&-i) sum+=dp0[i];
    for(int i=l;i>0;i-=i&-i) sum-=dp0[i];
    return sum;
}
ll g(int l,int r){
    ll sum=0;
    for(int i=r+1;i>0;i-=i&-i) sum+=dp1[i];
    for(int i=l;i>0;i-=i&-i) sum-=dp1[i];
    return sum;
}
ll play(int l,int r,int mid){
    return f(l,mid)*vec[mid].a-g(l,mid) + g(mid,r)-f(mid,r)*vec[mid].a;
}

void initialize(int N, std::vector<int> A, std::vector<int> W){
    ::N=N;
    for(int i=0;i<N;++i){
        vec.pb({i,A[i],W[i]});
    }
    sort(vec.begin(),vec.end());
    add(0,vec[0].w);
    add2(0,vec[0].w*vec[0].a);
    mp[vec[0].i]=0;
    tree=BB(0,N-1);
    tree.build();
    tree.upd(vec[0].i,0);
    for(int i=1;i<N;++i){
        add(i,vec[i].w);
        add2(i,vec[i].w*vec[i].a);
        mp[vec[i].i]=i;
        tree.upd(vec[i].i,i);
    }
    return;
}

void change_weight(int X, int V){
    ll x=V-vec[mp[X]].w;
    ll y=V*vec[mp[X]].a-vec[mp[X]].w*vec[mp[X]].a;
    vec[mp[X]].w+=x;
    add(mp[X],x);
    add2(mp[X],y);
    return;
}
long long point_fatigue(std::vector<int> B){

    int l0=INT_MAX,r0=0;
    for(auto &e:B) l0=min(l0,mp[e]),r0=max(r0,mp[e]);
    while(l0>0&&vec[l0].a==vec[l0-1].a) --l0;
    while(r0<N-1&&vec[r0].a==vec[r0+1].a) ++r0;


    pair<int,ll> L={l0,vec[l0].w},R={r0,vec[r0].w};

    int l=l0,r=r0;
    while(l<r){
        int mid=l+(r-l>>1);
        if(f(l0,mid)>f(mid,r0)) r=mid;
        else l=mid+1;
    }

    ll ans=play(l0,r0,l);
    if(l-1>=l0) ans=min(ans,play(l0,r0,l-1));

    return ans;
}
long long interval_fatigue(std::vector<std::vector<int>> In){


    int l0=INT_MAX,r0=0;
    for(auto &e:In){
        pii temp=tree.query(e[0],e[1]);
        l0=min(l0,temp.f);
        r0=max(r0,temp.s);
    }

    while(l0>0&&vec[l0].a==vec[l0-1].a) --l0;
    while(r0<N-1&&vec[r0].a==vec[r0+1].a) ++r0;

    pair<int,ll> L={l0,vec[l0].w},R={r0,vec[r0].w};

    int l=l0,r=r0;
    while(l<r){
        int mid=l+(r-l>>1);
        if(f(l0,mid)>f(mid,r0)) r=mid;
        else l=mid+1;
    }

    ll ans=play(l0,r0,l);
    if(l-1>=l0) ans=min(ans,play(l0,r0,l-1));

    return ans;
}










//
//#include <cstdio>
//#include <vector>
//#include "fatigue.h"
//int main() {
//    ios::sync_with_stdio(false); cin.tie(0);
//    int N,M;
//    scanf("%d %d",&N,&M);
//    std::vector<int> A(N), W(N);
//    for(int i = 0;i < N;i++) {
//        scanf("%d",&A[i]);
//    }
//    for(int i = 0;i < N;i++) {
//        scanf("%d",&W[i]);
//    }
//    initialize(N,A,W);
//    std::vector<long long> Answer;
//    for(int i = 0;i < M;i++) {
//        int e;
//        scanf("%d",&e);
//        if(e==1) {
//            int X,V;
//            scanf("%d %d",&X,&V);
//            change_weight(X,V);
//        } else if(e==2) {
//            int p;
//            scanf("%d",&p);
//            std::vector<int> B(p);
//            for(int j = 0;j < p;j++) {
//                scanf("%d",&B[j]);
//            }
//            Answer.push_back(point_fatigue(B));
//        } else {
//            int q;
//            scanf("%d",&q);
//            std::vector<std::vector<int>> In(q,std::vector<int>(2));
//            for(int j = 0;j < q;j++) {
//                scanf("%d %d",&In[j][0],&In[j][1]);
//            }
//            Answer.push_back(interval_fatigue(In));
//        }
//    }
//    for(int i = 0;i < Answer.size();i++){
//        printf("%lld\n",Answer[i]);
//    }
//}
