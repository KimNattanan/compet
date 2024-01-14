#include<bits/stdc++.h>
using namespace std;

struct _iostream{
    template<class T> friend _iostream& operator>>(_iostream &is,T &x){cin>>x; return is;}
    template<class T> friend _iostream& operator<<(_iostream &os,const T &x){cout<<x; return os;}
    friend _iostream& operator<<(_iostream &os,ostream&(x)(ostream&)){cout<<x; return os;}
}io;

int main(){
    ios::sync_with_stdio(false);cin.tie(0);

    int a,b;
    io>>a>>b<<a+b;

    return 0;
}
