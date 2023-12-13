#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;

const ll md=998244353;

ll a,b,c[4],d[4];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i){
        int x; cin>>x;
        x&=1;
        if(x){
            if(i>=3){
                auto [d0,d1,d2,d3]=d;
                d[1]=(d1+d2+c[2])%md;
                d[3]=(d3+d1+c[1])%md;
            }
            c[1]=(c[1]+a)%md;
            c[3]=(c[3]+b)%md;
            ++b;
        }
        else{
            if(i>=3){
                auto [d0,d1,d2,d3]=d;
                d[0]=(d0+d0+c[0])%md;
                d[2]=(d2+d3+c[3])%md;
            }
            c[0]=(c[0]+a)%md;
            c[2]=(c[2]+b)%md;
            ++a;
        }
    }
    cout<<(d[0]+d[1]+d[2]+d[3])%md<<endl;

    return 0;
}
