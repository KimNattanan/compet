#include<bits/stdc++.h>
#include "card.h"
using namespace std;

namespace SHIN{
    int variable_example = 0;
}

namespace LENA{
    int variable_example = 0;
}

int f[]={1,1,2,6,24,120},comp[250];
bitset<250> used;
bitset<5> used2;

vector<int> play(int N,int x){
    used[x]=0;
    used2.reset();
    vector<int> A,B(5);
    int num=x;
    for(int i=0;i<N;++i){
        if(!used[i]) continue;
        A.emplace_back(i);
        if(i<x) --num; 
    }
    num>>=1;
    int cur=0;
    for(int i=0;i<5;++i){
        for(B[i]=0;;++B[i]){
            if(used2[B[i]]) continue;
            if(cur+f[4-i]>num) break;
            cur+=f[4-i];
        }
        used2[B[i]]=1;
    }
    for(int i=0;i<5;++i) B[i]=A[B[i]];
    return B;
}
int play2(int N,vector<int> B,bool p){
    for(int i=0,j=0;i<N;++i) if(used[i]) comp[i]=j++;
    for(int i=0;i<5;++i) B[i]=comp[B[i]];
    int num=0,num2=p;
    used2.reset();
    for(int i=0;i<5;++i){
        for(int j=0;j<B[i];++j){
            if(used2[j]) continue;
            num+=f[4-i];
        }
        used2[B[i]]=1;
    }
    while(num--) num2+=2;
    for(int i=0;i<=num2;++i){
        if(used[i]) ++num2;
    }
    return num2;
}

std::vector<int> Shin(int N, std::vector<int> A) {
    SHIN::variable_example++;
    sort(A.begin(),A.end());
    int cnt=0;
    used.reset();
    for(auto &e:A) cnt+=e&1, used[e]=1;
    vector<int> res;
    if(cnt==0||cnt==6) res=play(N,A[0]);
    else if(cnt==1||cnt==5){
        if((A[0]&1) != (A[1]&1)) res=play(N,A[2]);
        else res=play(N,A[0]);
    }
    else if(cnt==2){
        if(~A[0]&1) res=play(N,A[0]);
        else if(A[1]&1) res=play(N,A[2]);
        else if(~A[2]&1) res=play(N,A[2]);
        else res=play(N,A[4]);
    }
    else if(cnt==4){
        if(A[0]&1) res=play(N,A[0]);
        else if(~A[1]&1) res=play(N,A[2]);
        else if(A[2]&1) res=play(N,A[2]);
        else res=play(N,A[4]);
    }
    else res=play(N,A[1]);
    return res;
}

int Lena(int N, std::vector<int> B) {
    LENA::variable_example++;
    int cnt=0;
    used.reset();
    for(auto &e:B) cnt+=e&1, used[e]=1;
    return play2(N,B,cnt>=3);
}
