/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef int ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;

bool cmp(const plll& a, const plll& b)
{
	if (a.first == b.first)
		if (a.second.second - a.second.first == b.second.second - b.second.first)
			return a.second < b.second;
		else
			return (a.second.second - a.second.first) < (b.second.second - b.second.first);
	else
		return a.first < b.first;
}

class SpT
{
private:
	vector<vector<ll>> st;// st[i][j]: start at j, size 2^i;
	ll n; // array size
	vector<ll> log; // log value
	vector<ll> A; // copy of array
public:
	void merge(ll i, ll j)
	{
		if (A[st[i - 1][j]] <= A[st[i - 1][j + (1 << (i - 1))]])
			st[i][j] = st[i - 1][j];
		else
			st[i][j] = st[i - 1][j + (1 << (i - 1))];
	}
	void logs()
	{
		log.resize(n + 1);
		log[1] = 0;
		for (ll i = 2; i <= n; i++)
			log[i] = log[i / 2] + 1;
	}
	ll query(ll l, ll r)
	{
		ll p = log[r - l + 1];
		return min(A[st[p][l]], A[st[p][r - (1 << p) + 1]]);
	}
	void init(vector<ll>& a, ll si)
	{
		n = si;
		A = a;
		logs();
		st.resize(log[n] + 1);
		for (ll i = 0; i <= log[n]; i++)
			st[i].resize(n + 2, 0);
		for (ll i = 0; i <= log[n]; i++)
			for (ll j = 1; j + (1 << i) <= n + 1; j++)
				if (i == 0)
					st[0][j] = j; // index
				else
					merge(i, j);
	}
};

class LCP
{
private:
	string s;
	ll n;
	vector<ll>sa;   // (0->n-1)
	vector<ll> lcp; // (lcp[i]=lcp(suf[i],suf[i+1]))
	SpT t;
	vector<ll>trace;
public:

	void build()
	{
		// Suffix array
		for (ll i = n - 1; i >= 0; i--)
			sa.push_back(i);
		stable_sort(sa.begin(), sa.end(), [&](ll a, ll b) { return s[a] < s[b]; });
		vector<ll> classes(n);
		for (ll i = 0; i < n; ++i)
			classes[i] = s[i];
		for (ll len = 1; len < n; len *= 2)
		{
			vector<ll> c = classes;
			for (ll i = 0; i < n; i++)
				if (i > 0 && c[sa[i - 1]] == c[sa[i]] && sa[i - 1] + len < n && c[sa[i - 1] + len / 2] == c[sa[i] + len / 2])
					classes[sa[i]] = classes[sa[i - 1]];
				else
					classes[sa[i]] = i;
			vector<ll> cnt(n);
			iota(cnt.begin(), cnt.end(), 0);
			vector<ll> s = sa;
			for (ll i = 0; i < n; i++)
			{
				ll s1 = s[i] - len;
				if (s1 >= 0)
					sa[cnt[classes[s1]]++] = s1;
			}
		}
		// LCP
		vector<ll> rank(n);
		for (ll i = 0; i < n; i++)
			rank[sa[i]] = i;
		lcp.resize(n - 1);
		for (ll i = 0, h = 0; i < n; i++)
			if (rank[i] < n - 1)
			{
				for (ll j = sa[rank[i] + 1]; s[i + h] == s[j + h]; ++h);
				lcp[rank[i]] = h;
				if (h > 0) --h;
			}
		trace.resize(n + 1, 0);
		for (ll i = 1; i <= n - 1; i++)
			trace[sa[i]] = i;
	}
	ll find(pll a)
	{
		// lcp (1:n-2) 
		ll len = a.second - a.first + 1;
		ll pos = trace[a.first];
		ll l = 1;
		ll r = max(1, pos - 1);
		ll res = pos;
		while (l <= r)
		{
			ll m = (l + r) >> 1;
			ll id = t.query(m, r);
			if (id >= len)
			{
				r = m - 1;
				res = m;
			}
			else
				l = m + 1;
		}
		return res;
	}
	void solve(vector<pll>&a)
	{
		vector<plll>ans;
		for (auto p : a)
			ans.push_back({ find(p), p });
		sort(ans.begin(), ans.end(),cmp);
		for (auto p : ans)
			cout << p.second.first + 1 << " " << p.second.second + 1 << "\n";
	}
	LCP(string& tt)
	{
		s = tt + char(32);
		n = (ll)s.size();
		build();
		t.init(lcp,n - 2);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string s;
	cin >> s;
	LCP t(s);
	vector<pll>a;
	ll q;
	cin >> q;
	for (ll i = 1; i <= q; i++)
	{
		ll x, y;
		cin >> x >> y;
		x--, y--;
		a.push_back({ x,y });
	}
	t.solve(a);
	return 0;
}