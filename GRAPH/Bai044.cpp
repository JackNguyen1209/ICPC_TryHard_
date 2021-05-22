/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

class graph
{
private:
	vector<vector<ll>>g;
	vector<ll>eu;
	vector<ll>ev;
	ll n, m;
	vector <ll>ans;
public:
	void dfs(vector<ll>& used, ll u)
	{
		while (!(ll)g[u].empty())
		{
			ll id = g[u].back();
			g[u].pop_back();
			if (used[id])
				continue;
			ll fi = eu[id];
			ll se = ev[id];
			used[id] = 1;
			dfs(used, fi ^ se ^ u);
		}
		ans.push_back(u);
	}
	void sol()
	{
		for (ll i = 1; i <= n; i++)
			if ((ll)g[i].size() & 1)
			{
				cout << "IMPOSSIBLE";
				return;
			}
		vector<ll>used(m + 1, 0);
		dfs(used, 1);
		if ((ll)ans.size() != m + 1)
			cout << "IMPOSSIBLE";
		else
			for (ll i = 0; i <= (ll)ans.size() - 1; i++)
				cout << ans[i] << " ";
	}
	void add(ll u, ll v, ll id)
	{
		eu[id] = u;
		ev[id] = v;
		g[u].push_back(id);
		g[v].push_back(id);
	}
	graph(ll nn, ll mm)
	{
		n = nn;
		m = mm;
		g.resize(n + 1);
		eu.resize(m + 1);
		ev.resize(m + 1);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> n >> m;
	graph t(n, m);
	for (ll i = 1, a, b; i <= m; i++)
	{
		cin >> a >> b;
		t.add(a, b, i);
	}
	t.sol();


	return 0;
}