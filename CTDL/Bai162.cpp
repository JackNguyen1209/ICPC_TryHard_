/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

const ll M = 1e9 + 7;

ll fp(ll a, ll b)
{
	if (b == 0)
		return 1;
	ll t = fp(a, b >> 1);
	if (b & 1)
		return (t % M * t % M * a % M) % M;
	return (t % M * t % M) % M;
}

struct node
{
	ll s;
	ll l;
	node()
	{
		l = 1;
	}
};
class segtree
{
private:
	vector<node>st;
	ll n;
public:
	void push(ll l, ll r, ll si)
	{
		if (l > r || st[si].l == 1) return;
		if (l == r)
		{
			st[si].s *= st[si].l;
			st[si].s %= M;
			st[si].l = 1;
			return;
		}
		st[si].s = (st[si].s * st[si].l) % M;
		
		st[si * 2].l *= st[si].l;
		st[si * 2].l %= M;

		st[si * 2 + 1].l *= st[si].l;
		st[si * 2 + 1].l %= M;
		st[si].l = 1;
	}
	void merge(ll si)
	{
		st[si].s = (st[si * 2].s + st[si * 2 + 1].s) % M;
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
		if (l > r || r<ql || l>qr) return 0;
		if (ql <= l && r <= qr)return st[si].s;
		ll m = (l + r) >> 1;
		return (get(l, m, ql, qr, si * 2) % M + get(m + 1, r, ql, qr, si * 2 + 1) % M) % M;
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
	vector<ll>a(n + 1, 1);
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
