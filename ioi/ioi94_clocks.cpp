#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back

array<int,9> A[9]={
{1,1,0,1,0,0,0,0,0},
{1,1,1,0,1,0,0,0,0},
{0,1,1,0,0,1,0,0,0},
{1,0,0,1,1,0,1,0,0},
{1,0,1,0,1,0,1,0,1},
{0,0,1,0,1,1,0,0,1},
{0,0,0,1,0,0,1,1,0},
{0,0,0,0,1,0,1,1,1},
{0,0,0,0,0,1,0,1,1}
};
int B[9];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    for(int i=0;i<9;++i){
        cin>>B[i];
        B[i]=(4-B[i])%4;
    }

    for(int j=0;j<9;++j){
        for(int i=j;i<9;++i){
            if(A[i][j]&1){
                swap(A[i],A[j]);
                swap(B[i],B[j]);
                break;
            }
        }
        B[j]=(B[j]*A[j][j])%4;
        for(int k=8;k>=j;--k) A[j][k]=(A[j][k]*A[j][j])%4;
        for(int i=0;i<9;++i){
            if(!A[i][j]||i==j) continue;
            int c=4-A[i][j];
            B[i]=(B[i]+c*B[j])%4;
            for(int k=j;k<9;++k) A[i][k]=(A[i][k]+c*A[j][k])%4; 
        }
    }

    for(int i=0;i<9;++i){
        while(B[i]--) cout<<i+1<<" ";
    }

    return 0;
}
