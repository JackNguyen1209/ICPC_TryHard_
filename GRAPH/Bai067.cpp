/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef int ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;

class graph
{
private:
	vector<vector<ll>>g;
	ll n, k;
	vector<bool>c;
	vector<ll>si;
	ll cen;
	vector<ll>d;
	vector<ll>mse;

	long long ans;
public:
	ll dfs_si(ll u, ll pr)
	{
		si[u] = 1;
		for (auto v : g[u])
			if (!c[v] && v != pr)
			{
				dfs_si(v, u);
				si[u] += si[v];
			}
		return si[u];
	}

	void dfs_ce(ll u, ll pr, ll sz)
	{
		ll s = 0;
		for (auto v : g[u])
			if (!c[v] && v != pr)
			{
				if (si[v] <= sz / 2)
					s += si[v];
				else
					s = -INT_MAX;
				dfs_ce(v, u, sz);
				if (cen != -1)
					return;
			}
		if (sz - s - 1 <= sz / 2)
		{
			cen = u;
			c[cen] = 1;
			return;
		}
	}
	void dfs_len(ll u, ll pr)
	{
		for (auto v : g[u])
			if (!c[v] && v != pr)
			{
				d[v] = d[u] + 1;
				dfs_len(v, u);
			}
	}
	void prep()
	{
		dfs_si(1, 1);
	}
	void dfs_clear(ll u, ll pr)
	{
		mse[d[u]] = 0;
		if (k - d[u] >= 0)
			mse[k - d[u]] = 0;
		for (auto v : g[u])
			if (!c[v] && v != pr)
				dfs_clear(v, u);
	}
	void dfs_xuli(ll u,ll pr,ll goc)
	{
		mse[d[u]]++;
		if (d[u] == k)
			ans++;
		for (auto v : g[u])
			if (!c[v] && v != pr)
				dfs_xuli(v, u, goc);
	}
	void dfs_xuli2(ll u, ll pr, ll goc)
	{
		if (k - d[u] >= 0)
			ans+=mse[k - d[u]];
		for (auto v : g[u])
			if (!c[v] && v != pr)
				dfs_xuli2(v, u, goc);
	}
	long long xuli(ll u)
	{
		dfs_clear(u, u);
		ll dem = 1;
		ans = 0;
		for (auto v : g[u])
		{
			if (dem != 1 && !c[v])
				dfs_xuli2(v, v, u);
			if (!c[v])
			{
				dfs_xuli(v, v, u);
				dem++;
			}
		}
		return ans;
	}
	long long sol()
	{
		queue<ll>s;
		cen = -1;
		dfs_ce(1, 1, n);
		s.push(cen);
		long long res = 0;
		while (!s.empty())
		{
			ll t = s.front();
			s.pop();
			d[t] = 0;
			dfs_len(t, t);
			res += xuli(t);
			//recurse
			for (auto v : g[t])
				if (!c[v])
				{
					cen = -1;
					ll sz = dfs_si(v, v);
					if (sz == 1)
						continue;
					dfs_ce(v, v, sz);
					s.push(cen);
				}
		}
		return res;
	}
	void add(ll u, ll v)
	{
		g[u].push_back(v);
		g[v].push_back(u);
	}
	graph(ll nn,ll kk)
	{
		n = nn;
		k = kk;
		g.resize(n + 1);
		c.resize(n + 1, 0);
		si.resize(n + 1, 0);
		d.resize(n + 1, 0);
		mse.resize(n + 1, 0);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	ll n, k;
	cin >> n >> k;
	graph t(n, k);
	for (ll i = 1; i <= n - 1; i++)
	{
		ll u, v;
		cin >> u >> v;
		t.add(u, v);
	}
	t.prep();
	cout << t.sol();
	return 0;
}