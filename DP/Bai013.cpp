/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n;
	cin >> n;
	vector<ll>a(n + 1);
	ll s = 0;
	for (ll i = 1; i <= n; i++)
	{
		cin >> a[i];
		s += a[i];
	}
	vector<vector<ll>>d(n + 1, vector<ll>(n + 1, 0));
	for (ll i = 1; i <= n; i++)
		d[i][i] = a[i];
	for (ll i = n; i >= 1; i--)
		for (ll j = 1; j <= n; j++)
		{
			if (i + 1 <= j)
				d[i][j] = a[i] - d[i + 1][j];
			if (i <= j - 1)
				d[i][j] = max(d[i][j], a[j] - d[i][j - 1]);
		}
	cout << (d[1][n] + s) / 2;
	return 0;
}
