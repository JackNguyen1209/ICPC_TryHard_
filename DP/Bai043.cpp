/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

struct node
{
	ll s;
};

const ll md = 1e9;

class segtree
{
private:
	vector<node>st;
	ll n;
public:
	void merge(ll si)
	{
		st[si].s = st[si * 2].s + st[si * 2 + 1].s;
		st[si].s %= md;
	}
	void build(ll l, ll r, ll si)
	{
		if (l > r)return;
		if (l == r)
		{
			st[si].s = 0;
			return;
		}
		ll m = (l + r) >> 1;
		build(l, m, si * 2);
		build(m + 1, r, si * 2 + 1);
		merge(si);
	}
	void add(ll l, ll r, ll pos, ll x, ll si)
	{
		if (l == r)
		{
			st[si].s += x;
			st[si].s %= md;
			return;
		}
		ll m = (l + r) >> 1;
		if (pos <= m)add(l, m, pos, x, si * 2);
		else add(m + 1, r, pos, x, si * 2 + 1);
		merge(si);
	}
	void add(ll pos, ll x)
	{
		add(1, n, pos, x, 1);
	}
	ll query(ll l, ll r, ll ql, ll qr, ll si)
	{
		if (l > r || r<ql || l>qr)return 0;
		if (ql <= l && r <= qr)return st[si].s;
		ll m = (l + r) >> 1;
		return query(l, m, ql, qr, si * 2)%md + query(m + 1, r, ql, qr, si * 2 + 1)%md;
	}
	ll query(ll l, ll r)
	{
		return query(1, n, l, r, 1);
	}
	segtree(ll nn)
	{
		n = nn;
		st.resize(4 * n);
	}
};



int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, k;
	cin >> n >> k;
	vector <ll>a(n + 1);
	for (ll i = 1; i <= n; i++)cin >> a[i];
	vector<vector<ll>>d(n + 1, vector<ll>(12));
	for (ll i = 1; i <= n; i++)
		d[i][1] = 1;
	for (ll j = 2; j <= k; j++)
	{
		segtree t(n);
		for (ll i = 1; i <= n; i++)
		{
			if (a[i] != n)
				d[i][j] = t.query(a[i] + 1, n);
			t.add(a[i], d[i][j - 1]);
			d[i][j] %= md;
		}
	}
	ll ans = 0;
	for (ll i = 1; i <= n; i++)
		ans = (ans + d[i][k]) % md;
	cout << ans;
	return 0;
}
