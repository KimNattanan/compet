#include<bits/stdc++.h>
using namespace std;

int z[2000005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    string s,p; cin>>s>>p;
    string s2=p+s;
    z[0]=s2.size();
    for(int i=1,l=0,r=0;i<s2.size();++i){
        if(i<r) z[i]=min(z[i-l],r-i);
        while(i+z[i]<s2.size() && s2[z[i]]==s2[i+z[i]]) ++z[i];
        if(i+z[i]>r) l=i,r=i+z[i];
    }
    for(int i=0;i<s.size();++i){
        if(z[i+p.size()]>=p.size()) cout<<i<<"-"<<i+(int)p.size()-1<<'\n';
    }
}
