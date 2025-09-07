#include<bits/stdc++.h>
using namespace std;

template<class T>
struct SA{
  vector<int> sa,ra;
  SA(){}
  SA(const T &vec){ build(vec); }
  void build(const T &vec){
    int n=vec.size()+1;
    sa.resize(n),ra.resize(n);
    sa[0]=n-1;
    iota(sa.begin()+1,sa.end(),0);
    sort(sa.begin()+1,sa.end(),[&](const int &l,const int &r){
      return vec[l]<vec[r];
    });
    ra[sa[0]]=0, ra[sa[1]]=1;
    for(int i=2;i<n;++i) ra[sa[i]]=ra[sa[i-1]] + (vec[sa[i-1]]!=vec[sa[i]]);
    vector<int> cnt(n),sa2(n),ra2(n);
    for(int k=1;k<n;k<<=1){
      cnt.assign(n,0);
      for(int i=0;i<n;++i) ++cnt[ra[i]], sa[i]=(sa[i]-k+n)%n;
      for(int i=1;i<n;++i) cnt[i]+=cnt[i-1];
      for(int i=n-1;i>=0;--i) sa2[--cnt[ra[sa[i]]]]=sa[i];
      for(int i=1;i<n;++i) ra2[sa2[i]]=ra2[sa2[i-1]] + (ra[sa2[i-1]]!=ra[sa2[i]] || ra[(sa2[i-1]+k)%n]!=ra[(sa2[i]+k)%n]);
      swap(sa,sa2), swap(ra,ra2);
    }
  }
};

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  string s,p; cin>>s>>p;
  SA sa(s);

  int l=1,r=s.size();
  while(l<r){
    int mid=l+r>>1;
    if(s.substr(sa.sa[mid],p.size())<p) l=mid+1;
    else r=mid;
  }
  for(;l<=s.size() && sa.sa[l]+p.size()<=s.size() && s.substr(sa.sa[l],p.size())==p; ++l){
    cout<<sa.sa[l]<<"-"<<sa.sa[l]+(int)p.size()-1<<'\n';
  }
}
