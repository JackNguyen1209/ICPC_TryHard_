/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef int ll;
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
	ll query(ll l, ll r, ll ql, ll qr, ll si)
	{
		if (l > r || r<ql || l>qr)return 0;
		if (ql <= l && r <= qr)return st[si].s;
		ll m = (l + r) >> 1;
		return max(query(l, m, ql, qr, si * 2), query(m + 1, r, ql, qr, si * 2 + 1));
	}
	ll query(ll ql, ll qr)
	{
		return query(1, n, ql, qr, 1);
	}
	void change(ll l, ll r, ll pos, ll x, ll si)
	{
		if (l > r)return;
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
	void ini(vector<ll>& a, ll nn)
	{
		n = nn;
		st.resize(4 * n);
		build(a, 1, n, 1);
	}
};

class dsu
{
private:
	vector<ll>p;
	ll n;
public:
	ll get(ll u)
	{
		if (p[u] == -1)
			return u;
		return p[u] = get(p[u]);
	}
	void uni(ll u, ll v)// u to v
	{
		u = get(u);
		v = get(v);
		if (u == v)return;
		p[u] = v;
	}
	void ini(ll nn)
	{
		n = nn;
		p.resize(n + 1, -1);
	}
};

class graph
{
private:
	ll n, lg, time;
	vector<vector<ll>>g;
	vector<ll>up;
	vector<ll>tin;
	vector<ll>tout;

	vector<ll>si;
	vector<ll>heavy;
	vector<ll>des;
	vector<ll>pos;
	dsu t;
	segtree st;
public:
	bool ispar(ll u, ll v)//u is par of v
	{
		return tin[u] <= tin[v] && tout[u] >= tout[v];
	}
	void dfs(ll u, ll pr)
	{
		tin[u] = time++;
		up[u] = pr;
		ll lc = -1;
		for (auto v : g[u])
			if (v != pr)
			{
				dfs(v, u);
				if (lc == -1 || si[lc] < si[v])
					lc = v;
				si[u] += si[v];
			}
		si[u]++;
		if (si[u] != 1)
		{
			heavy[u] = lc;
			t.uni(lc, u);
		}
		tout[u] = time++;
	}
	void dfs1(ll u, ll pr)
	{
		des.push_back(u);
		if (heavy[u] != u)
			dfs1(heavy[u], u);
		for (auto v : g[u])
			if (v != pr && v != heavy[u])
				dfs1(v, u);
	}
	void prep(vector<ll>& a)
	{
		for (ll i = 1; i <= n; i++)
			heavy[i] = i;
		dfs(1, 1);
		dfs1(1, 1);
		for (ll i = 1; i <= n; i++)
			pos[des[i]] = i;
		vector<ll>temp(n + 1);
		for (ll i = 1; i <= n; i++)
			temp[pos[i]] = a[i];
		st.ini(temp, n);
	}
	void edit(ll u, ll x)
	{
		st.change(pos[u], x);
	}
	ll value(ll u, ll v)
	{
		ll ma = 0;
		// nhanh u
		while (true)
		{
			ll uu = t.get(u);
			if (ispar(uu, v))
				break;
			ma = max(ma, st.query(pos[uu], pos[u]));
			u = up[uu];
		}
		// nhanh v
		while (true)
		{
			ll vv = t.get(v);
			if (ispar(vv, u))
				break;
			ma = max(ma, st.query(pos[vv], pos[v]));
			v = up[vv];
		}
		if (u == v)
			return ma = max(ma, st.query(pos[u], pos[u]));
		if (ispar(u, v))
			return max(ma, st.query(pos[u], pos[v]));
		else
			return max(ma, st.query(pos[v], pos[u]));

	}
	void add(ll u, ll v)
	{
		g[u].push_back(v);
		g[v].push_back(u);
	}
	graph(ll nn)
	{
		n = nn;
		lg = ceil(log2(n));
		time = 0;

		g.resize(n + 1);
		up.resize(n + 1);
		tin.resize(n + 1);
		tout.resize(n + 1);

		si.resize(n + 1, 0);
		heavy.resize(n + 1, 0);
		des.push_back(0);
		pos.resize(n + 1);
		t.ini(n);
	}
};
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	ll n, q;
	cin >> n >> q;
	graph t(n);
	vector<ll>a(n + 1);
	for (ll i = 1; i <= n; i++)
		cin >> a[i];
	for (ll i = 1; i <= n - 1; i++)
	{
		ll u, v;
		cin >> u >> v;
		t.add(u, v);
	}
	t.prep(a);
	for (ll i = 1; i <= q; i++)
	{

		ll x;
		cin >> x;
		if (x == 1)
		{
			ll s, y;
			cin >> s >> y;
			t.edit(s, y);
		}
		else
		{
			ll u, v;
			cin >> u >> v;
			cout << t.value(u, v) << "\n";
		}
	}

	return 0;
}