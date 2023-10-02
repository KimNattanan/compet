#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define ll long long

//#define int ll

const int md=1e9-1;
const int inf=1e9+7;

int dp[45][80005];
int bit[45][80005];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,K; cin>>n>>K;
    for(int i=1;i<=n;++i){
        int x; cin>>x;
        dp[1][x]=(dp[1][x]+1)%md;
        for(int k=x;k<=n;k+=k&-k) bit[1][k]=(bit[1][k]+1)%md;
        for(int j=2;j<=K&&j<=i;++j){
            int sum=0;
            for(int k=n;k>0;k-=k&-k) sum=(sum+bit[j-1][k])%md;
            for(int k=x;k>0;k-=k&-k) sum=(sum-bit[j-1][k]+md)%md;
            dp[j][x]=sum;
            for(int k=x;k<=n;k+=k&-k) bit[j][k]=(bit[j][k]+dp[j][x])%md;
        }
    }
    int ans=0;
    for(int k=n;k>0;k-=k&-k) ans=(ans+bit[K][k])%md;
    cout<<ans;

    return 0;
}
/**

11 4
4 8 11 2 1 10 9 3 5 6 7

*/
