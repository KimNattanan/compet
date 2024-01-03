#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
 
int dp[55][35005],a[35005],freq[35005];
int cl,cr,cost;
void slide(int l,int r){
    while(cl<l){
        if(--freq[a[cl++]]==0) --cost;
    }
    while(cl>l){
        if(++freq[a[--cl]]==1) ++cost;
    }
    while(cr<r){
        if(++freq[a[++cr]]==1) ++cost;
    }
    while(cr>r){
        if(--freq[a[cr--]]==0) --cost;
    }
}
void play(int l,int r,int optl,int optr,int k){
    if(l>r) return;
    int mid=l+(r-l>>1);
    pair<int,int> best(0,0);
    for(int i=optl;i<=min(mid,optr);++i){
        slide(i,mid);
        best=max(best,pair<int,int>(dp[k-1][i-1]+cost,i));
    }
    dp[k][mid]=best.first;
    play(l,mid-1,optl,best.second,k);
    play(mid+1,r,best.second,optr,k);
}
 
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    int n,K; cin>>n>>K;
    int cnt=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        if(freq[a[i]]==0) ++cnt;
        dp[1][i]=cnt;
        ++freq[a[i]];
    }
    cl=1,cr=n,cost=cnt;
    for(int k=2;k<=K;++k){
        play(k,n,k,n,k);
    }
    cout<<dp[K][n];
 
    return 0;
}
