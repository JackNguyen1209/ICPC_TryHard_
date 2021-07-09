/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;

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
	ll query(ll l, ll r, ll ql, ll qr, ll si)
	{
		if (l > r || r<ql || l>qr)return 0;
		if (ql <= l && r <= qr)return st[si].s;
		ll m = (l + r) >> 1;
		return query(l, m, ql, qr, si * 2) + query(m + 1, r, ql, qr, si * 2 + 1);
	}
	ll query(ll ql, ll qr)
	{
		return query(1, n, ql, qr, 1);
	}
	void change(ll l, ll r, ll pos, ll x, ll si)
	{
		if (l == r && l == pos)
		{
			st[si].s = x;
			return;
		}
		ll m = (l + r) >> 1;
		if (pos <= m)
			change(l, m, pos, x, si * 2);
		else
			change(m + 1, r, pos, x, si * 2 + 1);
		merge(si);
	}
	void change(ll pos, ll x)
	{
		change(1, n, pos, x, 1);
	}
	void ini(vector<ll>&a,ll nn)
	{
		n = nn;
		st.resize(4 * n);
		build(a, 1, n, 1);
	}
};


class graph
{
private:
	vector<vector<ll>>g;
	ll n;
	
	vector<ll>st;
	vector<ll>en;
	vector<ll>tou;// tour
	vector<ll>pos;
	vector <ll>cost;
	ll id = 1;
	
	segtree t;
public:
	void dfs(ll u, ll pr)
	{
		tou.push_back(u);
		st[u] = id++;
		for (auto v : g[u])
			if (v != pr)
				dfs(v, u);
		en[u] = id - 1;
	}
	void prep()
	{
		tou.push_back(0);
		dfs(1, 1);
		vector<ll>it(n + 1);
		for(ll i=1;i<=n;i++)
			it[st[i]] = cost[i];
		t.ini(it, n);
	}
	ll query(ll u)
	{
		return t.query(st[u], en[u]);
	}
	void change(ll s, ll x)
	{
		t.change(st[s], x);
	}
	void add(ll u,ll v)
	{ 
		g[u].push_back(v);
		g[v].push_back(u);
	}
	graph(vector<ll>& c, ll nn)
	{
		n = nn;
		cost = c;
		g.resize(n + 1);
		st.resize(n + 1);
		en.resize(n + 1);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, q;
	cin >> n >> q;
	vector<ll>c(n + 1);
	for (ll i = 1; i <= n; i++)
		cin >> c[i];
	graph t(c, n);
	for (ll i = 1; i <= n - 1; i++)
	{
		ll u, v;
		cin >> u >> v;
		t.add(u, v);
	}
	t.prep();
	for (ll i = 1; i <= q; i++)
	{
		ll c;
		cin >> c;
		if (c == 1)
		{
			ll s, x;
			cin >> s >> x;
			t.change(s, x);
		}
		else
		{
			ll u;
			cin >> u;
			cout << t.query(u) << "\n";
		}
	}
	return 0;
}