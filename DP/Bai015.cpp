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

	ll n;
	cin >> n;
	vector<ll>a(n + 1);
	for (ll i = 1; i <= n; i++)
		cin >> a[i];
	vector <ll>d(n + 1, 1);
	vector<ll>len(n + 1, LLONG_MAX);
	len[1] = a[1];
	for (ll i = 2; i <= n; i++)
	{
		ll l = 1;
		ll r = n;
		ll res = -1;
		while (l <= r)
		{
			ll m = (l + r) >> 1;
			if (len[m] < a[i])
			{
				l = m + 1;
				res = m;
			}
			else
				r = m - 1;
		}
		if (res == -1)
		{
			d[i] = 1;
			len[d[i]] = min(len[d[i]], a[i]);
		}
		else
		{
			d[i] = res + 1;
			len[d[i]] = min(len[d[i]], a[i]);
		}
	}
	cout << *max_element(d.begin(), d.end());
	return 0;
}