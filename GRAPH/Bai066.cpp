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
	vector<ll>si;
	ll n;
	ll cent;
public:
	void dfs_size(ll u, ll pr)
	{
		for (auto v : g[u])
			if (v != pr)
			{
				dfs_size(v, u);
				si[u] += si[v];
			}
		si[u]++;
	}
	void dfs_centroid(ll u,ll pr)
	{
		ll s = 0;
		for (auto v : g[u])
			if (v != pr)
			{
				dfs_centroid(v, u);
				if (si[v] <= n / 2)
					s += si[v];
				else
					s = -INT_MAX;
			}
		if (n - s - 1 <= n / 2)
			cent = u;
	}
	void find()
	{
		dfs_size(1, -1);
		dfs_centroid(1, -1);
		cout << cent;
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
		si.resize(n + 1, 0);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n;
	cin >> n;
	graph t(n);
	for (ll i = 1; i <= n - 1; i++)
	{
		ll x, y;
		cin >> x >> y;
		t.add(x, y);
	}
	t.find();
	return 0;
}
