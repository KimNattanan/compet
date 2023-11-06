#include<stdio.h>

void main(){

    int X,Y,Z; scanf("%d %d %d",&X,&Y,&Z);
    int d0,d1,d2,d3; scanf("%d %d %d %d",&d0,&d1,&d2,&d3);
    int x=(d0-d1+X)/2;
    int y=(d0-d2+Y)/2;
    int z=(d0-d3+Z)/2;
    int N; scanf("%d",&N);
    int i,t0=1000000000;
    for(i=0;i<N;++i){
        int vx,vy,vz; scanf("%d %d %d",&vx,&vy,&vz);
        int t1=(1.0*x/vx + 1.0*y/vy + 1.0*z/vz)*2;
        if(t1<t0) t0=t1;
    }
    printf("%d %d %d\n%d",x,y,z,t0);

}
