/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;

class graph
{
private:
	vector <vector<ll>>g;
	ll n, lg;
	
	vector<vector<ll>>up;
	vector<ll>tin;
	vector<ll>tou;
	ll timer;

	vector<ll>num;
	vector<ll>d;
public:
	void dfs(ll u, ll pr)
	{
		tin[u] = timer++;
		up[u][0] = pr;
		for (ll i = 1; i <= lg; i++)
			up[u][i] = up[up[u][i - 1]][i - 1];
		for (auto v : g[u])
			if (v != pr)
				dfs(v, u);
		tou[u] = timer++;
	}	
	void dfs1(ll u, ll pr)
	{
		for (auto v : g[u])
			if (v != pr)
			{
				dfs1(v, u);
				d[u] += (d[v] - num[v]);
			}
	}
	bool ispar(ll u, ll v)
	{
		return tin[u] <= tin[v] && tou[u] >= tou[v];
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
	void prep()
	{
		dfs(1, 1);
	}
	void made(ll u, ll v)
	{
		d[u]++;
		d[v]++;
		ll l = lca(u, v);
		d[l]--;
		num[l]++;
	}
	void sol()
	{
		dfs1(1, 1);
		for (ll i = 1; i <= n; i++)
			cout << d[i] << " ";
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
		g.resize(n + 1);
		timer = 0;
		up.resize(n + 1, vector<ll>(lg + 1));
		tin.resize(n + 1);
		tou.resize(n + 1);

		num.resize(n + 1);
		d.resize(n + 1, 0);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> n >> m;
	graph t(n);
	for (ll i = 1; i <= n - 1; i++)
	{
		ll u, v;
		cin >> u >> v;
		t.add(u, v);
	}
	t.prep();
	for (ll i = 1; i <= m; i++)
	{
		ll u, v;
		cin >> u >> v;
		t.made(u, v);
	}
	t.sol();
	return 0;
}