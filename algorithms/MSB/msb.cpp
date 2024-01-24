#include<bits/stdc++.h>
using namespace std;

int log2(int x){
    return 31-__builtin_clz(x);
}
int msb(int x){
    return 1<<31-__builtin_clz(x);
}
