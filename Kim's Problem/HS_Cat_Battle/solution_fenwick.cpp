/*
    HS_CatBattle (fenwick)
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

const ll md=1e9+7;

struct fenwick{
	vector<ll> bit;
	void init(int n){bit.assign(n,0);}
	void upd(int i,int x){
		for(;i<bit.size();i+=i&-i) bit[i]=(bit[i]+x)%md;
	}
	ll qr(int i){
		ll ret=0;
		for(;i>0;i-=i&-i) ret=(ret+bit[i])%md;
		return ret;
	}
}fw;

vector<int> comp;
vector<pii> cat;

int main(){
    	ios::sync_with_stdio(false); cin.tie(0);

    	int n,m; cin>>n>>m;
    	for(int i=0;i<m;++i){
		int a,b; cin>>a>>b;
		cat.eb(a,b);
        	comp.push_back(b);
	}
	sort(comp.begin(),comp.end());
	comp.erase(unique(comp.begin(),comp.end()),comp.end());
	sort(cat.begin(),cat.end(),[&](const pii &l, const pii &r){
		if(l.f!=r.f) return l.f<r.f;
		return l.s>r.s;
	});
	for(auto &e:cat) e.s=lower_bound(comp.begin(),comp.end(),e.s)-comp.begin()+1;

	fw.init(comp.size()+5);
	for(auto &e:cat) fw.upd(e.s,fw.qr(e.s-1)+1);
    	cout<<fw.qr(comp.size());

    	return 0;
}
