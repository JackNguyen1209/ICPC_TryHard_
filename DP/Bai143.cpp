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
	vector<vector<ll>>d(n + 1, vector<ll>(n + 1, LLONG_MAX));
	vector<vector<ll>>pos(n + 1, vector<ll>(n + 1));
	vector<ll>a(n + 1);
	vector<ll>pr(n + 1, 0);
	for (ll i = 1; i <= n; i++)
		cin >> a[i], pr[i] = pr[i - 1] + a[i];

	//d[i][j]: cost to separate i,j
	//d[i][j]=min(d[i][k]+d[k+1][j]) i<=k<=j-1
	//pos[i][j]: position optimize dp
	for (ll i = 1; i <= n; i++)
		d[i][i] = 0, pos[i][i] = i;
	for (ll l = 2; l <= n; l++)
		for (ll i = 1; i <= n - l + 1; i++)
		{
			ll j = i + l - 1;
			for (ll k = max(min(pos[i][j - 1], pos[i + 1][j]) - 1, i); k <= min(max(pos[i][j - 1], pos[i + 1][j]) + 1, j - 1); k++)
				if (d[i][k] + d[k + 1][j] + pr[j] - pr[i - 1] < d[i][j])
				{
					d[i][j] = d[i][k] + d[k + 1][j] + pr[j] - pr[i - 1];
					pos[i][j] = k;
				}
		}
	cout << d[1][n];
	return 0;
}
