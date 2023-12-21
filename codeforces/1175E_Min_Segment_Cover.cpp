#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

struct fenwick{
	vector<pii> bit;
	void init(int n){
		bit=vector<pii>(n,pii(1e9,0));
	}
	void add(int i,pii x){
		for(;i<bit.size();i+=i&-i) bit[i]=min(bit[i],x);
	}
	pii qr(int i){
		pii ret(1e9,0);
		for(;i>0;i-=i&-i) ret=min(ret,bit[i]);
		return ret;
	}
}fw;
pii dp[200005][25];

int qr(int u,int l){
	int ans=1;
	for(int i=20;i>=0;--i){
		if(dp[u][i].f<=l) continue;
		u=dp[u][i].s;
		ans+=(1<<i);
	}
	if(dp[u][0].f>l) return -1;
	return ans+1;
}

int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	
	int n,Q; cin>>n>>Q;
	vector<pii> vec(n);
	for(auto &e:vec) cin>>e.f>>e.s;
	sort(vec.begin(),vec.end(),[&](const pii &l,const pii &r){
		if(l.s!=r.s) return l.s<r.s;
		return l.f<r.f;
	});
	fw.init(5e5+5);
	for(int i=0;i<n;++i){
		dp[i+1][0]=fw.qr(5e5-vec[i].f+1);
		if(!dp[i+1][0].s||dp[i+1][0].f>=vec[i].f) dp[i+1][0]=pii(vec[i].f,i+1);
		fw.add(5e5-vec[i].s+1,pii(vec[i].f,i+1));
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<25;++j){
			dp[i][j]=dp[dp[i][j-1].s][j-1];
		}
	}
	while(Q--){
		int l,r; cin>>l>>r;
		pii u=fw.qr(5e5-r+1);
		if(u.f>r){cout<<-1<<endl;continue;}
		if(u.f<=l){cout<<1<<endl;continue;}
		cout<<qr(u.s,l)<<endl;
	}

	return 0;
}
