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
typedef pair<pll, ll>plll;

struct node
{
	ll co;
	ll tr;
};
class segtree
{
private:
	vector<node>st;
	ll n;
public:
	void merge(ll si, ll l, ll m, ll r)
	{
		st[si].co = st[si * 2].co;
		st[si].tr = st[si * 2].tr;
		if ((m + 1 - l) % 2 == 0)
		{
			st[si].co += st[si * 2 + 1].co;
			st[si].tr += st[si * 2 + 1].tr;
		}
		else
		{
			st[si].co += st[si * 2 + 1].tr;
			st[si].tr += st[si * 2 + 1].co;
		}
	}
	void build(vector<ll>& a, ll l, ll r, ll si)
	{
		if (l > r)return;
		if (l == r)
		{
			st[si] = { a[l],-a[l] };
			return;
		}
		ll m = (l + r) >> 1;
		build(a, l, m, si * 2);
		build(a, m + 1, r, si * 2 + 1);
		merge(si, l, m, r);
	}
	void set(ll l, ll r, ll k, ll x, ll si)
	{
		if (l > r)return;
		if (l == r)
		{
			st[si].co = x;
			st[si].tr = -x;
			return;
		}
		ll m = (l + r) >> 1;
		if (k <= m)
			set(l, m, k, x, si * 2);
		else
			set(m + 1, r, k, x, si * 2 + 1);
		merge(si, l, m, r);

	}
	void query(ll l, ll r, ll ql, ll qr, ll si, vector<plll>& ans)
	{
		if (l > r || ql > r || qr < l)return;
		if (ql <= l && r <= qr)
		{
			ans.push_back({ { l,r },si });
			return;
		}
		ll m = (l + r) >> 1;
		query(l, m, ql, qr, si * 2, ans);
		query(m + 1, r, ql, qr, si * 2 + 1, ans);
	}
	ll query(ll ql, ll qr)
	{
		vector<plll>ans;
		query(1, n, ql, qr, 1, ans);
		sort(ans.begin(), ans.end());
		ll s = 0;
		ll pr = ql;
		for (ll i = 0; i <= (ll)ans.size() - 1; i++)
		{
			if ((ans[i].first.first - pr) % 2 == 0)
			{
				s += st[ans[i].second].co;
			}
			else
			{
				s += st[ans[i].second].tr;
			}
		}
		return s;
	}
	void set(ll k, ll x)
	{
		set(1, n, k, x, 1);
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
	ll n;
	cin >> n;
	vector<ll>a(n + 1);
	for (ll i = 1; i <= n; i++)
		cin >> a[i];

	segtree t(a, n);
	ll m;
	cin >> m;
	for (ll i = 1; i <= m; i++)
	{
		ll x;
		cin >> x;
		if (x == 1)
		{
			ll l; ll r;
			cin >> l >> r;
			cout << t.query(l, r) << "\n";
		}
		else
		{
			ll u, v;
			cin >> u >> v;
			t.set(u, v);
		}
	}
	return 0;
}