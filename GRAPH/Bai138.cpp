/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;
typedef pair<ld, pll>pfll;

class graph
{
private:
	vector<vector<pll>>g;
	ll n;
public:
	void sol(ll k)
	{
		priority_queue<pfll, vector<pfll>, greater<pfll>>q;
		vector<vector<ld>>d(n + 1, vector<ld>(k+1, (ld)LLONG_MAX));
		d[1][0] = (ld)0;
		q.push({ d[1][0],{1,0} });
		while (!q.empty())
		{
			pfll temp = q.top();
			q.pop();
			ld d_u = temp.first;
			ll u = temp.second.first;
			ll num = temp.second.second;
			if (d_u != d[u][num])continue;
			for (auto vv : g[u])
			{
				ll v = vv.first;
				ll w = vv.second;
				for (ll i = num; i <= k; i++)
					if (d[v][i] > d[u][num] + (ld)w / (1LL << (i - num)))
					{
						d[v][i] = d[u][num] + (ld)w / (1LL << (i - num));
						q.push({ d[v][i], {v,i} });
					}
			}
		}
		cout << fixed << setprecision(2) << d[n][k];
	}
	void add(ll u, ll v,ll w)
	{
		g[u].push_back({ v,w });
		g[v].push_back({ u,w });
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
	
	ll n, m, k;
	cin >> n >> m >> k;
	graph t(n);
	for (ll i = 1; i <= m; i++)
	{
		ll u, v, w;
		cin >> u >> v >> w;
		t.add(u, v, w);
	}
	t.sol(k);

	return 0;
}