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

const ll M = 1e9 + 7;

class graph
{
private:
	vector<vector<ll>>g;
	ll n, m;
public:
	ll sol()
	{
		//d(i,x): num of path to visit subset i finish at vertex u and start from 1

		vector<vector<ll>>d((1LL << n) + 1, vector<ll>(n + 1, 0));
		d[1][0] = 1;

		for (ll i = 0; i <= (1LL << n) - 1; i++)
			for (ll u = 0; u <= n - 1; u++)
				for (auto v : g[u])
				{
					ll subset = i;
					if (((subset & (1LL << v)) == 0LL) && ((subset & (1LL << u)) != 0LL))
					{
						d[subset | (1LL << v)][v] += d[subset][u];
						d[subset | (1LL << v)][v] %= M;
					}
				}
		return d[(1LL << n) - 1][n - 1];
	}
	void add(ll u, ll v)
	{
		g[u].push_back(v);
	}
	graph(ll nn, ll mm)
	{
		n = nn;
		m = mm;
		g.resize(n + 1);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> n >> m;
	graph t(n, m);
	for (ll i = 1; i <= m; i++)
	{
		ll u, v;
		cin >> u >> v;
		u--;
		v--;
		t.add(u, v);
	}
	cout << t.sol();

	return 0;
}