#include "symbols.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

const ll md=20232566;

// edit this file as you like

int N,Q;
struct A{
    vector<A> child;
    int l,r,mid;
    int L;
    ll ans;
    A(int l_=0,int r_=0){
        l=l_,r=r_,mid=l+(r-l>>1);
        L=l;
        ans=0;
    }
    void build(){
        if(l==r) return void(ans=26);
        child.emplace_back(l,mid);
        child.emplace_back(mid+1,r);
        child[0].build();
        child[1].build();
        ans=(child[0].ans*child[1].ans)%md;
    }
    void upd(int i,int x){
        if(l==r){
            L=min(L,x);
            ans=26-l+L;
            return;
        }
        if(i<=mid) child[0].upd(i,x);
        else child[1].upd(i,x);
        ans=(child[0].ans*child[1].ans)%md;
    }
}tree;

void explore_site(int N, int Q) {
    ::N = N;
    ::Q = Q;
    tree=A(0,N-1);
    tree.build();
}
bool ok=1;
int retrieve_notes(int L, int R){
    if(R-L+1>26) ok=0;
    if(!ok) return 0;
    for(int i=L;i<=R;++i){
        tree.upd(i,L);
    }
    return tree.ans;
}



//int main() {
//  std::ios::sync_with_stdio(false);
//  std::cin.tie(0);
//  int n, q;
//  std::cin >> n >> q;
//  explore_site(n, q);
//  while (q--) {
//    int l, r;
//    std::cin >> l >> r;
//    std::cout << retrieve_notes(l, r) << std::endl;
//  }
//  return 0;
//}
