#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
#define f first
#define s second

struct fenwick{
	array<int,300005> freq;
	vector<int> bit;
	void init(int n){
		bit.assign(n,0);
		for(int i=0;i<=n;++i) freq[i]=0;
	}
	void insert(int i){
		if(++freq[i]==1) upd(i,1);
	}
	void erase(int i){
		if(--freq[i]==0) upd(i,-1);
	}
	void upd(int i,int x){ for(;i<bit.size();i+=i&-i) bit[i]+=x; }
	int qr(int i){
		int ret=0;
		for(;i>0;i-=i&-i) ret+=bit[i];
		return ret;
	}
}trow,tcol;

struct fenwick2{
	vector<int> bit;
	void init(int n){ bit.assign(n,0); }
	void upd(int i,int x){ for(;i<bit.size();i+=i&-i) bit[i]+=x; }
	int qr(int i){
		int ret=0;
		for(;i>0;i-=i&-i) ret+=bit[i];
		return ret;
	}
}trow_all,tcol_all;

int qi[300005], qj[300005];
set<int> row[300005], col[300005];

void solve(){
	int n,m,Q;
	cin >> n >> m >> Q;
	vector<int> row_comp, col_comp;
	for(int i=1;i<=Q;++i){
		cin >> qi[i] >> qj[i];
		row_comp.emplace_back(qi[i]), col_comp.emplace_back(qj[i]);
	}
	sort(row_comp.begin(),row_comp.end());
	row_comp.erase(unique(row_comp.begin(),row_comp.end()),row_comp.end());
	sort(col_comp.begin(),col_comp.end());
	col_comp.erase(unique(col_comp.begin(),col_comp.end()),col_comp.end());
	for(int i=1;i<=row_comp.size();++i) row[i].clear();
	for(int i=1;i<=col_comp.size();++i) col[i].clear();
	trow.init(row_comp.size()+5);
	tcol.init(col_comp.size()+5);
	trow_all.init(col_comp.size()+5);
	tcol_all.init(row_comp.size()+5);
	auto ID=[&](vector<int> &comp,int x){
		return upper_bound(comp.begin(),comp.end(),x)-comp.begin();
	};
	auto qr_row=[&](int qi_id){
		if(row[qi_id].empty()) return tcol_all.qr(qi_id);
		int l=*row[qi_id].begin(), r=*row[qi_id].rbegin();
		return l-1 + m-r -(tcol.qr(ID(col_comp,l)-1)-tcol.qr(ID(col_comp,r))+tcol.qr(ID(col_comp,m)));
	};
	auto qr_col=[&](int qj_id){
		if(col[qj_id].empty()) return trow_all.qr(qj_id);
		int l=*col[qj_id].begin(), r=*col[qj_id].rbegin();
		return l-1 + n-r -(trow.qr(ID(row_comp,l)-1)-trow.qr(ID(row_comp,r))+trow.qr(ID(row_comp,n)));
	};
	auto add_all=[&](fenwick2 &fw,set<int> &s,vector<int> &comp,int x){
		if(s.empty()) return;
		int l=*s.begin(), r=*s.rbegin();
		fw.upd(1,x);
		fw.upd(ID(comp,l),-x);
		fw.upd(ID(comp,r)+1,x);
	};
	ll ans=0;
	for(int i=1;i<=Q;++i){
		int qi_id=ID(row_comp,qi[i]);
		int qj_id=ID(col_comp,qj[i]);
		add_all(trow_all,row[qi_id],col_comp,-1);
		add_all(tcol_all,col[qj_id],row_comp,-1);
		ans-=qr_row(qi_id)+qr_col(qj_id);
		if(row[qi_id].find(qj[i])==row[qi_id].end()){
			row[qi_id].emplace(qj[i]);
			col[qj_id].emplace(qi[i]);
			trow.insert(qi_id);
			tcol.insert(qj_id);
		}
		else{
			row[qi_id].erase(qj[i]);
			col[qj_id].erase(qi[i]);
			trow.erase(qi_id);
			tcol.erase(qj_id);
			if(row[qi_id].empty()&&!col[qj_id].empty()){
				if(qi[i]<*col[qj_id].begin()||qi[i]>*col[qj_id].rbegin()) --ans;
			}
			else if(!row[qi_id].empty()&&col[qj_id].empty()){
				if(qj[i]<*row[qi_id].begin()||qj[i]>*row[qi_id].rbegin()) --ans;
			}
		}
		add_all(trow_all,row[qi_id],col_comp,1);
		add_all(tcol_all,col[qj_id],row_comp,1);
		ans+=qr_row(qi_id)+qr_col(qj_id);
		cout << ans << "\n";
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
}
