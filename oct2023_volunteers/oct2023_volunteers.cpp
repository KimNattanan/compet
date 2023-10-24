#include "volunteers.h"
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back

const int inf=1e9+7;

int a[20005][405];
int dp[20005][405];
int mxL[20005][405];
int N,M;

struct A{
    vector<A> child;
    int l,r,mid;
    pii mx;
    int mx2;
    A(int l_=0,int r_=0){
        l=l_,r=r_,mid=l+(r-l>>1);
        mx={0,0};
        mx2=0;
    }
    void build(){
        if(l==r){
            mx={dp[l][M],mxL[l][M]};
            mx2=mx.f+mx.s;
            return;
        }
        child.emplace_back(l,mid);
        child.emplace_back(mid+1,r);
        child[0].build(); child[1].build();
        mx=max(child[0].mx,child[1].mx);
        mx2=max(child[0].mx2,child[1].mx2);
    }
    int query1(int l0,int r0){
        if(l0>r0) return 0;
        if(l0<=l&&r<=r0) return mx2;
        if(l>r0||r<l0) return 0;
        return max(child[0].query1(l0,r0),child[1].query1(l0,r0));
    }
    int query2(int l0,int r0){
        if(l0>r0) return 0;
        if(l0<=l&&r<=r0) return mx.f;
        if(l>r0||r<l0) return 0;
        return max(child[0].query2(l0,r0),child[1].query2(l0,r0));
    }
}tree;

void setup_battalion(int N_, int M_, int Q, std::vector<std::vector<int>> H){
    N=N_,M=M_;
    for(int i=1;i<=N;++i){
        for(int j=1;j<=M;++j){
            a[i][j]=H[i-1][j-1];
        }
        sort(a[i]+1,a[i]+1+M,greater<int>());
    }
    for(int i=1;i<=N;++i){
        for(int j=1;j<=M;++j){
            int idx=upper_bound(a[i-1]+1,a[i-1]+1+M,a[i][j],greater<int>())-a[i-1]-1;
            dp[i][j]=dp[i-1][idx]+1;
            if(idx==0) mxL[i][j]=i;
            else mxL[i][j]=mxL[i-1][idx];
        }
    }
    tree=A(1,N);
    tree.build();
}
int count_volunteers(int L, int R) {
    ++L,++R;

    int ans=0;

    int l=L,r=R+1;
    while(l<r){
        int mid=l+(r-l>>1);
        if(mxL[mid][M]<L) l=mid+1;
        else r=mid;
    }
    ans=max(tree.query1(L,l-1)-L,tree.query2(l,R));


    return ans;
}

/**
5 1 1
1 3 5 10 3
4 4
*/


//int main() {
//  std::ios::sync_with_stdio(false);
//  std::cin.tie(0);
//  int N, M, Q;
//  std::cin >> N >> M >> Q;
//  std::vector<std::vector<int>> H;
//  H.resize(N);
//  for (int i = 0; i < N; i++) {
//    H[i].reserve(M);
//    int x;
//    for (int j = 0; j < M; j++) {
//      std::cin >> x;
//      H[i].push_back(x);
//    }
//  }
//  setup_battalion(N, M, Q, H);
//  while (Q--) {
//    int L, R;
//    std::cin >> L >> R;
//    std::cout << count_volunteers(L, R) << "\n";
//  }
//  std::cout << std::flush;
//  return 0;
//}
