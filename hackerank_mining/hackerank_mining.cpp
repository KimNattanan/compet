#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back

const int inf=1e9+7;
const int md=1e9+7;

ll X[5005],W[5005],cost[5005][5005];
ll W0[5005],WX0[5005];
int opt0[5005][5005];

ll dp0[5005][2];

void play(int l,int r,int optl,int optr,int z){
    if(l>r) return;
    int mid=l+(r-l>>1);
    pair<ll,int> best={LLONG_MAX,-1};
    for(int k=optl;k<=min(mid,optr);++k){
        best=min(best,{dp0[k-1][!z]+cost[k][mid],k});
    }
    dp0[mid][z]=best.f;
    play(l,mid-1,optl,best.s,z);
    play(mid+1,r,best.s,optr,z);
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,K; cin>>n>>K;
    for(int i=1;i<=n;++i){
        cin>>X[i]>>W[i];
        W0[i]=W[i]+W0[i-1];
        WX0[i]=W[i]*X[i]+WX0[i-1];
    }
    for(int len=1;len<=n;++len){
        for(int i=1,j=len;j<=n;++i,++j){
            if(len==1){
                cost[i][j]=0;
                opt0[i][j]=i;
                continue;
            }
            pair<ll,int> best={LLONG_MAX,-1};
            for(int k=opt0[i][j-1];k<=opt0[i+1][j];++k){
                best=min(best,{X[k]*(W0[k-1]-W0[i-1]-W0[j]+W0[k])+WX0[j]-WX0[k]-WX0[k-1]+WX0[i-1],k});
            }
            cost[i][j]=best.f;
            opt0[i][j]=best.s;
        }
    }
    for(int i=1;i<=n;++i) dp0[i][1]=cost[1][i];
    for(int k=2;k<=K;++k){
        play(k,n,k,n,k%2);
    }
    cout<<dp0[n][K%2]<<endl;

    return 0;
}
/**

-Xk*(sumWr)+sumWXr+Xk*(sumWl)-sumWXl

Xk(sumWl-sumWr)+sumWXr-sumWXl

*/
// https://www.hackerrank.com/contests/world-codesprint-5/challenges/mining/problem
