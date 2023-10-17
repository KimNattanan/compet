#include<bits/stdc++.h>
using namespace std;

int X,Y,Z,d0,d1,d2,d3,xy,xz,yz,x,y,z;
int n,vx,vy,vz,t,ans;
int i;

int main(){
    scanf("%d %d %d",&X,&Y,&Z);
    scanf("%d %d %d %d",&d0,&d1,&d2,&d3);
    yz=(d0+d1-X)/2;
    xz=(d0+d2-Y)/2;
    xy=(d0+d3-Z)/2;
    x=(xy+xz-yz)/2;
    y=(xy+yz-xz)/2;
    z=(xz+yz-xy)/2;
    scanf("%d",&n);
    ans=INT_MAX;
    for(i=1;i<=n;++i){
        scanf("%d %d %d",&vx,&vy,&vz);
        t=(1.0*x/vx)+(1.0*y/vy)+(1.0*z/vz);
        if(t<ans) ans=t;
    }
    printf("%d %d %d\n%d",x,y,z,2*ans);

    return 0;
}
/**

4 4 4
6 6 6 6
1
1 1 1


*/
