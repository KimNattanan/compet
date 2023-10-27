#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

const int inf=1e9;
const int md=29947;

int dp0[705][705];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int x,y,z; cin>>x>>y>>z; --x,--y,--z;
    for(int i=0;i<705;++i) dp0[i][0]=dp0[0][i]=1;
    for(int i=1;i<705;++i){
        for(int j=1;j<705;++j){
            dp0[i][j]=(dp0[i-1][j]+dp0[i][j-1])%md;
        }
    }
    int ans=dp0[y+z][x];
    for(int i=1;i<=y;++i){
        for(int j=1;j<=z;++j){
            ans=(ans+dp0[i-1][j-1]*dp0[x][y+z-i-j])%md;
        }
    }
    cout<<ans;

    return 0;
}
/**

*/
