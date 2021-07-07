/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;

vector<ll>c;

class dsu
{
private:
	vector<ll>p;
	ll n;
public:
	ll get(ll u)
	{
		if (p[u] == -1)
			return u;
		return p[u] = get(p[u]);
	}
	void uni(ll u, ll v)
	{
		u = get(u);
		v = get(v);
		if (u == v)return;

		p[u] = v;
	}
	void ini(ll nn)
	{
		n = nn;
		p.resize(n + 1, -1);
	}
};

class graph
{
private:
	// do thi
	vector<vector<ll>>g;
	vector<vector<ll>>g2;
	vector<pll>e;

	ll n, m;
	vector<bool>vis;
	// topo
	vector<ll>to;
	vector<ll>d;
	// tarjan
	vector<ll>low;
	vector<ll>num;
	vector<bool>found;
	stack<ll>st;
	ll count;
	// dinh ao 
	ll id;
	dsu ao;
public:
	void dfstarjan(ll u)
	{
		count++;
		num[u] = low[u] = count;
		st.push(u);
		for (auto v : g[u])
			if (!found[v])
				if (num[v] > 0)
					low[u] = min(low[u], num[v]);
				else
				{
					dfstarjan(v);
					low[u] = min(low[u], low[v]);
				}
		if (num[u] == low[u])
		{
			ll v;
			vector<ll>temp;
			do {
				v = st.top();
				st.pop();
				found[v] = 1;
				temp.push_back(v);
			} while (v != u);
			if ((ll)temp.size()>=2)
			{
				ll cost = 0;
				for (ll i = 0; i <= (ll)temp.size() - 1; i++)
				{
					ao.uni(temp[i], id);
					cost += c[temp[i]];
				}
				c[id] += cost;
				id++;
			}
		}
	}
	void topo(ll u)
	{
		vis[u] = 1;
		for (auto v : g[u])
			if (!vis[v])
				topo(v);
		to.push_back(u);
	}
	void topo2(ll u)
	{
		vis[u] = 1;
		for (auto v : g2[u])
			if (!vis[v])
				topo2(v);
		to.push_back(u);
	}
	void dfs(ll u)
	{
		vis[u] = 1;
		ll ma = 0;
		for (auto v : g2[u])
		{
			if (!vis[v])
				dfs(v);		
			ma = max(ma, d[v]);
		}
		d[u] = ma + c[u];
	}
	void sol()
	{
		// topo do thi 1
		fill(vis.begin(), vis.end(), 0);
		for (ll i = 1; i <= n; i++)
			if (!vis[i])
				topo(i);
		reverse(to.begin(), to.end());
		// tarjan do thi 1
		for (ll i = 0; i <= n - 1; i++)
			if (!found[to[i]])
				dfstarjan(to[i]);
		fill(vis.begin(), vis.end(), 0);
		// xu ly do thi 2
		for(ll i=0;i<=m-1;i++)
		{ 
			ll u = ao.get(e[i].first);
			ll v = ao.get(e[i].second);
			if (u != v)
				add2(u, v);
		}
		//topo do thi 2
		to.clear();
		for (ll i = 1; i <= 2*n; i++)
			if (!vis[i])
				topo2(i);
		reverse(to.begin(), to.end());
		//dp
		fill(vis.begin(), vis.end(), 0);
		for (ll i = 0; i <= (ll)to.size() - 1; i++)
			if (!vis[to[i]])
				dfs(to[i]);
		cout << *max_element(d.begin(), d.end());	
	}
	void add(ll u, ll v)
	{
		g[u].push_back(v);
		e.push_back({ u,v });
	}
	void add2(ll u, ll v)
	{
		g2[u].push_back(v);
	}
	graph(ll nn, ll mm)
	{
		n = nn;
		m = mm;
		g.resize(n + 1);
		g2.resize(2 * n + 1);
		vis.resize(2*n + 1);
		//dp
		d.resize(2*n + 1);
		// tarjan
		count = 0;
		low.resize(n + 1, 0);
		num.resize(n + 1, 0);
		found.resize(n + 1, 0);
		// ao
		ao.ini(2 * n + 1);
		id = n + 1;	
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> n >> m;
	c.resize(2 * n + 1, 0);

	graph t(n, m);
	for (ll i = 1; i <= n; i++)
		cin >> c[i];
	for (ll i = 1; i <= m; i++)
	{
		ll u, v;
		cin >> u >> v;
		t.add(u, v);
	}
	t.sol();
	return 0;
}