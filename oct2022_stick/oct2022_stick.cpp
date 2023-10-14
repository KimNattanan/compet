#include "stick.h"
#include<bits/stdc++.h>
using namespace std;
#define pb push_back

int n;
vector<int> vec0;
const int K=50;

struct A{
    vector<A> adj;
    int l,r,mid,sz;
    vector<int> vec;
    A(int l_=0,int r_=0){
        l=l_,r=r_,mid=l+(r-l>>1),sz=r-l+1;
    }
    void build(){
        if(l==r){
            vec.pb(vec0[l]);
            return;
        }
        adj.emplace_back(l,mid);
        adj.emplace_back(mid+1,r);
        adj[0].build();
        adj[1].build();
        int L=0,R=0;
        while(L<adj[0].vec.size()&&R<adj[1].vec.size()&&vec.size()<K){
            if(adj[0].vec[L]>adj[1].vec[R]) vec.pb(adj[0].vec[L++]);
            else vec.pb(adj[1].vec[R++]);
        }
        while(vec.size()<K&&L<adj[0].vec.size()) vec.pb(adj[0].vec[L++]);
        while(vec.size()<K&&R<adj[1].vec.size()) vec.pb(adj[1].vec[R++]);
    }
    vector<int> query(int l0,int r0){
        if(l0<=l&&r<=r0) return vec;
        if(l0>r||r0<l) return {};
        vector<int> vl=adj[0].query(l0,r0),vr=adj[1].query(l0,r0);
        int L=0,R=0;
        vector<int> ans;
        while(ans.size()<K&&L<vl.size()&&R<vr.size()){
            if(vl[L]>vr[R]) ans.pb(vl[L++]);
            else ans.pb(vr[R++]);
        }
        while(ans.size()<K&&L<vl.size()) ans.pb(vl[L++]);
        while(ans.size()<K&&R<vr.size()) ans.pb(vr[R++]);
        return ans;
    }
};

A tree;

void init(int N, std::vector<int> X){
    n=N,vec0=X;
    tree=A(0,N-1);
    tree.build();
    return;
}

int max_length(int L,int R){
    if(R-L+1<3) return -1;
    vector<int> ans=tree.query(L,R);
    int c=-1,b=-1,a=-1;
    for(auto &e:ans){
        if(c==-1) c=e;
        else if(b==-1) b=e;
        else{
            if(a==-1) a=e;
            else c=b,b=a,a=e;
            if(a+b>c) return a+b+c;
        }
    }
    return -1;
}
