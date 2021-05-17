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

struct node
{
	ll s;
	ll la;
	node()
	{
		s = la = 0;
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
		if (l == r)
		{
			st[si].s += st[si].la;
			st[si].la = 0;
			return;
		}
		//Cap nhat nut hien tai
		st[si].s += st[si].la;
		//Truyen Xuong Con
		st[si * 2 + 1].la += st[si].la;
		st[si * 2].la += st[si].la;
		st[si].la = 0;

	}
	void merge(ll si)
	{
		st[si].s = max(st[si * 2].s, st[si * 2 + 1].s);
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
	void set(ll l, ll r, ll ql, ll qr, ll x, ll si)
	{
		push(l, r, si);
		if (l > r || r<ql || l>qr)return;
		if (ql <= l && r <= qr)
		{
			st[si].la = x;
			push(l, r, si);
			return;
		}
		ll m = (l + r) >> 1;
		set(l, m, ql, qr, x, si * 2);
		set(m + 1, r, ql, qr, x, si * 2 + 1);
		merge(si);
	}
	void set(ll ql, ll qr, ll x)
	{
		set(1, n, ql, qr, x, 1);
	}
	ll query(ll l, ll r, ll ql, ll qr, ll si)
	{
		push(l, r, si);
		if (l > r || l > qr || r < ql)return 0;
		if (ql <= l && r <= qr)return st[si].s;
		ll m = (l + r) >> 1;
		ll le = query(l, m, ql, qr, si * 2);
		ll ri = query(m + 1, r, ql, qr, si * 2 + 1);
		return max(le, ri);
	}
	ll query(ll ql, ll qr)
	{
		return query(1, n, ql, qr, 1);
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
	{
		cin >> a[i];
	}
	segtree t(a, n);
	for (ll i = 1; i <= q; i++)
	{
		ll x;
		cin >> x;
		if (x == 1)
		{
			ll l, r, x;
			cin >> l >> r >> x;
			t.set(l, r, x);
		}
		else
		{
			ll u, v;
			cin >> u >> v;
			cout << t.query(u, v) << "\n";
		}
	}

	return 0;
}