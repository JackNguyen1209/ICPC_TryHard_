/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;

const ll mxn = 100 + 1;
const ll mxm = 1e4 + 1;

ll n, m;
ll a[mxm];
ll d[mxn][mxn];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (ll i = 1; i <= m; i++)cin >> a[i];

	for (ll i = 1; i <= n; i++)
		for (ll j = 1; j <= n; j++)
			cin >> d[i][j];

	for (ll k = 1; k <= n; k++)
		for (ll i = 1; i <= n; i++)
			for (ll j = 1; j <= n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	ll c = 0;
	for (ll i = 2; i <= m; i++)
		c += d[a[i - 1]][a[i]];
	cout << c;
	return 0;
}