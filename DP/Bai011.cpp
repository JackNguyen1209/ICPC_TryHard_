/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

vector<vector<ll>>d;
ll sol(ll a, ll b)
{
	if (d[a][b] != -1)return d[a][b];
	ll cost = LLONG_MAX;

	for (ll i = 1; i <= a - 1; i++)
		cost = min(cost,1 + sol(a - i, b) + sol(i, b));
	for (ll j = 1; j <= b - 1; j++)
		cost = min(cost,1 + sol(a, b - j) + sol(a, j));

	return d[a][b] = cost;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll a, b;
	cin >> a >> b;
	d.resize(a + 1, vector<ll>(b + 1, -1));
	for (ll i = 0; i <= min(a, b); i++)
		d[i][i] = 0;
	sol(a, b);
	cout << d[a][b];
	return 0;
}
