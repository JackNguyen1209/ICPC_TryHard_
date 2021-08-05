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
	vector<vector<pll>>g;
	ll n;
public:
	void sol()
	{
		priority_queue<pll, vector<pll>, greater<pll>>q;
		vector<ll>d(n + 1, LLONG_MAX);
		vector<ll>c(n + 1, 0);
		c[1] = 1;
		d[1] = 0;
		q.push({ 0,1 });
		while (!q.empty())
		{
			pll tt = q.top();
			q.pop();
			ll u = tt.second;
			ll w = tt.first;
			if (d[u] != w) continue;
			for(auto v:g[u])
				if (d[u] + v.second < d[v.first])
				{
					d[v.first] = d[u] + v.second;
					q.push({ d[v.first],v.first });
					c[v.first] = c[u];
				}
				else if (d[u] + v.second == d[v.first])
					c[v.first] += c[u];
		}
		cout << d[n] << " " << c[n];

	}
	void add(ll u, ll v, ll w, ll t)
	{
		if (t == 1) g[u].push_back({ v,w });
		else g[u].push_back({ v,w }), g[v].push_back({ u,w });
	}
	graph(ll nn)
	{
		n = nn;
		g.resize(n + 1);
	}
};


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> n >> m;
	graph t(n);
	for (ll i = 1; i <= m; i++)
	{
		ll k, u, v, w;
		cin >> k >> u >> v >> w;
		t.add(u, v, w, k);
	}
	t.sol();

	return 0;
}