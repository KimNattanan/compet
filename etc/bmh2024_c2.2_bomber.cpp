#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

using t4=tuple<int,int,int,int>;

int dif[1005][1005];
t4 a[10005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
    while(Q--){
        int n,m; cin>>n>>m;
        int k; cin>>k;
        for(int i=0;i<k;++i){
            int ii,jj,r; cin>>ii>>jj>>r;
            int i1=ii-r,i2=ii+r,j1=jj-r,j2=jj+r;
            i1=max(i1,1),j1=max(j1,1);
            i2=min(i2,n),j2=min(j2,m);
            a[i]=t4(i1,j1,i2,j2);
        }
        int l=0,r=k;
        while(l<r){
            int mid=l+r>>1;
            for(int i=1;i<=n;++i){
                for(int j=1;j<=m;++j) dif[i][j]=0;
            }
            for(int i=0;i<=mid;++i){
                auto &[i1,j1,i2,j2]=a[i];
                ++dif[i1][j1];
                --dif[i1][j2+1];
                --dif[i2+1][j1];
                ++dif[i2+1][j2+1];
            }
            bool ok=1;
            for(int i=1;ok&&i<=n;++i){
                for(int j=1;ok&&j<=m;++j){
                    dif[i][j]+=dif[i-1][j]+dif[i][j-1]-dif[i-1][j-1];
                    ok&=(dif[i][j]>0);
                }
            }
            if(ok) r=mid;
            else l=mid+1;
        }
        cout<<(l==k?-1:l+1)<<endl;
    }

    return 0;
}
