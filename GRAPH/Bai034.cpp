/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

const ll M = 1e9 + 7;

class graph
{
private:
	vector<vector<pll>>g;
	vector<ll>p;
	ll n;
public:
	void dijkstra(ll start)
	{
		vector<ll>d(n + 1, LLONG_MAX);
		vector<ll>num(n + 1, 0);
		vector<ll>mi(n + 1, LLONG_MAX);
		vector<ll>ma(n + 1, 0);
		priority_queue<pll, vector<pll>, greater<pll>>q;
		
		d[start] = 0;
		num[start] = 1;
		mi[start] = 0;
		ma[start] = 0;

		q.push({ d[start],start });
		while (!q.empty())
		{
			pll t = q.top();
			ll u = t.second;
			ll d_u = t.first;
			q.pop();
			if (d_u != d[u])
				continue;
			for (auto e : g[u])
			{
				ll v = e.first;
				ll w = e.second;
				if (d[u] + w < d[v])
				{
					d[v] = d[u] + w;
					q.push({ d[v],v });
					p[v] = u;
					num[v] = num[u];
					mi[v] = mi[u] + 1;
					ma[v] = ma[u] + 1;
				}
				else if (d[u] + w == d[v])
				{
					mi[v] = min(mi[v], mi[u] + 1);
					ma[v] = max(ma[v], ma[u] + 1);
					num[v] += num[u];
					num[v] %= M;
				}
			}
		}

		cout << d[n] << " " << num[n] << " " << mi[n] << " " << ma[n];
	}
	void add(ll u, ll v, ll w)
	{
		g[u].push_back({ v,w });
	}
	graph(ll nn)
	{
		n = nn;
		g.resize(n + 1);
		p.resize(n + 1, -1);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> n >> m;
	graph t(n);
	for (ll i = 1, a, b, w; i <= m; i++)
	{
		cin >> a >> b >> w;
		t.add(a, b, w);
	}
	t.dijkstra(1);
	return 0;
}
