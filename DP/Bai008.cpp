/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;
const ll mo = 1e9 + 7;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> n >> m;
	vector<ll>a(n + 1);
	for (ll i = 1; i <= n; i++)
		cin >> a[i];
	vector<vector<ll>>d(n + 1, vector<ll>(m + 1, 0));
	//d[1]
	if (a[1] == 0)
	{
		for (ll i = 1; i <= m; i++)
			d[1][i] = 1;
	}
	else
		d[1][a[1]] = 1;
	for (ll i = 2; i <= n; i++)
	{
		for (ll j = -1; j <= 1; j++)
		{
			if (a[i] == 0)
			{
				for (ll z = 1; z <= m; z++)
					for (ll k = -1; k <= 1; k++)
					{
						if (k + z >= 1 && k + z <= m)
							d[i][z] += d[i - 1][k + z];
						d[i][z] %= mo;
					}
				break;
			}
			else
			{
				if (j + a[i] >= 1 && j + a[i] <= m)
					d[i][a[i]] += d[i - 1][j + a[i]];
				d[i][a[i]] %= mo;
			}
		}
	}
	ll s = 0;
	for (ll i = 1; i <= m; i++)
	{
		s += d[n][i];
		s %= mo;
	}
	cout << s;
	return 0;
}
