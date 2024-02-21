#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()

const int K[2]={1<<13,1<<12};

string s[10];
int mask[10][10],item[10][10],dp[2][1<<13];

bool check(int i,int j){
    return ( s[i][j]=='B' && s[i-1][j-1]=='B' && s[i-1][j+1]=='B' && s[i+1][j-1]=='B' && s[i+1][j+1]=='B' );
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    for(int i=2,m1=1,m2=1;i<=6;++i){
        for(int j=2;j<=6;++j){
            if((i+j)&1) mask[i][j]=m1,m1<<=1;
            else mask[i][j]=m2,m2<<=1;
        }
    }
    for(int i=1;i<=7;++i){
        for(int j=1;j<=7;++j) item[i][j]=mask[i][j]|mask[i-1][j-1]|mask[i-1][j+1]|mask[i+1][j-1]|mask[i+1][j+1];
    }

    int Q(1);
    cin>>Q;
    while(Q--){
        
        array<vector<int>,2> vec;
        array<int,2> m0({0,0});
        array<int,2> ans({49,49});
        for(int i=1;i<=7;++i){
            cin>>s[i];
            s[i]=" "+s[i];
        }
        for(int i=1;i<=7;++i){
            for(int j=1;j<=7;++j){
                if(s[i][j]=='B'){
                    int id=(i+j)&1;
                    vec[id].eb(item[i][j]);
                    if(check(i,j)) m0[id]|=mask[i][j];
                }
            }
        }
        for(int i=1;i<K[0];++i) dp[0][i]=dp[1][i]=49;
        for(int id=0;id<2;++id){
            for(int i=0;i<K[id];++i){
                if((i&m0[id])==m0[id]) ans[id]=min(ans[id],dp[id][i]);
                for(auto &e:vec[id]) dp[id][i|e]=min(dp[id][i|e],dp[id][i]+1);
            }
        }
        cout<<ans[0]+ans[1]<<endl;

    }
}
