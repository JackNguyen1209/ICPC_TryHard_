/*
Nguyen Duc Anh Phuc_Jacke
*/

#include <limits.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
#include <fstream>
#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

class segtree
{
private:
	vector<ll> st;
	ll n;
public:
	void merge(ll i)
	{
		st[i] = min(st[2 * i], st[2 * i + 1]);
	}
	void build(vector<ll>& a, ll l, ll r, ll si)
	{
		if (l == r)
			st[si] = a[l];
		else
		{
			ll m = (l + r) / 2;
			build(a, l, m, si * 2);
			build(a, m + 1, r, si * 2 + 1);
			merge(si);
		}
	}
	ll query(ll l, ll r, ll ql, ll qr, ll si)
	{
		if (r<ql || l>qr || l > r)
			return LLONG_MAX;
		if (ql <= l && r <= qr)
			return st[si];
		ll m = (l + r) / 2;
		ll le = query(l, m, ql, qr, si * 2);
		ll ri = query(m + 1, r, ql, qr, si * 2 + 1);
		return min(le, ri);
	}
	ll query(ll ql, ll qr)
	{
		return query(1, n, ql, qr, 1);
	}
	void set(ll l, ll r, ll i, ll x, ll si)
	{
		if (l == i && r == i)
		{
			st[si] = x;
			return;
		}
		ll m = (l + r) / 2;
		if (i <= m)
			set(l, m, i, x, si * 2);
		else
			set(m + 1, r, i, x, si * 2 + 1);
		merge(si);
	}
	void set(ll i, ll x)
	{
		set(1, n, i, x, 1);
	}
	segtree(vector<ll>& a, ll si)
	{
		n = si;
		st.resize(4 * n, 0);
		build(a, 1, n, 1);
	}
};


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	ll n, m;
	cin >> n >> m;
	vector<ll> a; a.resize(n + 1);
	for (ll i = 1; i <= n; i++)
		cin >> a[i];
	segtree t(a, n);

	for (ll i = 1; i <= m; i++)
	{
		ll x, y, z;
		cin >> x >> y >> z;
		if (x == 1)
			t.set(y + 1, z);
		else
			cout << t.query(y + 1, z) << "\n";
	}

	return 0;
}