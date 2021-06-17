/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

struct node
{
	ll s;
	ll l;
};
class segtree
{
private:
	vector<node>st;
	ll n;
public:
	void push(ll l, ll r, ll si)
	{
		if (l > r || st[si].l == 0) return;
		if (l == r)
		{
			st[si].s += st[si].l;
			st[si].l = 0;
			return;
		}
		st[si].s += st[si].l;
		st[si * 2].l += st[si].l;
		st[si * 2 + 1].l += st[si].l;
		st[si].l = 0;
	}
	void merge(ll si)
	{
		st[si].s = min(st[si * 2].s, st[si * 2 + 1].s);
	}
	void build(vector<ll>& a, ll l, ll r, ll si)
	{
		if (l > r)return;
		if (l == r)
		{
			st[si] = { a[l],0 };
			return;
		}
		ll m = (l + r) >> 1;
		build(a, l, m, si * 2);
		build(a, m + 1, r, si * 2 + 1);
		merge(si);
	}
	void add(ll l, ll r, ll ql, ll qr, ll si, ll x)
	{
		push(l, r, si);
		if (l > r || l > qr || r < ql)return;
		if (ql <= l && r <= qr)
		{
			st[si].l = x;
			push(l, r, si);
			return;
		}
		ll m = (l + r) >> 1;
		add(l, m, ql, qr, si * 2, x);
		add(m + 1, r, ql, qr, si * 2 + 1, x);
		merge(si);
	}
	ll get(ll l, ll r, ll ql, ll qr, ll si)
	{
		push(l, r, si);
		if (l > r || r<ql || l>qr)return LLONG_MAX;
		if (ql <= l && r <= qr)return st[si].s;
		ll m = (l + r) >> 1;
		return min(get(l, m, ql, qr, si * 2), get(m + 1, r, ql, qr, si * 2 + 1));
	}
	ll get(ll l, ll r)
	{
		return get(1, n, l, r, 1);
	}
	void add(ll l, ll r, ll x)
	{
		add(1, n, l, r, 1, x);
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
	ll n, m;
	cin >> n >> m;
	vector<ll>a(n + 1, 0);
	segtree t(a, n);
	for (ll i = 1; i <= m; i++)
	{
		ll x;
		cin >> x;
		if (x == 1)
		{
			ll l, r, x;
			cin >> l >> r >> x;
			t.add(l + 1, r, x);
		}
		else
		{
			ll pos, pos1;
			cin >> pos >> pos1;
			cout << t.get(pos + 1, pos1) << "\n";
		}
	}

	return 0;
}
