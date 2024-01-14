#include<bits/stdc++.h>
using namespace std;
using ll=long long;

template<class T>
struct Matrix{
    int n,m;
    vector<vector<T>> a;
    Matrix(const int &n,const int &m):n(n),m(m),a(n,vector<T>(m)){}
    Matrix& operator+=(const Matrix &r){
        for(int i=0;i<n;++i) for(int j=0;j<m;++j) a[i][j]+=r.a[i][j];
        return *this;
    }
    friend Matrix operator+(const Matrix &l,const Matrix &r){return Matrix(l)+=r;}
    friend istream& operator>>(istream &is,Matrix &x){
        for(auto &i:x.a) for(auto &j:i) is>>j;
        return is;
    }
    friend ostream& operator<<(ostream &os,const Matrix &x){
        for(auto &i:x.a){
            for(auto &j:i) os<<j<<" ";
            os<<'\n';
        }
        return os;
    }
};

int main(){
    ios::sync_with_stdio(false);cin.tie(0);

    int n,m; cin>>n>>m;
    Matrix<ll> m1(n,m),m2(n,m);
    cin>>m1>>m2;
    cout<<(m1+m2);

    return 0;
}
