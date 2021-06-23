/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;
typedef pair<pll, ll>pl;

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
	void query(ll l, ll r, ll ql, ll qr, ll si, set<pl>& s)
	{
		if (l > r || l > qr || r < ql)return;
		if (ql <= l && r <= qr)
		{
			s.insert({ {l,r}, si });
			return;
		}
		ll m = (l + r) >> 1;
		query(l, m, ql, qr, si * 2, s);
		query(m + 1, r, ql, qr, si * 2 + 1, s);
	}
	ll sol(ll l, ll r, ll si)
	{
		if (st[si].s == 0)
			return -1;
		if (l == r)
			return l;
		ll m = (l + r) >> 1;
		if (st[si * 2].s >= 1)
			return sol(l, m, si * 2);
		else
			return sol(m + 1, r, si * 2 + 1);
	}
	ll query(ll ql, ll qr)
	{
		set<pl>s;
		query(1, n, ql, qr, 1, s);
		for (auto v : s)
		{
			ll x = sol(v.first.first, v.first.second, v.second);
			if (x != -1)
				return x;
		}
		return -1;
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
	void uni(ll u, ll v)//u->v
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
	ll n, m, lg, timer;
	vector<ll>tin;
	vector<ll>tout;
	vector <vector<ll>>up;
	vector<vector<pll>>g;

	vector<ll>si;
	vector<ll>heavy;
	vector<ll>pos;
	vector<ll>des;
	segtree st;
	vector<ll>state;
	dsu t;
public:
	bool ispar(ll u, ll v)// u is par of v
	{
		return tin[u] <= tin[v] && tout[u] >= tout[v];
	}
	void dfs(ll u, ll pr)
	{
		tin[u] = ++timer;
		up[u][0] = pr;
		for (ll i = 1; i <= lg; i++)
			up[u][i] = up[up[u][i - 1]][i - 1];
		bool f = 1;
		ll lc = -1;
		for (auto v : g[u])
			if (v.first != pr)
			{
				f = 0;
				dfs(v.first, u);
				if (lc == -1 || si[lc] > si[v.first])
					lc = v.first;
				si[u] += si[v.first];
			}
		if (f)//leave?
			si[u] = 1;
		else
		{
			heavy[u] = lc;
			t.uni(lc, u);
			si[u]++;
		}
		tout[u] = ++timer;
	}

	ll lca(ll u, ll v)
	{
		if (ispar(u, v))return u;
		if (ispar(v, u))return v;

		for (ll i = lg; i >= 0; i--)
			if (!ispar(up[u][i], v))
				u = up[u][i];
		return up[u][0];
	}
	void add(ll u, ll v, ll w)
	{
		g[u].push_back({ v,w });
		g[v].push_back({ u,w });
	}
	void go(ll u, ll pr)
	{
		des.push_back(u);
		if (heavy[u] != u)
			go(heavy[u], u);
		for (auto v : g[u])
			if (v.first != pr && v.first != heavy[u])
				go(v.first, u);
	}
	void solve()
	{
		dfs(1, 1);
		des.push_back(0);
		go(1, 1);
		for (ll i = 1; i <= n; i++)
			pos[des[i]] = i;

		vector<ll>a(n + 1, 0);
		st.ini(a, n);
	}
	void update(ll i)
	{
		state[i] = !state[i];
		st.change(pos[i], state[i]);
	}
	ll get(ll u)
	{
		vector<pll>ans;
		while (true)
		{
			ll v = t.get(u);

			if (v == 1)
			{
				ans.push_back({ 1,u });
				break;
			}
			if (ispar(v, 1))
			{
				ans.push_back({ 1,u });
				break;
			}
			else
			{
				ans.push_back({ v, u });
				u = up[v][0];
			}
		}
		reverse(ans.begin(), ans.end());
		for (ll i = 0; i <= (ll)ans.size() - 1; i++)
		{
			ll x = st.query(pos[ans[i].first], pos[ans[i].second]);
			if (x != -1)
				return des[x];
		}
		return -1;
	}
	graph(ll nn)
	{
		n = nn;
		m = n - 1;
		lg = ceil(log2(n));
		g.resize(n + 1);
		tin.resize(n + 1);
		tout.resize(n + 1);
		up.resize(n + 1, vector<ll>(lg + 1));

		t.ini(n);
		heavy.resize(n + 1);
		for (ll i = 1; i <= n; i++)
			heavy[i] = i;
		si.resize(n + 1);
		pos.resize(n + 1);
		state.resize(n + 1, 0);
		timer = 0;

	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, q;
	cin >> n >> q;
	graph t(n);
	for (ll i = 1; i <= n - 1; i++)
	{
		ll u, v;
		cin >> u >> v;
		t.add(u, v, 1);
	}
	t.solve();
	for (ll i = 1; i <= q; i++)
	{
		ll x;
		cin >> x;
		if (x == 1)
		{
			ll y;
			cin >> y;
			cout << t.get(y) << "\n";
		}
		else
		{
			ll y;
			cin >> y;
			t.update(y);
		}
	}

	return 0;
}