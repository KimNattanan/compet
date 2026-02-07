const short MN = -9999;

short dp[51][51][51];

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        short n=(short)grid.size();
        for(short i=0;i<=n;++i) for(short j=0;j<=n;++j) for(short k=0;k<=n;++k) dp[i][j][k] = MN;
        dp[1][1][1] = (grid[0][0]==-1 ? MN : grid[0][0]);
        for(short i=1;i<=n;++i) for(short j=1;j<=n;++j) if(grid[i-1][j-1]!=-1) for(short k=max(1,i+j-n),l=i+j-k;k<=n && l>0;++k,--l) if(grid[k-1][l-1]!=-1 && (i!=1 || j!=1)) dp[i][j][k] = max({dp[i-1][j][k-1], dp[i-1][j][k], dp[i][j-1][k-1], dp[i][j-1][k]}) + grid[i-1][j-1] + (i==k && j==l ? 0 : grid[k-1][l-1]);
        return max(0,(int)dp[n][n][n]);
    }
};