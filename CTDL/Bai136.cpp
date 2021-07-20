/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef int ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;

class LCP
{
private:
	string s;
	ll n;
	vector<ll>sa;   // (0->n-1)
	vector<ll> lcp; // (lcp[i]=lcp(suf[i],suf[i+1]))
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
	}

	void sol(ll k)
	{
		vector<ll>mx(n + 1, 0);
		for (ll i = 0; i <= n - 1; i++)
		{
			ll cur_len = n - 1 - sa[i];
			for (ll j = mx[i] + 1; j <= cur_len; j++)
			{
				k--;
				if (k == 0)
				{
					cout << (s.substr(sa[i], j));
					return;
				}
				for (ll kk = i + 1; kk <= n; kk++) {
					if (lcp[kk - 1] < j)
						break;
					mx[kk] = max(mx[kk], j);
					k--;
					if (k == 0)
					{
						cout << (s.substr(sa[i], j));
						return;
					}
				}
			}
		}
	}
	void solve(ll lens, ll lent)
	{
		ll ans = 0;
		ll pos = 0;
		for (ll i = n - 2; i >= 0; i--)
			if ((sa[i] <= lens - 1 && sa[i + 1] >= lens + 1) || (sa[i + 1] <= lens - 1 && sa[i] >= lens + 1))
			{
				if (lcp[i] >= ans)
				{
					ans = lcp[i];
					pos = sa[i];
				}
			}
		cout << s.substr(pos, ans);
	}
	LCP(string& t)
	{
		s = t + "$";
		n = (ll)s.size();
		build();
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string s, t;
	cin >> s >> t;
	string ss = s + '#' + t;
	LCP sol(ss);
	ll n = (ll)s.size();
	ll m = (ll)t.size();
	sol.solve(n, m);

	return 0;
}