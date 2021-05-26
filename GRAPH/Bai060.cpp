/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef int ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

class graph
{
private:
	vector<vector<ll>>g;
	ll n;
	ll lg;
	ll time = 0;
	vector<ll>d;
	vector<ll>tin, tou;
	vector<vector<ll>>up;
public:
	void dfs(ll u, ll pr, ll c)
	{
		d[u] = c;
		tin[u] = time++;
		up[u][0] = pr;
		for (ll i = 1; i <= lg; i++)
			up[u][i] = up[up[u][i - 1]][i - 1];
		for (auto v : g[u])
			if (v != pr)
				dfs(v, u, c + 1);
		tou[u] = time++;
	}
	bool ispar(ll u, ll v)// u is parent of v
	{
		return tin[u] <= tin[v] && tou[u] >= tou[v];
	}
	void sol()
	{
		time = 0;
		dfs(1, 1, 0);
	}
	ll lca(ll u, ll v)
	{
		if (ispar(u, v)) return u;
		if (ispar(v, u)) return v;
		for (ll i = lg; i >= 0; i--)
			if (!ispar(up[u][i], v))
				u = up[u][i];
		return up[u][0];
	}
	ll query(ll u, ll v)
	{
		return d[u] + d[v] - 2 * d[lca(u, v)];
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
		
		d.resize(n + 1, 0);
		tin.resize(n + 1);
		tou.resize(n + 1);
		up.resize(n + 1, vector<ll>(lg + 1));
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, q;
	cin >> n >> q;
	graph t(n);
	for (ll i = 1,u,v; i <= n - 1; i++)
	{
		cin >> u >> v;
		t.add(u, v);
	}
	t.sol();
	for (ll i = 1,a,b; i <= q; i++)
	{
		cin >> a >> b;
		cout << t.query(a, b) << "\n";
	}

	return 0;
}
