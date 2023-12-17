#include<bits/stdc++.h>
using namespace std;

int n, x, ans = 0, a[200005], f[2][200005];

int solve(){
    cin >> n >> x;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		f[0][i] = f[1][i] = INT_MAX;
	}
	f[0][0] = f[1][0] = INT_MIN;
	for (int i = 2; i <= n; i++) {
		int k = lower_bound(f[0] + 1, f[0] + n + 1, a[i - 1] - x) - f[0];
		f[0][k] = a[i - 1] - x;
		f[1][k] = min(f[1][k], f[0][k]);
		ans = max(ans, k);
		k = lower_bound(f[1] + 1, f[1] + n + 1, a[i]) - f[1];
		f[1][k] = a[i];
		ans = max(ans, k);
	}
	cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q(1);
    cin>>Q;
    while(Q--) solve();

    return 0;
}
