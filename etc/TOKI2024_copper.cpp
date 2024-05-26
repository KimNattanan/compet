#include "copper.h"
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
using ll=long long;
#define f first
#define s second
#define eb emplace_back

vector<int> A,a[100005],adj[100005];
int lm[200005],rm[200005],U[200005][20],D[200005][20],lv[100005],p[100005][19],p2[200005][20],p3[200005][20];
void dfs(int u,int p){
  lv[u]=lv[p]+1;
  ::p[u][0]=p;
  for(int i=1;i<19;++i) ::p[u][i]=::p[::p[u][i-1]][i-1];
  for(auto &e:a[u]){
    if(u==p) p2[e][0]=p3[e][0]=e;
    else{
      int id=lower_bound(a[p].begin(),a[p].end(),e)-a[p].begin();
      if(id!=a[p].size()) p2[e][0]=a[p][id];
      else p2[e][0]=e;
      --id;
      if(id!=-1) p3[e][0]=a[p][id];
      else p3[e][0]=e;
    }
  }
  for(int i=1;i<20;++i){
    for(auto &e:a[u]){
      p2[e][i]=p2[p2[e][i-1]][i-1];
      p3[e][i]=p3[p3[e][i-1]][i-1];
    }
  }
  for(auto &e:a[u]){
    if(u==p) U[e][0]=D[e][0]=e;
    else{
      U[e][0]=p2[a[::p[A[p2[e][19]]][0]][0]][19];
      D[e][0]=p3[a[::p[A[p3[e][19]]][0]].back()][19];
    }
  }
  for(int i=1;i<20;++i){
    for(auto &e:a[u]){
      U[e][i]=U[U[e][i-1]][i-1];
      D[e][i]=D[D[e][i-1]][i-1];
    }
  }
  for(auto &v:adj[u]){
    if(v==p) continue;
    dfs(v,u);
  }
}
int LCA(int u,int v){
  if(lv[u]>lv[v]) swap(u,v);
  for(int i=18;i>=0;--i) if(lv[p[v][i]]>=lv[u]) v=p[v][i];
  if(u==v) return u;
  for(int i=18;i>=0;--i) if(p[u][i]!=p[v][i]) u=p[u][i], v=p[v][i];
  return p[u][0];
}
ll calc(int lca,int iu,int iv){
  ll ret=0;
  for(int i=19;i>=0;--i){
    if(lv[A[U[iu][i]]]>lv[lca]) iu=U[iu][i], ret+=1<<i;
    if(lv[A[D[iv][i]]]>lv[lca]) iv=D[iv][i], ret+=1<<i;
  }
  if(p[A[p2[iu][19]]][0]!=A[p2[iu][19]]&&lv[A[a[p[A[p2[iu][19]]][0]][0]]]>=lv[lca]) iu=a[p[A[p2[iu][19]]][0]][0], ++ret;
  if(p[A[p3[iv][19]]][0]!=A[p3[iv][19]]&&lv[A[a[p[A[p3[iv][19]]][0]].back()]]>=lv[lca]) iv=a[p[A[p3[iv][19]]][0]].back(), ++ret;
  for(int i=19;i>=0;--i){
    if(lv[A[p2[iu][i]]]>=lv[lca]) iu=p2[iu][i];
    if(lv[A[p3[iv][i]]]>=lv[lca]) iv=p3[iv][i];
  }
  if(iv<iu) ++ret;
  return ret;
}
pair<ll,int> play(int iu,int v){
  int lca=LCA(A[iu],v);
  ll mn=calc(lca,iu,a[v].back());
  int l=0,r=a[v].size()-1;
  while(l<r){
    int mid=l+r>>1;
    if(calc(lca,iu,a[v][mid])==mn) r=mid;
    else l=mid+1;
  }
  return {mn, a[v][l]};
}

long long min_risk(int N, int M, int L, std::vector<int> U, std::vector<int> V,
                   std::vector<int> A, std::vector<int> S) {
  ::A=A;
  for(int i=0;i<M;++i){
    a[A[i]].eb(i);
  }
  for(int i=0;i<M;++i){
    lm[i]=a[A[i]][0];
    rm[i]=a[A[i]].back();
  }
  for(int i=0;i<N-1;++i) adj[U[i]].eb(V[i]), adj[V[i]].eb(U[i]);
  dfs(0,0);
  int cur=0;
  ll ans=0,tmp=0;
  for(int i=0;i<L;++i){
    tie(tmp,cur)=play(cur,S[i]);
    ans+=tmp;
  }
  return ans;
}
