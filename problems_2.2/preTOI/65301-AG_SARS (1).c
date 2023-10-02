#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

#define int ll

const ll md=1e9+7;
const ll inf=1e18+7;

struct A{
    int l,r,cnt,k;
    bool operator<(const A&o)const{
        if(k==o.k) return cnt>o.cnt;
        return k>o.k;
    }
};

int a[2007],p[2007],dp[2007][2007];
int cnt[2007];
int adj[2007][2];
int K;

int f(int a,int b){
    return max(0LL,(abs(a-b)-1LL)/K);
}

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>K>>Q;
    for(int i=1;i<=n;i++) cin>>a[i];
    int idx=1;
    p[1]=1;
    cnt[1]=1;
    for(int i=2;i<=n;i++){
        if(a[i]-a[i-1]<=K) p[i]=idx,cnt[idx]++;
        else{
            p[i]=++idx;
            cnt[idx]=1;
            adj[idx][0]=adj[idx-1][1]=f(a[i],a[i-1]);
        }
    }
    memset(dp,0x3f,sizeof dp);
    for(int i=1;i<=idx;i++){

        for(int j=0;j<=cnt[i];j++){
            dp[i][j]=0;
        }

        int temp=cnt[i];
        ll w=0;
        for(int j=i+1;j<=idx;j++){
            int temp2=temp+cnt[j];
            w+=adj[j][0];
            for(int k=i;k<=j;k++){
                dp[k][temp2]=min(dp[k][temp2],w);
            }
            temp=temp2;
        }

//        int itr=cnt[i]+1;
//        priority_queue<A> pq;
//        if(i>1) pq.push({i-1,i,cnt[i]+cnt[i-1],adj[i][0]});
//        if(i<idx) pq.push({i,i+1,cnt[i]+cnt[i+1],adj[i][1]});
//        while(itr<=n){
//            int l=pq.top().l;
//            int r=pq.top().r;
//            int j=pq.top().cnt;
//            int k=pq.top().k;
//            pq.pop();
//            if(j<itr) continue;
//            for(;itr<=j;itr++) dp[i][itr]=k;
//            if(l>1&&dp[i][j+cnt[l-1]]>k+adj[l][0])
//                pq.push({l-1,l,j+cnt[l-1],k+adj[l][0]});
//            if(r<idx&&dp[i][j+cnt[r+1]]>k+adj[r][1])
//                pq.push({l,r+1,j+cnt[r+1],k+adj[r][1]});
//        }
    }
    for(int i=1;i<=idx;i++){
        for(int j=n;j>=1;j--){
            dp[i][j]=min(dp[i][j],dp[i][j+1]);
        }
    }
    while(Q--){
        int x,k; cin>>x>>k; x++;
        x=p[x];
        int ans=upper_bound(dp[x],dp[x]+n+1,k)-dp[x]-1;
        cout<<ans<<endl;
    }

	return 0;
}
/**

5 2 4
4 7 12 13 19
0 1
3 0
4 2
2 4

2 4 5
2 19
0 0
0 1
0 2
0 3
0 4

*/
