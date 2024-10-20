struct rmq{
    vector<vector<int>> a;
    void init(vector<int> &vec){
        int n=vec.size();
        int m=31-__builtin_clz(n);
        a.resize(n,vector<int>(m+1));
        for(int i=0;i<n;++i){
            a[i][0]=vec[i];
            for(int j=0;j<=m;++j) a[i][j+1]=max(a[i][j],a[max(0,i-(1<<j))][j]);
        }
    }
    int qr(int l,int r){
        int i=31-__builtin_clz(r-l+1);
        return max(a[r][i],a[l+(1<<i)-1][i]);
    }
}
