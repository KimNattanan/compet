#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const ll md=1e9+7;

ll dp[505][505],dp2[505][505];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    if(n&1){
        cout<<0;
        return 0;
    }
    string s; cin>>s;
    s=" "+s;
    for(int i=1;i<n;++i){
        if(s[i]=='(') dp[i][i+1]=dp2[i][i+1]=(s[i+1]==')'||s[i+1]=='?');
        else if(s[i]=='[') dp[i][i+1]=dp2[i][i+1]=(s[i+1]==']'||s[i+1]=='?');
        else if(s[i]=='?') dp[i][i+1]=dp2[i][i+1]=(s[i+1]=='?'?2:(s[i+1]==')'||s[i+1]==']'));
    }
    for(int k=4;k<=n;++k){
        for(int l=1,r=k;r<=n;++l,++r){
            ll tmp=0;
            if(s[l]=='?'){
                if(s[r]=='?') tmp=(dp[l+1][r-1]<<1)%md;
                else if(s[r]==')'||s[r]==']') tmp=dp[l+1][r-1];
            }
            else if(s[r]=='?'&&(s[l]=='('||s[l]=='[')) tmp=dp[l+1][r-1];
            else if(s[l]=='('&&s[r]==')'||s[l]=='['&&s[r]==']') tmp=dp[l+1][r-1];
            dp[l][r]=dp2[l][r]=tmp;

            for(int i=l+2;i<r;i+=2){
                dp[l][r]=(dp[l][r]+( dp2[l][i-1]*dp[i][r] )%md)%md;
            }
        }
    }
    cout<<dp[1][n];

}
