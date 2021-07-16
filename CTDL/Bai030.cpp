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
	ll mi;
	ll ma;
	ll s;
};

class segtree
{
private:
	vector<node>st;
	ll n;
	vector<ll>pos;
public:
	void merge(ll si)
	{
		st[si].ma = max(st[si * 2].ma, st[si * 2 + 1].ma);
		st[si].mi = min(st[si * 2].mi, st[si * 2 + 1].mi);
		st[si].s = st[si * 2].s + st[si * 2 + 1].s;
	}
	void build(vector<ll>& a, ll l, ll r, ll si)
	{
		if (l > r)return;
		if (l == r)
		{
			pos[si] = l;
			st[si] = { a[l],a[l],a[l] };return;
		}
		ll m = (l + r) >> 1;
		build(a, l, m, si * 2);
		build(a, m + 1, r, si * 2 + 1);
		merge(si);
	}
	ll find(ll l, ll r, ll num, ll si)
	{
		if (st[si].ma < num)return 0;
		if (l == r)return pos[si];
		ll m = (l + r) >> 1;
		if (st[si * 2].ma >= num)
			return find(l, m, num, si * 2);
		return find(m + 1, r, num, si * 2 + 1);
	}
	ll find(ll num)
	{
		return find(1, n, num, 1);
	}
	void edit(ll l, ll r, ll pos, ll x, ll si)
	{
		if (l == r && l == pos)
		{
			st[si] = { st[si].s - x,st[si].s - x,st[si].s - x }; return;
		}
		ll m = (l + r) >> 1;
		if (pos <= m)
			edit(l, m, pos, x, si * 2);
		else
			edit(m + 1, r, pos, x, si * 2 + 1);
		merge(si);
	}
	void edit(ll pos,ll x)
	{
		edit(1, n, pos, x, 1);
	}
	segtree(vector<ll>& a, ll nn)
	{
		n = nn;
		st.resize(4 * n);
		pos.resize(4 * n, -1);
		build(a, 1, n, 1);
	}

};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> n >> m;
	vector<ll>a(n + 1);
	for (ll i = 1; i <= n; i++)
		cin >> a[i];
	segtree t(a, n);
	for (ll i = 1; i <= m; i++)
	{
		ll x;
		cin >> x;
		ll key = t.find(x);
		cout << key << " ";
		if(key!=0)
			t.edit(key, x);
	}
	return 0;
}