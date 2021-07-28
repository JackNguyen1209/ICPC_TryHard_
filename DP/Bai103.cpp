/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

class graph
{
private:
	vector<vector<ll>>g;
	ll n;
	vector<ll>d;
public:
	void dfs(ll u, ll pr)
	{
		for (auto v : g[u])
			if (v != pr)
				dfs(v, u),d[u] += d[v];
	}
	void dfs2(ll u, ll pr, ll k, ll &cnt)
	{
		for (auto v : g[u])
			if (v!=pr)
				if (d[v] >= k)
				{
					ll be = d[v];
					dfs2(v, u, k, cnt);
					d[u] -= be;
					d[u] += d[v];
				}
		if (d[u] >= k)
		{
			cnt++;
			d[u] = 0;
		}
	}
	void prep()
	{
		dfs(1, 1);
	}
	void sol(ll k)
	{
		ll cnt = 0;
		dfs2(1, 1, k,cnt);
		cout << cnt;
	}
	void add(ll u, ll v)
	{
		g[u].push_back(v);
		g[v].push_back(u);
	}
	graph(ll nn)
	{
		n = nn;
		g.resize(n + 1);
		d.resize(n + 1, 1);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll k, n;
	cin >> k >> n;
	graph t(n);
	for (ll i = 1; i <= n - 1; i++)
	{
		ll x;
		cin >> x;
		t.add(i + 1, x);
	}
	t.prep();
	t.sol(k);
	return 0;
}
