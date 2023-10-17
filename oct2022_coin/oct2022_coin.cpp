
#include "coin.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
struct A{
    int i,sz,opr,b,i2; // 0:query  1:init
    bool operator<(const A&o)const{
        if(sz==o.sz) return opr<o.opr;
        return sz>o.sz;
    }
};

struct B{
    vector<B> adj;
    int l,r,mid;
    bool call; int lazy;
    int sum,mx;
    B(int l_=0,int r_=0,int sum_=0,int mx_=0){
        l=l_,r=r_,mid=l+(r-l>>1);
        sum=sum_,mx=mx_;
        call=lazy=0;
    }
    void build(){
        if(l==r) return;
        adj.emplace_back(l,mid);
        adj.emplace_back(mid+1,r);
        adj[0].build(),adj[1].build();
    }
    void upd(int x){
        if(l==r) return void(++sum);
        if(x<=mid) adj[0].upd(x);
        else adj[1].upd(x);
        sum=adj[0].sum+adj[1].sum;
    }
    int query2(int l0,int r0){
        if(l0<=l&&r<=r0) return sum;
        if(l>r0||r<l0) return 0;
        return adj[0].query2(l0,r0)+adj[1].query2(l0,r0);
    }
    int query(int l0,int x){ // x=b+1
        if(l==r) return l;
        if(mid<l0) return adj[1].query(l0,x);
        if(l>=l0){
            if(adj[0].sum<x) return adj[1].query(l0,x-adj[0].sum);
            return adj[0].query(l0,x);
        }
        int sumL=adj[0].query2(l0,mid);
        if(sumL<x) return adj[1].query(l0,x-sumL);
        return adj[0].query(l0,x);
    }
    void flush(){
        if(call){
            if(l!=r){
                adj[0].call=adj[1].call=1;
                adj[0].lazy+=lazy;
                adj[1].lazy+=lazy;
            }
            mx+=lazy;
            call=lazy=0;
        }
    }
    void upd0(int l0,int r0){
        flush();
        if(l0<=l&&r<=r0){
            call=1;
            ++lazy;
            flush();
            return;
        }
        if(l>r0||r<l0) return;
        adj[0].upd0(l0,r0);
        adj[1].upd0(l0,r0);
        mx=max(adj[0].mx,adj[1].mx);
    }
    int query0(int l0,int r0){
        flush();
        if(l0<=l&&r<=r0) return mx;
        if(l>r0||r<l0) return 0;
        return max(adj[0].query0(l0,r0),adj[1].query0(l0,r0));
    }
};

vector<A> vec;
int N,L;

void initialize(int N_,std::vector<int> Rail,int L_)
{
    N=N_,L=L_;
    for(int i=0;i<N;++i){
        vec.pb({i,Rail[i],1,0,0});
    }
    return;
}
std::vector<int> max_dist(std::vector<std::vector<int> > Coins)
{
    std::vector<int> Ans(Coins.size());

    for(int i=0;i<Coins.size();++i){
        vec.pb({Coins[i][0],Coins[i][2],0,Coins[i][1],i});
    }

    sort(vec.begin(),vec.end());
    B tree(0,N);
    tree.build();

    for(int i=0;i<vec.size();++i){
        if(vec[i].opr==1){
            tree.upd(vec[i].i);
            tree.upd0(max(0,vec[i].i-L+1),vec[i].i);
        }
        else{
            int pos=tree.query(vec[i].i,vec[i].b+1);
            if(pos>=N){
                Ans[vec[i].i2]=N;
                continue;
            }
            int b=vec[i].b+tree.query0(vec[i].i,pos);
            pos=tree.query(vec[i].i,b+1);

            Ans[vec[i].i2]=min(pos,N);
        }
    }

    return Ans;
}
/**

7 3 2
1 2 1 3 1 3 3
1 1 2
1 0 1
1 1 1

*/
