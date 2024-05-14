#include<bits/stdc++.h>
using namespace std;
using A=unsigned long long;

// you may define some global variables, but it does not work if you try to transfer any information from function Alice to function Bob through these variables.
// you had better not use the same global variables in function Alice and in function Bob.

/*
p:              The original permutation owned by Alice. You can get its length by p.size(). 
				It is guaranteed that p.size()<=20 and each integers in [0, p.size()) appears exactly once in p.
return value:   The integer passed from Alice to Bob (64-bit unsigned).
*/

bitset<25> used;
A f[25];

unsigned long long Alice(const std::vector<int> p){
	// add your code here
	used.reset();
	f[0]=1;
	for(int i=1;i<=20;++i) f[i]=f[i-1]*i;
	
	int n=p.size();
	A ret=0;
	for(int i=1;i<n;++i) ret+=f[i];
	for(int i=0;i<n;++i){
		int cnt=0;
		for(int j=0;j<p[i];++j) if(!used[j]) ++cnt;
		ret+=cnt*f[n-i-1];
		used[p[i]]=1;
	}
	return ret; // change this into your code
}

/*
x:         		The integer that Bob received from Alice.
return value:	The permutation that Bob restored based on the received information.
*/
std::vector<int> Bob(const unsigned long long x_){
	A x=x_;
	// add your code here
	used.set();
	f[0]=1;
	for(int i=1;i<=20;++i) f[i]=f[i-1]*i;
	
	int n=1;
	while(x>=f[n]) x-=f[n++];
	vector<int> ret(n);
	for(int i=0;i<n;++i){
		ret[i]=used._Find_first();
		while(x>=f[n-i-1]) x-=f[n-i-1], ret[i]=used._Find_next(ret[i]);
		used[ret[i]]=0;
	}
	return ret; // change this into your code
}

