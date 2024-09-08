#include<bits/stdc++.h>
using namespace std;

int cnt[3],a[100005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
    while(Q--){
        int n,m; cin>>n>>m;
        // cnt[0]=cnt[1]=cnt[2]=0;
        // for(int i=1;i<=n;++i){
        //     int x; cin>>x;
        //     ++cnt[x%3];
        // }
        // int ans=(n%3==0);
        // if(cnt[1]%3==0){
        //     if(cnt[2]%3==0) ans+=m;
        // }
        // else if(cnt[1]%3==1){
        //     if(cnt[2]%3==2) ans+=m/2;
        //     else ans+=(m+1)/2;
        // }
        // else{
        //     if(cnt[2]%3==1) ans+=m/2;
        //     else ans+=(m+1)/2;
        // }
        int ans=0;
        for(int i=1;i<=n;++i) cin>>a[i];
        for(int k=0;k<=m;++k){
            int sum=0;
            for(int i=1;i<=n;++i){
                int x=1;
                // for(int j=0;j<k;++j) x=(x*a[i])%3;
                if(k==0) x=1;
                else if(a[i]%3==0) x=0;
                else if(a[i]%3==1) x=1;
                else if(k&1) x=2;
                else x=1;
                sum=(sum+x)%3;
            }
            if(sum%3==0) ++ans;
        }
        cout<<ans<<'\n';
    }
    
}
/*

1<=Q,N,M<=1e2

1<=N<=1e2
1<=M<=1e3

1<=Q<=1e3
1<=N<=1e5
1<=M<=1e9

2
5 5
1 2 3 4 5
10 4219
12 88 35 18 9 43 12 47 104 44

3
2109

k=1 ;  1 +  2 +   3 +    4 +    5 =   15
k=3 ;  1 +  8 +  27 +   64 +  125 =  225
k=5 ;  1 + 32 + 243 + 1024 + 3125 = 4425

*/
