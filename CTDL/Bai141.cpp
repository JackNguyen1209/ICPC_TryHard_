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

struct node
{
	ll s;
};

class segtree
{
private:
	vector<node>st;
	ll n;
public:
	void merge(ll si)
	{
		st[si].s = st[si * 2].s + st[si * 2 + 1].s;
	}
	void build(vector<ll>& a, ll l, ll r, ll si)
	{
		if (l > r)return;
		if (l == r)
		{
			st[si].s = a[l];
			return;
		}
		ll m = (l + r) >> 1;
		build(a, l, m, si * 2);
		build(a, m + 1, r, si * 2 + 1);
		merge(si);

	}
	void modifyhelp(ll l, ll r, ll k, ll x, ll si)
	{
		if (l > r)
			return;
		if (l == r)
		{
			st[si].s = x;
			return;
		}
		ll m = (l + r) >> 1;
		if (k <= m)
			modifyhelp(l, m, k, x, si * 2);
		else
			modifyhelp(m + 1, r, k, x, si * 2 + 1);
		merge(si);
	}
	void modify(ll k, ll x)
	{
		modifyhelp(1, n, k, x, 1);
	}
	ll queryhelp(ll l, ll r, ll ql, ll qr, ll si)
	{
		if (l > r || qr<l || ql>r)
			return 0;
		if (ql <= l && r <= qr)
			return st[si].s;
		ll m = (l + r) >> 1;
		ll le = queryhelp(l, m, ql, qr, si * 2);
		ll ri = queryhelp(m + 1, r, ql, qr, si * 2 + 1);
		return le + ri;
	}
	ll query(ll ql, ll qr)
	{
		return queryhelp(1, n, ql, qr, 1);
	}
	segtree(vector<ll>& a, ll nn)
	{
		n = nn;
		st.resize(4 * n);
		build(a, 1, n, 1);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, q;
	cin >> n >> q;
	vector<ll>a(n + 1);
	for (ll i = 1; i <= n; i++)
		cin >> a[i];
	segtree t(a, n);
	for (ll i = 0; i <= q - 1; i++)
	{
		ll x;
		cin >> x;
		if (x == 1)
		{
			ll u, v;
			cin >> u >> v;
			u++;
			t.modify(u, v);
		}
		else
		{
			ll l; ll r;
			cin >> l >> r;
			l++;
			cout << t.query(l, r) << "\n";
		}
	}
	return 0;
}