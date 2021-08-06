/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

bool ok(ll num1, ll num2)
{
	return ((num1 & num2) == 0);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll msk = (1LL << 8) - 1;
	vector<ll>s(1LL << 8, 0);
	while (msk--)
	{
		ll t = msk;
		vector<ll>a;
		for (ll i = 0; i <= 7; i++)
		{
			if (t & 1) a.push_back(1);
			else a.push_back(0);
			t >>= 1LL;
		}
		bool f = 1;
		for (ll i = 1; i <= 7; i++)
			if (a[i] == 1 && a[i] == a[i - 1])
			{
				f = 0;
				break;
			}
		if (f)
			s[msk] = 1;
	}

	ll n;
	cin >> n;
	ll ma = -LLONG_MAX;
	vector<vector<ll>>a(8, vector<ll>(n));
	for (ll i = 0; i <= 7; i++)
		for (ll j = 0; j <= n - 1; j++)
		{
			cin >> a[i][j];
			ma = max(ma, a[i][j]);
		}
	vector <vector<ll>>d(n, vector<ll>(1LL << 8, -LLONG_MAX));
	//d[i][k]: maximum value at state k
	// d[i][k]=max(d[i-1][all possible state before k])
	for (ll msk = 0; msk < (1LL << 8); msk++)
		if (s[msk])
		{
			ll t = msk;
			ll ans = 0;
			for (ll i = 0; i <= 7; i++)
			{
				if (t & 1)
					ans += a[i][0];
				t >>= 1LL;
			}
			d[0][msk] = ans;
		}

	for (ll i = 1; i <= n - 1; i++)
		for (ll msk1 = 0; msk1 < (1LL << 8); msk1++)
			if (s[msk1])
			{
				ll ans = -LLONG_MAX;
				for (ll msk2 = 0; msk2 < (1LL << 8); msk2++)
					if (s[msk2] && ok(msk1, msk2))
						ans = max(ans,d[i - 1][msk2]);
				ll t = msk1;
				ll s = 0;
				for (ll j = 0; j <= 7; j++)
				{
					if (t & 1)
						s += a[j][i];
					t >>= 1LL;
				}
				ans += s;
				d[i][msk1] = ans;
			}
	ll ans = -LLONG_MAX;
	for (ll msk = 0; msk < (1LL << 8); msk++)
		if (s[msk])
			ans = max(ans, d[n - 1][msk]);

	if (ans == 0)
		cout << ma;
	else
		cout << ans;
	return 0;
}
