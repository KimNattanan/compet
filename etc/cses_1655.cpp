#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)x.size()
#define add(x,y) ((((x)+(y))%md+md)%md)
#define Add(x,y) (x=add(x,y))
#define mul(x,y) ((((x)*(y))%md+md)%md)
#define Mul(x,y) (x=mul(x,y))
template<class T> T chmn(T &x,T y){ return x=min(x,y); }
template<class T> T chmx(T &x,T y){ return x=max(x,y); }
const int inf=1e9;
const ll linf=1e18;
const ll md=1e9+7;
// const ll md=119<<23|1;

struct trie{
  const int K=30;
  struct node{
    node *ch[2];
    node(){
      for(auto &e:ch) e=nullptr;
    }
  };
  using pnode=node*;
  pnode rt;
  trie():rt(new node()){}
  void insert(int x){
    pnode t=rt;
    for(int i=K;i>=0;--i){
      int j = x>>i&1;
      t = t->ch[j] ? t->ch[j] : t->ch[j]=new node();
    }
  }
  int qr(pnode t1,pnode t2,int x1,int x2,int i){
    if(i==-1) return x1^x2;
    int res=0;
    for(int j=0;j<2;++j) if(t1->ch[j]){
      if(t2->ch[!j]) chmx(res, qr(t1->ch[j],t2->ch[!j],x1^(j<<i),x2^((!j)<<i),i-1));
      else chmx(res, qr(t1->ch[j],t2->ch[j],x1^(j<<i),x2^(j<<i),i-1));
    }
    return res;
  }
  int qr(){ return qr(rt,rt,0,0,K); }
}t;

void solve(){
  int n; cin>>n;
  t.insert(0);
  for(int i=0,prv=0;i<n;++i){
    int x; cin>>x;
    t.insert(prv=(x^=prv));
  }
  cout<<t.qr();
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int Q(1);
  // cin>>Q;
  while(Q--) solve();

}
/*


*/