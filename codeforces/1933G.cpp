#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()
 
const ll md=998244353;
 
bool ok[8];
 
void solve(){
    int n,m,Q; cin>>n>>m>>Q;
    
    for(int i=0;i<8;++i) ok[i]=1;
    cout<<8<<endl;
 
    while(Q--){
        int r,c; cin>>r>>c;
        string s; cin>>s;
        bool x=(s=="circle"),tmp;
 
        tmp=(c+1>>1)&1;
        ok[0]&=1^tmp^(x==!(r&1)), ok[1]&=1^tmp^(x==(r&1));
 
        tmp=(r+1>>1)&1;
        ok[2]&=1^tmp^(x==!(c&1)), ok[3]&=1^tmp^(x==(c&1));
 
        tmp=c&1;
        ok[4]&=1^tmp^(x==((r>>1)&1)), ok[5]&=1^tmp^(x!=((r>>1)&1));
 
        tmp=r&1;
        ok[6]&=1^tmp^(x==((c>>1)&1)), ok[7]&=1^tmp^(x!=((c>>1)&1));
 
        int ans=0;
        for(int i=0;i<8;++i) ans+=ok[i];
        cout<<ans<<endl;
 
    }
}
 
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    int Q(1);
    cin>>Q;
    while(Q--){
        solve();
    }
}
