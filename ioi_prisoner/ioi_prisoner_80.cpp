#include "insects.h"
#include<bits/stdc++.h>

using namespace std;

#define in move_inside
#define press press_button
#define out move_outside

set<int> mp,mp2,mp3;
int n,p;
vector<int> idx;

bool check(int k1){
    stack<int> st;
    for(auto &i:idx){
        if(mp.size()==p*k1) break;
        if(mp.count(i)) continue;
        if(mp3.count(i)) continue;
        in(i);
        if(press()>k1) out(i);
        else mp.insert(i),st.push(i);
    }
    if(mp.size()==p*k1){
        for(auto &e:mp) if(mp2.count(e)) mp2.erase(e);
        return 1;
    }
    stack<int> st2;
    for(auto &e:mp2){
        if(!mp.count(e)) st2.push(e);
    }
    while(!st2.empty()){
        mp2.erase(st2.top());
        mp3.insert(st2.top());
        st2.pop();
    }
    while(st.size()){
        mp.erase(st.top());
        out(st.top());
        st.pop();
    }
    return 0;
}

int min_cardinality(int N){
    n=N;
    for(int i=0;i<n;++i){
        idx.push_back(i);
        in(i);
        if(press()>1) out(i),mp2.insert(i);
        else mp.insert(i);
    }
    p=mp.size();

    int l=1,r=(n)/p;
    while(l<r){
        int mid=l+(r-l+1>>1);
        random_shuffle(idx.begin(),idx.end());
        if(check(mid)) l=mid;
        else r=mid-1;
    }
    return l;
}
