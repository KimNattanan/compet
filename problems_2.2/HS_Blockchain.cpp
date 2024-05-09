/*
	HS_Blockchain
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll md=1e8+7;

bool adj[4][4][4];
ll f[65][4][4],tmp[4],tmp2[4][4],tmp3[4][4];

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	for(int i=0;i<4;++i) for(int j=0;j<4;++j) for(int k=0;k<4;++k) cin>>adj[i][j][k];
	for(int i=0;i<4;++i){
        f[0][i][i]=1;
        for(int j=0;j<4;++j){
            for(int k=0;k<4;++k) tmp[k]=f[0][i][k];
            for(int k=0;k<4;++k) for(int l=0;l<4;++l) f[0][i][l]=(f[0][i][l]+tmp[k]*adj[j][k][l])%md;
        }
	}
	for(int z=1;z<65;++z){
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
    		    for(int k=0;k<4;++k){
					f[z][i][j]=(f[z][i][j]+f[z-1][i][k]*f[z-1][k][j])%md;
				}
			}
		}
    }

	int Q; cin>>Q;
	while(Q--){
		ll x; cin>>x;
		ll t=x/4;
        for(int i=0;i<4;++i) for(int j=0;j<4;++j) tmp2[i][j]=(i==j);
		for(ll i=0,msk=1 ;i<63; ++i,msk<<=1){
			if(t&msk){
                for(int j=0;j<4;++j) for(int k=0;k<4;++k) tmp3[j][k]=0;
                for(int j=0;j<4;++j){
                    for(int k=0;k<4;++k){
                        for(int l=0;l<4;++l){
                            tmp3[j][k]=(tmp3[j][k]+tmp2[j][l]*f[i][l][k])%md;
                        }
                    }
                }
                for(int j=0;j<4;++j) for(int k=0;k<4;++k) tmp2[j][k]=tmp3[j][k];
            }
		}
		for(int i=0;i<x%4;++i){
            for(int j=0;j<4;++j) tmp[j]=tmp2[0][j];
            for(int j=0;j<4;++j) for(int k=0;k<4;++k) tmp2[0][k]=(tmp2[0][k]+tmp[j]*adj[i][j][k])%md;
        }
        for(int i=0;i<4;++i) cout<<tmp2[0][i]<<" \n"[i==3];
	}

	return 0;
}
