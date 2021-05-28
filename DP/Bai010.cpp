/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	string s, t;
	cin >> s >> t;
	ll n = (ll)s.size();
	ll m = (ll)t.size();
	vector<vector<ll>>d(n + 1, vector<ll>(m + 1, 0));

	for (ll i = 0; i <= n; i++)
	{
		for (ll j = 0; j<=m; j++)
		{
			if (i == 0 || j == 0)
			{
				d[i][j] = i + j;
				continue;
			}
			if (s[i-1] == t[j-1])
			{
				d[i][j] = d[i - 1][j - 1];
			}
			else
			{
				d[i][j] = min(d[i - 1][j - 1], min(d[i - 1][j], d[i][j - 1])) + 1;
			}
		}
	}
	cout << d[n][m];
	
	return 0;
}