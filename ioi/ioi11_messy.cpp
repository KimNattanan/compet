#include "messy.h"
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

string s;
vector<int> ans;

void addElement(int l,int r){
  if(l==r) return;
  int mid=l+r>>1;
  for(auto &e:s) e='1';
  for(int i=l;i<=r;++i) s[i]='0';
  for(int i=l;i<=mid;++i){
    s[i]='1';
    add_element(s);
    s[i]='0';
  }
  addElement(l,mid), addElement(mid+1,r);
}
void checkElement(int l,int r,vector<int> v){
  if(l==r) return void(ans[v[0]]=l);
  int mid=l+r>>1;
  vector<int> vl,vr;
  for(auto &e:s) e='1';
  for(auto &e:v) s[e]='0';
  for(auto &e:v){
    s[e]='1';
    if(check_element(s)) vl.eb(e);
    else vr.eb(e);
    s[e]='0';
  }
  checkElement(l,mid,vl), checkElement(mid+1,r,vr);
}

vector<int> restore_permutation(int n, int w, int r) {
  s.resize(n);
  addElement(0,n-1);
  compile_set();
  vector<int> v(n);
  iota(v.begin(),v.end(),0);
  ans.resize(n);
  checkElement(0,n-1,v);
  return ans;
}
