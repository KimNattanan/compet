#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define ll long long

//#define int ll

const int inf=1e9+7;
const int md=1e9+7;

int W[4005][4005];
int sum[4005][4005],sum2[4005][4005];
int dp[4005][805];

void play(int l,int r,int optl,int optr,int k){
    if(l>r) return;
    int mid=l+(r-l>>1);
    pair<int,int> best={INT_MAX,-1};
    for(int i=optl;i<=min(mid,optr);++i){
        best=min(best,{dp[i-1][k-1]+sum[i][mid],i});
    }
    dp[mid][k]=best.f;
    int opt=best.s;
    play(l,mid-1,optl,opt,k);
    play(mid+1,r,opt,optr,k);
}


void fastscan(int &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register int c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    if (c=='-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

int32_t main(){
//    ios::sync_with_stdio(false); cin.tie(0);

    int n,K;
    fastscan(n);
    fastscan(K);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            fastscan(W[i][j]);
            sum2[i][j]=sum2[i][j-1]+W[i][j];
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            sum[i][j]=sum[i][j-1]+sum2[j][j]-sum2[j][i-1];
        }
        dp[i][1]=dp[i-1][1]+sum2[i][i];
    }
    for(int k=2;k<=K;++k){
        play(1,n,1,n,k);
    }
    printf("%d",dp[n][K]);

    return 0;
}
/**

8 3
0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1
1 1 1 0 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 1 1 0 1 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 0

*/
