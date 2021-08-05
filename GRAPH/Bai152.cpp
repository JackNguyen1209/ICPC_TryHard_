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
	vector<vector<plll>>g;
	ll n;
public:
	ll sol(ll st,ll en)
	{
		priority_queue<plll, vector<plll>, greater<plll>>q;
		vector<vector<ll>>d(n + 1, vector<ll>(2, LLONG_MAX));
		//d[i][0]: st->i: no 2 way
		//d[i][1]: st->i: has 2 way
		d[st][0] = 0;
		q.push({ d[st][0],{st,0} });
		while (!q.empty())
		{
			plll temp = q.top();
			q.pop();
			ll ok = temp.second.second;
			ll u = temp.second.first;
			ll d_u = temp.first;
			if (d_u != d[u][ok])continue;
			if(ok)
				for (auto vv : g[u])
				{
					ll tw = vv.first;
					ll v = vv.second.first;
					ll w = vv.second.second;
					if (tw == 1)continue;
					if (d[v][1] > d[u][1] + w)
					{
						d[v][1] = d[u][1] + w;
						q.push({ d[v][1],{v,1} });
					}
				}
			else
				for (auto vv : g[u])
				{
					ll tw = vv.first;
					ll v = vv.second.first;
					ll w = vv.second.second;
					if (d[v][tw] > d[u][0] + w)
					{
						d[v][tw] = d[u][0] + w;
						q.push({ d[v][tw],{v,tw} });
					}
				}
		}
		return min(d[en][0], d[en][1]);
	}
	void add(ll u, ll v, ll w)
	{
		g[u].push_back({0, { v,w } });
	}
	void add1(ll u, ll v, ll w)
	{
		g[u].push_back({ 1,{ v,w } });
		g[v].push_back({ 1,{ u,w } });
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
	ll tt;
	cin >> tt;
	while(tt--)	
	{
		ll n, m, k, st, en;
		cin >> n >> m >> k >> st >> en;
		graph t(n);
		for (ll i = 1; i <= m; i++)
		{
			ll u, v, w;
			cin >> u >> v >> w;
			t.add(u, v, w);
		}
		for (ll i = 1; i <= k; i++)
		{
			ll u, v, w;
			cin >> u >> v >> w;
			t.add1(u, v, w);
		}
		ll ans = t.sol(st, en);
		if (ans == LLONG_MAX)
			cout << -1;
		else
			cout<<t.sol(st, en);
		cout << "\n";
	}

	return 0;
}