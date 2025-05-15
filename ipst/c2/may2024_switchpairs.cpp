#include "switchpairs.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define sz(x) (int)x.size()

vector<int> v0,v;
int M;
int ask(vector<int> v){
  for(int i=0;i<sz(v);++i) if(v0[i]!=-1) v[i]=v0[i];
  return control_switches(v);
}

void solve(int N){
  M=N<<1;
  int K=31-__builtin_clz(M-1);
  v0.assign(M,-1);
  v.resize(M);
  for(int i=0;i<N;++i){
    int y=-1,x0,x1;
    fill(v.begin(),v.end(),0);
    if(ask(v)>i) y=0;
    else{
      fill(v.begin(),v.end(),1);
      if(ask(v)>i) y=1;
    }
    if(y==-1){
      vector<int> y0,y1;
      for(int j=0;j<=K;++j){
        for(int k=0;k<M;++k) v[k]=bool(k&1<<j);
        if(ask(v)>i){ // 1:j 0:no-j
          for(int k=0;k<M;++k){
            if(v[k]) y1.eb(k);
            else y0.eb(k);
          }
          break;
        }
        for(auto &e:v) e=!e;
        if(ask(v)>i){ // 1:no-j 0:j
          for(int k=0;k<M;++k){
            if(v[k]) y1.eb(k);
            else y0.eb(k);
          }
          break;
        }
      }
      int l=0,r=sz(y0)-1;
      while(l<r){
        int mid=l+r>>1;
        fill(v.begin(),v.end(),1);
        for(int j=0;j<sz(y0);++j) v[y0[j]]=(j<=mid ? 0 : 1);
        if(ask(v)>i) r=mid;
        else l=mid+1;
      }
      x0=y0[l];
      l=0,r=sz(y1)-1;
      while(l<r){
        int mid=l+r>>1;
        fill(v.begin(),v.end(),0);
        for(int j=0;j<sz(y1);++j) v[y1[j]]=(j<=mid ? 1 : 0);
        if(ask(v)>i) r=mid;
        else l=mid+1;
      }
      x1=y1[l];
    }else{
      int l=0,r=M-1;
      while(l<r){
        int mid=l+r>>1;
        for(int j=0;j<M;++j) v[j]=(j<=mid ? y : !y);
        if(ask(v)>i) r=mid;
        else l=mid+1;
      }
      x0=l;
      l=0,r=M-1;
      while(l<r){
        int mid=l+r+1>>1;
        for(int j=0;j<M;++j) v[j]=(j>=mid ? y : !y);
        if(ask(v)>i) l=mid;
        else r=mid-1;
      }
      x1=l;
    }
    if(y==-1) v0[x0]=0, v0[x1]=1;
    else v0[x0]=v0[x1]=y;
  }
  ask(v0);
}
