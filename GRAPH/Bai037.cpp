/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;

class dsu
{
private:
	vector<ll>p;
	vector<ll>si;
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
		si[v] += si[u];
	}
	ll get_size(ll u)
	{
		return si[get(u)];
	}
	void init(ll nn)
	{
		n = nn;
		p.resize(n + 1, -1);
		si.resize(n + 1, 1);
	}
};

class graph
{
private:
	vector<vector<ll>>g;
	ll n;
	vector<ll>to;
	vector<ll>vis;
	// tarrjan
	vector<ll>low;
	vector<ll>num;
	vector<bool>found;
	stack<ll>st;
	ll count;
	// co dac
	dsu ao;
	ll id;
	//distance
	vector<ll>d;
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
			if ((ll)temp.size() >= 2)
			{
				for (ll i = 0; i <= (ll)temp.size() - 1; i++)
					ao.uni(temp[i], id);
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
	void dfs(ll u)
	{
		vis[u] = 1;
		ll num = -1;
		for (auto v : g[u])
		{
			if (!vis[v])
				dfs(v);
			num = d[v];
		}
		if (num!=-1)
			d[u] = num + 1;
	}
	void sol()
	{
		// topo 1
		fill(vis.begin(), vis.end(), 0);
		for (ll i = 1; i <= n; i++)
			if (!vis[i])
				topo(i);
		reverse(to.begin(), to.end());
		// tarjan (condense graph)
		fill(vis.begin(), vis.end(), 0);
		for (ll i = 0; i <= n - 1; i++)
			if (!vis[to[i]])
				dfstarjan(to[i]);
		//distance
			// xu ly cycle
		fill(vis.begin(), vis.end(), 0);
		for (ll i = 1; i <= n; i++)
		{
			ll u = ao.get(i);
			ll si = ao.get_size(i);
			if (si != 1)
			{
				d[i] = si - 1;
				vis[i] = 1;
			}
		}
		for (ll i = 0; i <= n - 1; i++)
			if (!vis[to[i]])
				dfs(to[i]);
		//out
		for (ll i = 1; i <= n; i++)
			cout << d[i] << " ";
	}
	void add(ll u, ll v)
	{
		g[u].push_back(v);
	}
	graph(ll nn)
	{
		n = nn;
		g.resize(n + 1);
		vis.resize(n + 1);

		// tarjan
		count = 0;
		low.resize(n + 1, 0);
		num.resize(n + 1, 0);
		found.resize(n + 1, 0);
		// co dac
		ao.init(2 * n + 1);
		id = n + 1;
		// distance
		d.resize(n + 1, 0);
	}

};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n;
	cin >> n;
	graph t(n);
	for (ll i = 1; i <= n; i++)
	{
		ll x;
		cin >> x;
		t.add(i, x);
	}
	t.sol();
	return 0;
}