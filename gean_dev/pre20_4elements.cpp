#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
#define f first
#define s second
 
using A=pair<ll,ll>;
bool cmpX(const A &l,const A &r){return l.f<r.f;}
bool cmpY(const A &l,const A &r){return l.s<r.s;}
 
A p[100005], tmp[100005];
 
ld play(int l,int r){
	if(r-l+1<=3){
		ld ret=LDBL_MAX;
		for(int i=l;i<=r;++i) for(int j=i+1;j<=r;++j) ret=min(ret,(ld)(p[i].f-p[j].f)*(p[i].f-p[j].f)+(ld)(p[i].s-p[j].s)*(p[i].s-p[j].s));
		return ret;
	}
	int m=l+r>>1, N=0;
	ld mn=min(play(l,m), play(m+1,r));
	for(int i=l;i<=r;++i) if((ld)(p[i].f-p[m].f)*(p[i].f-p[m].f) < mn) tmp[N++]=p[i];
	sort(tmp,tmp+N,cmpY);
	for(int i=0;i<N;++i) for(int j=i+1;(ld)(tmp[i].s-tmp[j].s)*(tmp[i].s-tmp[j].s)<mn && j<N;++j) mn=min(mn,(ld)(tmp[i].f-tmp[j].f)*(tmp[i].f-tmp[j].f)+(ld)(tmp[i].s-tmp[j].s)*(tmp[i].s-tmp[j].s));
	return mn;
}
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	int n; cin>>n;
	for(int i=1;i<=n;++i) cin>>p[i].f;
	for(int i=1;i<=n;++i) cin>>p[i].s;
	for(int i=1,x;i<=n;++i) cin>>x, p[i].f-=x;
	for(int i=1,x;i<=n;++i) cin>>x, p[i].s-=x;
	for(int i=1;i<=n;++i) p[i].f+=p[i-1].f, p[i].s+=p[i-1].s;
	sort(p,p+n+1,cmpX);
	cout<<fixed<<setprecision(0)<<play(0,n);
 
	return 0;
}
