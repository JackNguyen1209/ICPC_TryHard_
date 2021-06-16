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
	vector<ll>cnt;
	ll val;
	node()
	{
		cnt.resize(41, 0);
	}
};
class segtree
{
private:
	vector<node>st;
	ll n;
public:
	void merge(ll si)
	{
		for (ll i = 1; i <= 40; i++)
			st[si].cnt[i] = (st[si * 2].cnt[i] + st[si * 2 + 1].cnt[i]);
	}
	void build(vector<ll>& a, ll l, ll r, ll si)
	{
		if (l > r)return;
		if (l == r)
		{
			st[si].cnt[a[l]]++;
			st[si].val = a[l];
			return;
		}
		ll m = (l + r) >> 1;
		build(a, l, m, si * 2);
		build(a, m + 1, r, si * 2 + 1);
		merge(si);
	}
	void sett(ll l, ll r, ll pos, ll x, ll si)
	{
		if (l > r)
			return;
		if (l == r && r == pos)
		{
			st[si].cnt[x]++;
			st[si].cnt[st[si].val]--;
			st[si].val = x;
			return;
		}
		ll m = (l + r) >> 1;
		if (pos <= m)
			sett(l, m, pos, x, si * 2);
		else
			sett(m + 1, r, pos, x, si * 2 + 1);
		merge(si);
	}
	void sett(ll pos, ll x)
	{
		sett(1, n, pos, x, 1);
	}
	void diff(ll l, ll r, ll ql, ll qr, ll si, set<ll>& s)
	{
		if (l > r || r<ql || l>qr)return;
		if (ql <= l && r <= qr)
		{
			for (ll i = 1; i <= 40; i++)
				if (st[si].cnt[i] >= 1)
					s.insert(i);
			return;
		}
		ll m = (l + r) >> 1;
		diff(l, m, ql, qr, si * 2,s);
		diff(m + 1, r, ql, qr, si * 2 + 1,s);
	}
	ll diff(ll l, ll r)
	{
		set<ll>s;
		diff(1, n, l, r, 1,s);
		return (ll)s.size();
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
	for (ll i = 1; i <= q; i++)
	{
		ll x;
		cin >> x;
		if (x == 1)
		{
			ll l, r;
			cin >> l >> r;
			cout << t.diff(l, r) << "\n";
		}
		else
		{
			ll u, v;
			cin >> u >> v;
			t.sett(u, v);
		}
	}
	return 0;
}