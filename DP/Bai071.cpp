/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n;
	cin >> n;
	vector<vector<ll>>c(n + 1, vector<ll>(n + 1));
	for (ll i = 1; i <= n; i++)
		for (ll j = 1; j <= n; j++)
			cin >> c[i][j];
	vector<vector<ll>>d(1LL << n, vector<ll>(n + 1, LLONG_MAX));
	// d[state][j]: min cost from state to city j <state!=j> (di qua mot lan)
	ll state = (1LL << n) - 1;
	for (ll i = 1; i <= n; i++)
	{
		d[0][i] = 0;
		d[1LL << (i - 1)][i] = 0;
	}
	for (ll s = 1; s <= state; s++)
		for (ll i = 1; i <= n; i++)
			if (((1LL << (i - 1)) & (s)) == (1LL << (i - 1))) // ton tai i trong state
				for (ll j = 1; j <= n; j++)
					if ((i != j) && ((1LL << (j - 1)) & (s)) != (1LL << (j - 1))) // khong ton tai j trong state
					{
						ll ss = s | (1LL << (j - 1));
						d[ss][j] = min(d[ss][j],d[s][i] + c[i][j]);
					}
			
	ll ans=LLONG_MAX;
	for (ll i = 1; i <= n; i++)
		ans = min(ans, d[state][i]);
	cout << ans;
	return 0;
}
