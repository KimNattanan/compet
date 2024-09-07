#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll a[400005];
int p[400005][19];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,k; cin>>n>>k;
    for(int i=1;i<=n;++i) cin>>a[i],a[i+n]=a[i];
    for(int i=1;i<=2*n;++i) a[i]+=a[i-1];
    for(int i=0;i<=18;++i) p[0][i]=-1;
    ll l=1,r=2e9;
    while(l<r){
        ll mid=l+(r-l+1>>1);
        for(int i=1;i<=2*n;++i){
            int id=upper_bound(a,a+i,a[i]-mid)-a-1;
            p[i][0]=id;
            for(int j=1;j<=18;++j){
                if(p[i][j-1]==-1) p[i][j]=-1;
                else p[i][j]=p[p[i][j-1]][j-1];
            }
        }
        int cnt=0;
        for(int i=n+1;i<=2*n;++i){
            int cur=i;
            for(int j=18;cur!=-1&&j>=0;--j){
                if(k>>j&1) cur=p[cur][j];
            }
            if(cur!=-1 && cur>=i-n) ++cnt;
        }
        if(cnt==0) r=mid-1;
        else l=mid;
    }
    for(int i=1;i<=2*n;++i){
        int id=upper_bound(a,a+i,a[i]-l)-a-1;
        p[i][0]=id;
        for(int j=1;j<=18;++j){
            if(p[i][j-1]==-1) p[i][j]=-1;
            else p[i][j]=p[p[i][j-1]][j-1];
        }
    }
    int cnt=0;
    for(int i=n+1;i<=2*n;++i){
        int cur=i;
        for(int j=18;cur!=-1&&j>=0;--j){
            if(k>>j&1) cur=p[cur][j];
        }
        if(cur!=-1 && cur>=i-n) ++cnt;
    }
    cout<<l<<" "<<n-cnt;
    
}
